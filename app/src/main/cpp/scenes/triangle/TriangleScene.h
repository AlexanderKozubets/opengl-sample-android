#ifndef OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H
#define OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H

#include <scenes/Scene.h>
#include <GLDrawElementsMode.h>

class TriangleScene : public Scene {
private:
    Shader* colorShader;

    GLDrawElementsMode mode;

    int verticesCount;

public:
    TriangleScene(ShaderRepository *shaderRepository);

    virtual ~TriangleScene();

    virtual void setDrawMode(GLDrawElementsMode mode);

    virtual void setVerticesCount(int count);

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H
