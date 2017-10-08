#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_alexander_kozubets_opengl_sample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(JNIEnv *env, jclass type, jint width,
                                                            jint height) {
    // TODO
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(JNIEnv *env, jclass type) {
    // TODO
}