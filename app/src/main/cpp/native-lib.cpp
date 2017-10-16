#include <jni.h>
#include "log_macros.h"

#include <GLES2/gl2.h>

#include <stdlib.h>

static void printGlValue(const char *name, GLenum glEnum) {
    const char *v = (const char *) glGetString(glEnum);
    LOGI("%s = %s\n", name, v);
}

static void checkGlError(const char* operation) {
    while (GLint error = glGetError()) {
        LOGI("After %s() glError (0x%x)\n", operation, error);
    }
}

bool setupGraphics(int w, int h) {
    printGlValue("Version", GL_VERSION);
    printGlValue("Vendor", GL_VENDOR);
    printGlValue("Renderer", GL_RENDERER);
    printGlValue("Extensions", GL_EXTENSIONS);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

void renderFrame() {
    glClearColor(.0f, .0f, .0f, 1.0f);
    checkGlError("glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");
}

extern "C" {
JNIEXPORT void JNICALL Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(
        JNIEnv *env, jclass type, jint width, jint height);

JNIEXPORT void JNICALL Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(
        JNIEnv *env, jclass type);
};

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(JNIEnv *env, jclass type, jint width,
                                                            jint height) {
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(JNIEnv *env, jclass type) {
    renderFrame();
}