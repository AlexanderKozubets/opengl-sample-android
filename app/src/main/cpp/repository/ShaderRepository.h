#ifndef OPENGL_SAMPLE_ANDROID_SHADERREPOSITORY_H
#define OPENGL_SAMPLE_ANDROID_SHADERREPOSITORY_H

#include <Shader.h>
#include <string>
#include <jni.h>

class ShaderRepository {
private:
    JavaVM *jvm;

    jobject shaderRepository;

    JNIEnv* getJniEnv();

public:

    ShaderRepository(JNIEnv *env, jobject shaderRepository);

    virtual ~ShaderRepository();

    virtual Shader* getShader(std::string name);
};

#endif //OPENGL_SAMPLE_ANDROID_SHADERREPOSITORY_H
