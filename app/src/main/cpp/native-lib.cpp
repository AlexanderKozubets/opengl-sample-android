#include <jni.h>
#include "log_macros.h"

#include <GLES2/gl2.h>

#include <stdlib.h>

static void printGlValue(const char *name, GLenum glEnum) {
    const char *v = (const char *) glGetString(glEnum);
    LOGI("%s = %s\n", name, v);
}

static void checkGlError(const char* operation) {
    while (GLint error = glGetError()) {
        LOGI("After %s() glError (0x%x)\n", operation, error);
    }
}

const char* gVertexShader;

const char* gFragmentShader;

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gvPositionHandle;

bool setupGraphics(int w, int h) {
    printGlValue("Version", GL_VERSION);
    printGlValue("Vendor", GL_VENDOR);
    printGlValue("Renderer", GL_RENDERER);
    printGlValue("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
         gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

void renderFrame() {
    glClearColor(.0f, .0f, .0f, 1.0f);
    checkGlError("glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glUseProgram(gProgram);
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

void loadShaders(JNIEnv *env, jobject shaderRepository) {
//    jvm->AttachCurrentThread(&myEnv, 0);

    jstring vertexShaderName = env->NewStringUTF("draw_color.vert");
    jstring fragmentShaderName = env->NewStringUTF("draw_color.frag");

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
    gVertexShader = env->GetStringUTFChars(vertexShader, &isCopy);
    gFragmentShader = env->GetStringUTFChars(fragmentShader, &isCopy);
//    if (isCopy) {
//        env->ReleaseStringUTFChars(vertexShader, gVertexShader);
//    }
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_init(JNIEnv *env, jobject jobj, jint width,
                                                            jint height) {
    loadShaders(env, getShaderRepository(env, jobj));
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_view_NativeRenderer_draw(JNIEnv *env, jobject jobj) {
    renderFrame();
}