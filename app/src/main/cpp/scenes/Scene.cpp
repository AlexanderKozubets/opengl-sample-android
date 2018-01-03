#include <stdlib.h>
#include "Scene.h"

jfieldID Scene::nativePointerFieldId = 0;

void Scene::registerClass(JNIEnv* env) {
    jclass clazz = env->FindClass("com/alexander/kozubets/opengl/view/ShaderNativeRenderer");

    if (clazz == 0) {
        LOGE("No class was found!");
        abort();
    }

    nativePointerFieldId = env->GetFieldID(clazz, "nativePointer", "J"); // J -> Long
    if (nativePointerFieldId == 0) {
        LOGE("No field was found!");
        abort();
    }
}

void Scene::setNativeScene(JNIEnv* env, jobject instance, Scene* scene) {
    env->SetLongField(instance, nativePointerFieldId, (long)scene);
}

Scene* Scene::getNativeScene(JNIEnv* env, jobject instance) {
    return (Scene *) env->GetLongField(instance, nativePointerFieldId);
}

Scene::~Scene() {
    LOGI("Scene destructor was called");
    if (shader) {
        delete shader;
        shader = NULL;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_ShaderNativeRenderer_destroy(JNIEnv *env, jobject instance) {
    Scene* scene = Scene::getNativeScene(env, instance);
    if (scene) {
        delete scene;
        Scene::setNativeScene(env, instance, 0);
    }
}
