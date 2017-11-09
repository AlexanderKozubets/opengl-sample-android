#include <jni.h>
#include "log_macros.h"
#include "Shader.h"

#include <GLES2/gl2.h>

#include <stdlib.h>
#include <string>

static void printGlValue(const char *name, GLenum glEnum) {
    const char *v = (const char *) glGetString(glEnum);
    LOGI("%s = %s\n", name, v);
}

static void checkGlError(const char* operation) {
    while (GLint error = glGetError()) {
        LOGI("After %s() glError (0x%x)\n", operation, error);
    }
}

GLuint textureId = 0;

Shader* gSimpleProgram = 0;
Shader* gTextureProgram = 0;

bool setupGraphics(int w, int h) {
    printGlValue("Version", GL_VERSION);
    printGlValue("Vendor", GL_VENDOR);
    printGlValue("Renderer", GL_RENDERER);
    printGlValue("Extensions", GL_EXTENSIONS);
    LOGI("setupGraphics(%d, %d)", w, h);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

void renderFrame() {
    glClearColor(.0f, .0f, .0f, 1.0f);
    checkGlError("glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    gSimpleProgram->use();

    GLuint gvPositionHandle;
    gvPositionHandle = glGetAttribLocation(gSimpleProgram->getId(), "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);
    checkGlError("glUseProgram");

    static const GLfloat gTriangleVertices[] = {
            -1.0f,  1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
             1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
             1.0f,  1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = { 0, 1, 2, 2, 3, 0};

    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
    checkGlError("glDrawArrays");
}

extern "C" {
JNIEXPORT void JNICALL Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(
        JNIEnv *env, jobject jobj, jint width, jint height);

JNIEXPORT void JNICALL Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(
        JNIEnv *env, jobject jobj);
};

jobject getShaderRepository(JNIEnv *env, jobject renderer) {
    jclass javaClass = env->GetObjectClass(renderer);
    jfieldID fieldId = env->GetFieldID(javaClass, "shaderRepository", "Lcom/alexander/kozubets/opengl/view/ShaderRepository;");
    jobject repo = env->GetObjectField(renderer, fieldId);
    env->DeleteLocalRef(javaClass);
    return repo;
}

Shader* loadShaders(JNIEnv *env, jobject shaderRepository, const char *name) {
//    jvm->AttachCurrentThread(&myEnv, 0);

    std::string vsh = name + std::string(".vert");
    std::string fsh = name + std::string(".frag");

    jstring vertexShaderName = env->NewStringUTF(vsh.c_str());
    jstring fragmentShaderName = env->NewStringUTF(fsh.c_str());

    jclass javaClass = env->GetObjectClass(shaderRepository);
    if (javaClass == NULL) {
        LOGI("ERROR - cant find class");
    }

    jmethodID method = env->GetMethodID(javaClass, "getShader", "(Ljava/lang/String;)Ljava/lang/String;");
    if (method == NULL) {
        LOGI("ERROR - cant access method");
    }

    jstring vertexShader = (jstring) env->CallObjectMethod(shaderRepository, method, vertexShaderName);
    jstring fragmentShader = (jstring) env->CallObjectMethod(shaderRepository, method, fragmentShaderName);

    jboolean isCopy;
    const char* strVertexShader = env->GetStringUTFChars(vertexShader, &isCopy);
    const char* strFragmentShader = env->GetStringUTFChars(fragmentShader, &isCopy);

//    if (isCopy) {
//        env->ReleaseStringUTFChars(vertexShader, gVertexShader);
//    }

    return new Shader(strVertexShader, strFragmentShader);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(JNIEnv *env, jobject jobj, jint width,
                                                            jint height) {
    jobject shaderRepository = getShaderRepository(env, jobj);
    gSimpleProgram = loadShaders(env, shaderRepository, "draw_color");
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(JNIEnv *env, jobject jobj) {
    renderFrame();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_onTextureLoaded(JNIEnv *env, jobject instance) {
    // TODO
}