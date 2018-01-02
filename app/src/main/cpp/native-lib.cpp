#include <jni.h>
#include "utils/log_macros.h"
#include "Shader.h"

#include <GLES2/gl2.h>

#include <stdlib.h>
#include <string>
#include <gl_wrapper/GL2.h>
#include <utils/gl_error_check.h>
#include <math/matr4.h>
#include <scenes/triangle/TriangleScene.h>

GLuint gTextureId = 0;

Shader* gSimpleProgram = 0;
Shader* gTextureProgram = 0;

//TODO: move to base IScene implementation
bool setupGraphics(int w, int h) {
    printGlValue("Version", GL_VERSION);
    printGlValue("Vendor", GL_VENDOR);
    printGlValue("Renderer", GL_RENDERER);
    printGlValue("Extensions", GL_EXTENSIONS);
    LOGI("setupGraphics(%d, %d)", w, h);

    GL2::viewport(0, 0, w, h);
    return true;
}

void renderSimple() {
    gSimpleProgram->use();

    GLuint gvPositionHandle = GL2::getAttribLocation(gSimpleProgram->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    static const GLfloat gTriangleVertices[] = {
            -1.0f,  1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
             1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
             1.0f,  1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = { 0, 1, 2, 2, 3, 0};

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);
    GL2::drawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
}

void renderTexture(Shader* shader, GLint textureId) {
    shader->use();

    static const GLfloat gTriangleVertices[] = {
            -1.0f,  1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
             1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
             1.0f,  1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = { 0, 1, 2, 2, 3, 0};

    // Set vertices
    GLuint gvPositionHandle;
    gvPositionHandle = GL2::getAttribLocation(shader->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);

    // Set texture
    GL2::activeTexture(GL_TEXTURE0);
    GL2::bindTexture(GL_TEXTURE_2D, textureId);
    GL2::uniform1i(glGetUniformLocation(shader->getId(), "tex"), 0);

    GL2::drawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);

    shader->unuse();
}

void renderTextureWithTransform(Shader* shader, GLint textureId) {
    shader->use();

    static const GLfloat gTriangleVertices[] = {
            -1.0f,  1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
            1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
            1.0f,  1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = { 0, 1, 2, 2, 3, 0};

    // Set vertices
    GLuint gvPositionHandle = GL2::getAttribLocation(shader->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);

    // Set texture
    GL2::activeTexture(GL_TEXTURE0);
    GL2::bindTexture(GL_TEXTURE_2D, textureId);
    GL2::uniform1i(glGetUniformLocation(shader->getId(), "tex"), 0);

    GLuint modelViewProjectionHandle = GL2::getUniformLocation(shader->getId(), "uMVPMatrix");
    matr4 matrix = matr4::identity();
    GL2::uniformMatrix4fv(modelViewProjectionHandle, 1, GL_FALSE, matrix.ptr());

    GL2::drawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);

    shader->unuse();
}

void renderFrame() {
    GL2::clearColor(.0f, .0f, .0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (gTextureId) {
//        renderTexture(gTextureProgram, gTextureId);
        renderTextureWithTransform(gTextureProgram, gTextureId);
    } else {
        renderSimple();
    }
}

extern "C" {
JNIEXPORT void JNICALL Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(
        JNIEnv *env, jobject jobj, jint width, jint height);

JNIEXPORT void JNICALL Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(
        JNIEnv *env, jobject jobj);
};

//TODO: move to base IScene implementation
jobject getShaderRepository(JNIEnv *env, jobject renderer) {
    jclass javaClass = env->GetObjectClass(renderer);
    jfieldID fieldId = env->GetFieldID(javaClass, "shaderRepository", "Lcom/alexander/kozubets/opengl/view/ShaderRepository;");
    jobject repo = env->GetObjectField(renderer, fieldId);
    env->DeleteLocalRef(javaClass);
    return repo;
}

//TODO: move to base IScene implementation
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
    gTextureProgram = loadShaders(env, shaderRepository, "draw_texture_2");
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(JNIEnv *env, jobject jobj) {
    renderFrame();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_onTextureLoaded(JNIEnv *env, jobject instance, jint textureId) {
    if (gTextureId) {
        glDeleteTextures(1, &gTextureId);
        gTextureId = 0;
    }
    gTextureId = textureId;
}
