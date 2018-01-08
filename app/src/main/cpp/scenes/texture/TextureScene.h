#ifndef OPENGL_SAMPLE_ANDROID_TEXTURESCENE_H
#define OPENGL_SAMPLE_ANDROID_TEXTURESCENE_H

#include <scenes/Scene.h>

class TextureScene : public Scene {
private:
    Shader* textureShader;

    GLuint textureId;

public:
    TextureScene(ShaderRepository *shaderRepository);

    virtual ~TextureScene();

    virtual void setTexture(GLuint texId);

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_TEXTURESCENE_H
