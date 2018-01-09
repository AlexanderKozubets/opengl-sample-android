#include <gl_wrapper/GL2.h>
#include <math/matr4.h>
#include <scenes/triangle/TriangleScene.h>
#include "TransformationScene.h"

TransformationScene::TransformationScene(ShaderRepository *shaderRepository) : Scene(
        shaderRepository) {
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

matr4 gProjMatr = matr4::identity();

void TransformationScene::draw() {
    GL2::clearColor(.0f, .0f, .0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    transformTextureShader->use();

    static const GLfloat gTriangleVertices[] = {
            -1.0f, 1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
            1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
            1.0f, 1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = {0, 1, 2, 2, 3, 0};

    // Set vertices
    GLuint gvPositionHandle = GL2::getAttribLocation(transformTextureShader->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);

    // Set texture
    GL2::activeTexture(GL_TEXTURE0);
    GL2::bindTexture(GL_TEXTURE_2D, textureId);
    GL2::uniform1i(glGetUniformLocation(transformTextureShader->getId(), "tex"), 0);

    GLuint modelViewProjectionHandle = GL2::getUniformLocation(transformTextureShader->getId(),
                                                               "uMVPMatrix");
    matr4 matrix = gProjMatr; //matr4::identity();
    GL2::uniformMatrix4fv(modelViewProjectionHandle, 1, GL_FALSE, matrix.ptr());

    GL2::drawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
    GL2::bindTexture(GL_TEXTURE_2D, 0);

    transformTextureShader->unuse();
}

void TransformationScene::init(int width, int height) {
    Scene::init(width, height);
    float aspectRatio = float(width) / height;
    gProjMatr = matr4::ortho(-aspectRatio, aspectRatio, -1, 1, -1, 1);
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
    TransformationScene *scene = reinterpret_cast<TransformationScene *>(Scene::getNativeScene(env, instance));
    scene->setTexture(textureId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureProjectionRenderer_drawNative(JNIEnv *env,
                                                                                 jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}