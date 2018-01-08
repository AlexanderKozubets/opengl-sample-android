#ifndef OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H
#define OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H

#include <scenes/Scene.h>

class TransformationScene : public Scene {
private:
    Shader* transformTextureShader;

    GLuint textureId;

public:
    TransformationScene(ShaderRepository *shaderRepository);

    virtual ~TransformationScene();

    virtual void setTexture(GLuint texId);

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H
