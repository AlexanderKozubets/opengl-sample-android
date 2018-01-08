#include <GLES2/gl2.h>
#include <gl_wrapper/GL2.h>
#include <utils/log_macros.h>
#include <jni.h>
#include <string>
#include <repository/ShaderRepository.h>
#include "TriangleScene.h"

class string;

TriangleScene::TriangleScene(Shader *shader) : Scene(shader) {
    LOGI("TriangleScene::TriangleScene start/end");
}

TriangleScene::~TriangleScene() {
    LOGI("TriangleScene::~TriangleScene start/end");
}

void TriangleScene::draw() {
    LOGI("TriangleScene::draw start");
    GL2::clearColor(.0f, .0f, .0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    shader->use();

    GLuint gvPositionHandle = GL2::getAttribLocation(shader->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    static const GLfloat gTriangleVertices[] = {
            -1.0f, 1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
            1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
            1.0f, 1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = {0, 1, 2, 2, 3, 0};

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);
    GL2::drawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);

    shader->unuse();
    LOGI("TriangleScene::draw end");
}

extern "C" {

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_constructNative(JNIEnv *env,
                                                                                    jobject instance,
                                                                                    jobject shaderRepository) {
    ShaderRepository* repo = new ShaderRepository(env, shaderRepository);
    Shader *shader = repo->getShader("draw_color");
    TriangleScene *triangleScene = new TriangleScene(shader);
    Scene::setNativeScene(env, instance, triangleScene);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_initNative(JNIEnv *env,
                                                                               jobject instance,
                                                                               jint width,
                                                                               jint height) {
    Scene::getNativeScene(env, instance)->init(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_drawNative(JNIEnv *env,
                                                                               jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}

}
