#include <GLES2/gl2.h>
#include <gl_wrapper/GL2.h>
#include <utils/log_macros.h>
#include <jni.h>
#include "TriangleScene.h"

TriangleScene::TriangleScene(Shader *shader) : IScene(shader) {

}

TriangleScene::~TriangleScene() {

}

void TriangleScene::draw() {
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
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_construct(JNIEnv *env,
                                                                              jobject instance) {
    TriangleScene* triangleScene = new TriangleScene(0);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_destroy(JNIEnv *env,
                                                                            jobject instance) {

    // TODO
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_init(JNIEnv *env,
                                                                         jobject instance,
                                                                         jint width, jint height) {
    // TODO
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TriangleRenderer_draw(JNIEnv *env,
                                                                         jobject instance) {

    // TODO
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
