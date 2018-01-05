#ifndef OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H
#define OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H

#include <scenes/Scene.h>

class TransformationScene : public Scene {
private:
    GLuint textureId;

public:
    TransformationScene(Shader *shader);

    virtual ~TransformationScene();

    virtual void setTexture(GLuint texId);

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H
