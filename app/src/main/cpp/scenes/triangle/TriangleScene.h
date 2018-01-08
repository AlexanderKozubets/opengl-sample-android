#ifndef OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H
#define OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H

#include <scenes/Scene.h>

class TriangleScene : public Scene {
private:
    Shader* colorShader;

public:
    TriangleScene(ShaderRepository *shaderRepository);

    virtual ~TriangleScene();

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H
