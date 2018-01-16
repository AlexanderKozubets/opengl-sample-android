#include <gl_wrapper/GL2.h>
#include "TextureScene.h"

TextureScene::TextureScene(ShaderRepository *shaderRepository) : Scene(shaderRepository),
                                                                 textureId(0) {
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
    GL2::clearColor(1.0f, 1.0f, 1.0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    textureShader->use();

    float maxValue = 0.75f;
    static const GLfloat vertices[] = {
            -maxValue, maxValue, 0.0f,  // left top vertex,     0 index
            -maxValue, -maxValue, 0.0f, // left bottom vertex,  1 index
            maxValue, -maxValue, 0.0f,  // right bottom vertex, 2 index
            maxValue, maxValue, 0.0f    // right top vertex,    3 index
    };

    GLfloat texCoords[] = {
            0, 0,
            0, 1,
            1, 1,
            1, 0
    };

    const GLubyte indices[] = {0, 1, 2, 2, 3, 0};

    // Set vertices
    GLuint vPositionHandle, vTexCoordHandle;
    vPositionHandle = GL2::getAttribLocation(textureShader->getId(), "vPosition");
    vTexCoordHandle = GL2::getAttribLocation(textureShader->getId(), "vTexCoord");

    GL2::vertexAttribPointer(vPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    GL2::enableVertexAttribArray(vPositionHandle);

    GL2::vertexAttribPointer(vTexCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
    GL2::enableVertexAttribArray(vTexCoordHandle);

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
Java_com_alexander_kozubets_opengl_renderer_TextureRenderer_constructNative(JNIEnv *env,
                                                                                   jobject instance,
                                                                                   jobject shaderRepository) {
    TextureScene *textureScene = new TextureScene(new ShaderRepository(env, shaderRepository));
    Scene::setNativeScene(env, instance, textureScene);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureRenderer_initNative(JNIEnv *env,
                                                                              jobject instance,
                                                                              jint width,
                                                                              jint height) {
    Scene::getNativeScene(env, instance)->init(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureRenderer_drawNative(JNIEnv *env,
                                                                              jobject instance) {
    Scene::getNativeScene(env, instance)->draw();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_alexander_kozubets_opengl_renderer_TextureRenderer_onTextureLoadedNative(
        JNIEnv *env,
        jobject instance,
        jint textureId) {
    TextureScene *scene = reinterpret_cast<TextureScene *>(Scene::getNativeScene(env, instance));
    scene->setTexture((GLuint) textureId);
}
