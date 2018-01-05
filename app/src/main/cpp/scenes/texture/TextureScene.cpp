#include <gl_wrapper/GL2.h>
#include "TextureScene.h"

TextureScene::TextureScene(Shader *shader) : Scene(shader), textureId(0) {

}

TextureScene::~TextureScene() {
    setTexture(0);
}

void TextureScene::setTexture(GLuint texId) {
    if (textureId) {
        GL2::deleteTextures(1, &texId);
    }
    textureId = texId;
}

void TextureScene::draw() {
    GL2::clearColor(.0f, .0f, .0f, 1.0f);
    GL2::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    shader->use();

    static const GLfloat gTriangleVertices[] = {
            -1.0f, 1.0f, 0.0f, // left top vertex,     0 index
            -1.0f, -1.0f, 0.0f, // left bottom vertex,  1 index
            1.0f, -1.0f, 0.0f, // right bottom vertex, 2 index
            1.0f, 1.0f, 0.0f  // right top vertex,    3 index
    };

    const GLubyte indices[] = {0, 1, 2, 2, 3, 0};

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

    GL2::drawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLubyte), GL_UNSIGNED_BYTE, indices);

    shader->unuse();
}
