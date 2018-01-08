#include <gl_wrapper/GL2.h>
#include "TextureScene.h"

TextureScene::TextureScene(ShaderRepository *shaderRepository) : Scene(shaderRepository), textureId(0) {
    LOGI("TextureScene::TextureScene start");
    textureShader = shaderRepository->getShader("draw_texture");
    LOGI("Texture shader id: %d", textureShader->getId());
    LOGI("TextureScene::TextureScene end");
}

TextureScene::~TextureScene() {
    LOGI("TextureScene::~TextureScene start");
    if (textureShader) {
        delete textureShader;
        textureShader = 0;
    }
    setTexture(0);
    LOGI("TextureScene::~TextureScene end");
}

void TextureScene::setTexture(GLuint texId) {
    if (textureId) {
        GL2::deleteTextures(1, &textureId);
    }
    textureId = texId;
}

void TextureScene::draw() {
    GL2::clearColor(.0f, .0f, .0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    textureShader->use();

    static const GLfloat gTriangleVertices[] = {
            -1.0f, 1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
            1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
            1.0f, 1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = {0, 1, 2, 2, 3, 0};

    // Set vertices
    GLuint gvPositionHandle;
    gvPositionHandle = GL2::getAttribLocation(textureShader->getId(), "vPosition");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle);

    GL2::vertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    GL2::enableVertexAttribArray(gvPositionHandle);

    // Set texture
    GL2::activeTexture(GL_TEXTURE0);
    GL2::bindTexture(GL_TEXTURE_2D, textureId);
    GL2::uniform1i(glGetUniformLocation(textureShader->getId(), "tex"), 0);

    GL2::drawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);
    GL2::bindTexture(GL_TEXTURE_2D, 0);

    textureShader->unuse();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TextureRenderer_constructNative(JNIEnv *env,
                                                                                   jobject instance,
                                                                                   jobject shaderRepository) {
    TextureScene *textureScene = new TextureScene(new ShaderRepository(env, shaderRepository));
    Scene::setNativeScene(env, instance, textureScene);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TextureRenderer_initNative(JNIEnv *env,
                                                                              jobject instance,
                                                                              jint width,
                                                                              jint height) {
    Scene::getNativeScene(env, instance)->init(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_scenes_triangle_TextureRenderer_drawNative(JNIEnv *env,
                                                                              jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}