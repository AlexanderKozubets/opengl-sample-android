#include <jni.h>
#include <utils/log_macros.h>
#include "ShaderRepository.h"

ShaderRepository::ShaderRepository(JNIEnv *env, jobject shaderRepository) : jvm(0) {
    env->GetJavaVM(&jvm);
    this->shaderRepository = env->NewGlobalRef(shaderRepository);
}

ShaderRepository::~ShaderRepository() {
    getJniEnv()->DeleteGlobalRef(shaderRepository);
    shaderRepository = NULL;
    jvm = NULL;
}

JNIEnv *ShaderRepository::getJniEnv() {
    JNIEnv *env = 0;
    jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    jvm->AttachCurrentThread(&env, 0);
    return env;
}

Shader *ShaderRepository::getShader(std::string name) {
    JNIEnv *env = getJniEnv();

    std::string vsh = name + std::string(".vert");
    std::string fsh = name + std::string(".frag");

    jstring vertexShaderName = env->NewStringUTF(vsh.c_str());
    jstring fragmentShaderName = env->NewStringUTF(fsh.c_str());

    jclass javaClass = env->GetObjectClass(shaderRepository);
    if (javaClass == NULL) {
        LOGE("ERROR - cant find class");
    }

    jmethodID method = env->GetMethodID(javaClass, "getShader",
                                        "(Ljava/lang/String;)Ljava/lang/String;");
    if (method == NULL) {
        LOGE("ERROR - cant access method");
    }

    jstring vertexShader = (jstring) env->CallObjectMethod(shaderRepository, method,
                                                           vertexShaderName);
    jstring fragmentShader = (jstring) env->CallObjectMethod(shaderRepository, method,
                                                             fragmentShaderName);

    jboolean isCopy;
    const char *strVertexShader = env->GetStringUTFChars(vertexShader, &isCopy);
    const char *strFragmentShader = env->GetStringUTFChars(fragmentShader, &isCopy);

//    if (isCopy) {
//        env->ReleaseStringUTFChars(vertexShader, gVertexShader);
//    }

    LOGI("Vertex shader: %s", strVertexShader);
    LOGI("Fragment shader: %s", strFragmentShader);

    Shader *shader = new Shader(strVertexShader, strFragmentShader);
    LOGI("Linked program: %d", shader->getId());

    return shader;
}
