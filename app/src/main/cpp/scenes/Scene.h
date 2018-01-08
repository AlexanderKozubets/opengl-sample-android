//
// Created by Alexander Kozubets on 11/20/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_ISCENE_H
#define OPENGL_SAMPLE_ANDROID_ISCENE_H

#include <Shader.h>
#include <utils/log_macros.h>
#include <jni.h>

class Scene {
private:
    static jfieldID nativePointerFieldId;

protected:
    Shader* shader;

public:
    Scene(Shader *shader);

    virtual ~Scene();

    virtual void init(int w, int h);

    virtual void draw() = 0;

    static void registerClass(JNIEnv* env);

    static void setNativeScene(JNIEnv*, jobject instance, Scene* scene);

    static Scene* getNativeScene(JNIEnv*, jobject instance);
};

#endif //OPENGL_SAMPLE_ANDROID_ISCENE_H
