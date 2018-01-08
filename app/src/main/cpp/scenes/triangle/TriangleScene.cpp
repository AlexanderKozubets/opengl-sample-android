#include <GLES2/gl2.h>
#include <gl_wrapper/GL2.h>
#include <utils/log_macros.h>
#include <jni.h>
#include <string>
#include "TriangleScene.h"

class string;

TriangleScene::TriangleScene(Shader *shader) : Scene(shader) {
    LOGI("TriangleScene::TriangleScene start/end");
}

TriangleScene::~TriangleScene() {
    LOGI("TriangleScene::~TriangleScene start/end");
}

void TriangleScene::draw() {
    LOGI("TriangleScene::draw start");
    GL2::clearColor(.0f, .0f, .0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    shader->use();

    GLuint gvPositionHandle = GL2::getAttribLocation(shader->getId(), "vPosition");
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

    shader->unuse();
    LOGI("TriangleScene::draw end");
}

//TODO: move to base Scene implementation
jobject getShaderRepository(JNIEnv *env, jobject renderer) {
    jclass javaClass = env->GetObjectClass(renderer);
    jfieldID fieldId = env->GetFieldID(javaClass, "shaderRepository", "Lcom/alexander/kozubets/opengl/view/ShaderRepository;");
    jobject repo = env->GetObjectField(renderer, fieldId);
    env->DeleteLocalRef(javaClass);
    return repo;
}

//TODO: move to base Scene implementation
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
    
    LOGI("Vertex shader: %s", strVertexShader);
    LOGI("Fragment shader: %s", strFragmentShader);

    Shader *shader = new Shader(strVertexShader, strFragmentShader);
    LOGI("Linked program: %d", shader->getId());

    return shader;
}


extern "C" {

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_constructNative(JNIEnv *env,
                                                                              jobject instance) {
    jobject shaderRepository = getShaderRepository(env, instance);
    Shader* shader = loadShaders(env, shaderRepository, "draw_color");
//    gTextureProgram = loadShaders(env, shaderRepository, "draw_texture_2");

    TriangleScene *triangleScene = new TriangleScene(shader);
    Scene::setNativeScene(env, instance, triangleScene);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_initNative(JNIEnv *env,
                                                                         jobject instance,
                                                                         jint width, jint height) {
    Scene::getNativeScene(env, instance)->init(width, height);
}

JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_drawNative(JNIEnv *env,
                                                                         jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}

}

/*static JNINativeMethod gCameraMethods[] = {
        *//* name, signature, funcPtr *//*
        { "nativeConstructor",   "()V",    (void*)Camera_constructor   },
        { "nativeDestructor",    "()V",    (void*)Camera_destructor    },
        { "save",                "()V",    (void*)Camera_save          },
        { "restore",             "()V",    (void*)Camera_restore       },
        { "translate",           "(FFF)V", (void*)Camera_translate     },
        { "rotateX",             "(F)V",   (void*)Camera_rotateX       },
        { "rotateY",             "(F)V",   (void*)Camera_rotateY       },
        { "rotateZ",             "(F)V",   (void*)Camera_rotateZ       },
        { "rotate",              "(FFF)V", (void*)Camera_rotate        },
        { "setLocation",         "(FFF)V", (void*)Camera_setLocation   },
        { "getLocationX",        "()F",    (void*)Camera_getLocationX  },
        { "getLocationY",        "()F",    (void*)Camera_getLocationY  },
        { "getLocationZ",        "()F",    (void*)Camera_getLocationZ  },
        { "nativeGetMatrix",     "(I)V",   (void*)Camera_getMatrix     },
        { "nativeApplyToCanvas", "(I)V",   (void*)Camera_applyToCanvas },
        { "dotWithNormal",       "(FFF)F", (void*)Camera_dotWithNormal }
};

int register_android_graphics_Camera(JNIEnv* env) {
    jclass clazz = env->FindClass("android/graphics/Camera");
    if (clazz == 0) {
        return -1;
    }
    gNativeInstanceFieldID = env->GetFieldID(clazz, "native_instance", "I");
    if (gNativeInstanceFieldID == 0) {
        return -1;
    }
    return android::AndroidRuntime::registerNativeMethods(env,
                                                          "android/graphics/Camera",
                                                          gCameraMethods,
                                                          SK_ARRAY_COUNT(gCameraMethods));
}*/
