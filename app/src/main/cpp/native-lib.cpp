#include <jni.h>
#include <scenes/Scene.h>

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }

    Scene::registerClass(env);

    return  JNI_VERSION_1_6;
}
