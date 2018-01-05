#ifndef OPENGL_SAMPLE_ANDROID_TEXTURESCENE_H
#define OPENGL_SAMPLE_ANDROID_TEXTURESCENE_H

#include <scenes/Scene.h>

class TextureScene : public Scene {
private:
    GLuint textureId;

public:
    TextureScene(Shader *shader);

    virtual ~TextureScene();

    virtual void setTexture(GLuint texId);

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_TEXTURESCENE_H
