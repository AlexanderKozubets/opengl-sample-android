#ifndef OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H
#define OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H

#include <scenes/IScene.h>

class TriangleScene : public IScene {
public:
    TriangleScene(Shader *shader);

    virtual void draw();

    virtual ~TriangleScene();
};

#endif //OPENGL_SAMPLE_ANDROID_SIMPLESCENE_H
