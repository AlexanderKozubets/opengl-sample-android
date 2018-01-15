#include <gl_wrapper/GL2.h>
#include <math/matr4.h>
#include <scenes/triangle/TriangleScene.h>
#include "TransformationScene.h"

#define RAD(degrees) float(degrees) / 180.0f * M_PI

TransformationScene::TransformationScene(ShaderRepository *shaderRepository) : Scene(
        shaderRepository), angleX(0), angleY(0), angleZ(0),
        projMatr(matr4::identity()), viewMatr(matr4::identity()), modelMatr(matr4::identity()) {
    LOGI("TransformationScene::TransformationScene start");
    transformTextureShader = shaderRepository->getShader("draw_texture_2");
    LOGI("Texture shader id: %d", transformTextureShader->getId());
    LOGI("TransformationScene::TransformationScene end");
}

TransformationScene::~TransformationScene() {
    LOGI("TransformationScene::~TransformationScene start");
    if (transformTextureShader) {
        delete transformTextureShader;
        transformTextureShader = 0;
    }
    setTexture(0);
    LOGI("TransformationScene::~TransformationScene end");
}

void TransformationScene::setTexture(GLuint texId) {
    if (textureId) {
        GL2::deleteTextures(1, &textureId);
    }
    textureId = texId;
}

void TransformationScene::draw() {
    GL2::clearColor(1.0f, 1.0f, 1.0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    transformTextureShader->use();

    float d = 0.5f;
    static const GLfloat gTriangleVertices[] = {
            // near cube face
            -d, d, d,  // left top vertex,     0 index
            -d, -d, d, // left bottom vertex,  1 index
            d, -d, d,  // right bottom vertex, 2 index
            d, d, d,   // right top vertex,    3 index

            // far cube face
            -d, d, -d,  // left top vertex,     4 index
            -d, -d, -d, // left bottom vertex,  5 index
            d, -d, -d,  // right bottom vertex, 6 index
            d, d, -d,   // right top vertex,    7 index

    };

    const GLubyte indices[] = {
            0, 1, 2, 2, 3, 0, // front face
            6, 5, 4, 4, 7, 6, // rear face
            4, 0, 3, 3, 7, 4, // top face
            1, 5, 6, 6, 2, 1, // bottom face
            4, 5, 1, 1, 0, 4, // left face
            3, 2, 6, 6, 7, 3, // right face
    };

    const float colors[] = {
            0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f,
    };

    const int componentsPerColor = 3;

    // Set vertices
    GLuint gvPositionHandle = GL2::getAttribLocation(transformTextureShader->getId(), "vPosition");
//    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);

    // Set texture
    GL2::activeTexture(GL_TEXTURE0);
    GL2::bindTexture(GL_TEXTURE_2D, textureId);
    GL2::uniform1i(glGetUniformLocation(transformTextureShader->getId(), "tex"), 0);

    GLuint modelViewProjectionHandle = GL2::getUniformLocation(transformTextureShader->getId(),
                                                               "uMVPMatrix");
    modelMatr = matr4::rotateX(angleX) * matr4::rotateY(angleY) * matr4::rotateZ(angleZ);
    matr4 mvp = projMatr * viewMatr * modelMatr;
    GL2::uniformMatrix4fv(modelViewProjectionHandle, 1, GL_FALSE, mvp.ptr());

    GLuint colorHandle = GL2::getAttribLocation(transformTextureShader->getId(), "vColor");
    GL2::enableVertexAttribArray(colorHandle);
    GL2::vertexAttribPointer(colorHandle, 4, GL_FLOAT, false, componentsPerColor * 4, colors);

    GL2::drawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
    GL2::bindTexture(GL_TEXTURE_2D, 0);

    transformTextureShader->unuse();
}

void TransformationScene::init(int width, int height) {
    Scene::init(width, height);
    float aspectRatio = float(width) / height;
    projMatr = matr4::frustum(-aspectRatio, aspectRatio, -1, 1, 3, 7);
    viewMatr = matr4::lookAt(0, 0, -4, 0, 0, 0, 0, 1, 0);
}

void TransformationScene::setAngleX(float angleDeg) {
    TransformationScene::angleX = RAD(angleDeg);
}

void TransformationScene::setAngleY(float angleDeg) {
    TransformationScene::angleY = RAD(angleDeg);
}

void TransformationScene::setAngleZ(float angleDeg) {
    TransformationScene::angleZ = RAD(angleDeg);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_constructNative(JNIEnv *env,
                                                                                      jobject instance,
                                                                                      jobject shaderRepository) {
    TransformationScene *transformationScene = new TransformationScene(
            new ShaderRepository(env, shaderRepository));
    Scene::setNativeScene(env, instance, transformationScene);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_initNative(JNIEnv *env,
                                                                                 jobject instance,
                                                                                 jint width,
                                                                                 jint height) {
    Scene::getNativeScene(env, instance)->init(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_onTextureLoadedNative(
        JNIEnv *env, jobject instance, jint textureId) {
    Scene *pScene = Scene::getNativeScene(env, instance);
    TransformationScene *scene = reinterpret_cast<TransformationScene *>(pScene);
    scene->setTexture(textureId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_setRotationXNative(
        JNIEnv *env, jobject instance, jfloat angleDegrees) {
    Scene *pScene = Scene::getNativeScene(env, instance);
    TransformationScene *scene = reinterpret_cast<TransformationScene *>(pScene);
    scene->setAngleX(angleDegrees);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_setRotationYNative(
        JNIEnv *env, jobject instance, jfloat angleDegrees) {
    Scene *pScene = Scene::getNativeScene(env, instance);
    TransformationScene *scene = reinterpret_cast<TransformationScene *>(pScene);
    scene->setAngleY(angleDegrees);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_setRotationZNative(
        JNIEnv *env, jobject instance, jfloat angleDegrees) {
    Scene *pScene = Scene::getNativeScene(env, instance);
    TransformationScene *scene = reinterpret_cast<TransformationScene *>(pScene);
    scene->setAngleZ(angleDegrees);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_drawNative(JNIEnv *env,
                                                                                 jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}