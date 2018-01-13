#include <GLES2/gl2.h>
#include <gl_wrapper/GL2.h>
#include <utils/log_macros.h>
#include <jni.h>
#include <string>
#include <cmath>
#include <repository/ShaderRepository.h>
#include <gl_wrapper/GLDrawElementsMode.h>
#include "TriangleScene.h"

TriangleScene::TriangleScene(ShaderRepository *shaderRepository) : Scene(shaderRepository) {
    LOGI("TriangleScene::TriangleScene start");
    mode = GLDrawElementsMode::TRIANGLES;
    setVerticesCount(3);
    colorShader = shaderRepository->getShader("draw_color");
    LOGI("Color shader id: %d", colorShader->getId());
    LOGI("TriangleScene::TriangleScene end");

}

TriangleScene::~TriangleScene() {
    LOGI("TriangleScene::~TriangleScene start");
    if (colorShader) {
        delete colorShader;
        colorShader = 0;
    }
    LOGI("TriangleScene::~TriangleScene end");
}

void TriangleScene::setDrawMode(GLDrawElementsMode mode) {
    this->mode = mode;
}

void TriangleScene::setVerticesCount(int count) {
    this->verticesCount = std::min(7, std::max(1, count));
}

void TriangleScene::draw() {
    LOGI("TriangleScene::draw start");
    float maxValue = 1.0f - 0.5f;
    GL2::clearColor(.0f, .0f, .0f, maxValue);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    colorShader->use();

    GLuint gvPositionHandle = GL2::getAttribLocation(colorShader->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    static const GLfloat gTriangleVertices[] = {
            -maxValue, maxValue, 0.0f, //  square left top vertex,     0 index
            -maxValue, -maxValue, 0.0f, // square left bottom vertex,  1 index
            maxValue, -maxValue, 0.0f, //  square right bottom vertex, 2 index
            maxValue, maxValue, 0.0f,  //  square right top vertex,    3 index
            0.0f, 0.0f, 0.0f           //  square center,              4 index
    };

//    const GLubyte indices[] = {0, 1, 2, 0, 2, 3};
    const GLubyte indices[] = {0, 1, 4, 2, 3, 4};

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);

    glLineWidth(10);
    GL2::drawElements(mode, verticesCount, GL_UNSIGNED_BYTE, indices);

    colorShader->unuse();
    LOGI("TriangleScene::draw end");
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TriangleRenderer_constructNative(JNIEnv *env,
                                                                             jobject instance,
                                                                             jobject shaderRepository) {
    TriangleScene *triangleScene = new TriangleScene(new ShaderRepository(env, shaderRepository));
    Scene::setNativeScene(env, instance, triangleScene);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TriangleRenderer_initNative(JNIEnv *env,
                                                                        jobject instance,
                                                                        jint width,
                                                                        jint height) {
    Scene::getNativeScene(env, instance)->init(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TriangleRenderer_setModeNative(JNIEnv *env,
                                                                           jobject instance,
                                                                           jint mode) {
    TriangleScene *scene = reinterpret_cast<TriangleScene *>(Scene::getNativeScene(env, instance));
    scene->setDrawMode((GLDrawElementsMode) mode);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TriangleRenderer_setVerticesCountNative(JNIEnv *env,
                                                                                    jobject instance,
                                                                                    jint count) {
    TriangleScene *scene = reinterpret_cast<TriangleScene *>(Scene::getNativeScene(env, instance));
    scene->setVerticesCount(count);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TriangleRenderer_drawNative(JNIEnv *env,
                                                                        jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}

}
