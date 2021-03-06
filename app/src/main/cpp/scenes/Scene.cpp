#include <stdlib.h>
#include <utils/gl_error_check.h>
#include <gl_wrapper/GL2.h>
#include "Scene.h"

jfieldID Scene::nativePointerFieldId = 0;

Scene::Scene(ShaderRepository *shaderRepository) : shaderRepository(shaderRepository) {
    LOGI("Scene::Scene()");
}

Scene::~Scene() {
    LOGI("Scene::~Scene start");
    if (shaderRepository) {
        delete shaderRepository;
        shaderRepository = NULL;
    }
    LOGI("Scene::~Scene end");
}

void Scene::init(int w, int h) {
    printGlValue("Version", GL_VERSION);
    printGlValue("Vendor", GL_VENDOR);
    printGlValue("Renderer", GL_RENDERER);
    printGlValue("Extensions", GL_EXTENSIONS);
    LOGI("setupGraphics(%d, %d)", w, h);

    GL2::viewport(0, 0, w, h);
}

void Scene::registerClass(JNIEnv* env) {
    LOGI("Scene::registerClass start");
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

    LOGI("Scene::registerClass end");
}

void Scene::setNativeScene(JNIEnv* env, jobject instance, Scene* scene) {
    env->SetLongField(instance, nativePointerFieldId, (long)scene);
}

Scene* Scene::getNativeScene(JNIEnv* env, jobject instance) {
    return (Scene *) env->GetLongField(instance, nativePointerFieldId);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_ShaderNativeRenderer_destroy(JNIEnv *env, jobject instance) {
    LOGI("Scene::destroy start");
    Scene* scene = Scene::getNativeScene(env, instance);
    if (scene) {
        delete scene;
        Scene::setNativeScene(env, instance, 0);
    }
    LOGI("Scene::destroy end");
}
