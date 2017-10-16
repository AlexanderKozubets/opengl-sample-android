#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

bool setup(int w, int h) {
    return true;
}

void renderFrame() {
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
    setup(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(JNIEnv *env, jclass type) {
    renderFrame();
}