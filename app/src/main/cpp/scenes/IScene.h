//
// Created by Alexander Kozubets on 11/20/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_ISCENE_H
#define OPENGL_SAMPLE_ANDROID_ISCENE_H

#include <Shader.h>
#include <utils/log_macros.h>

class IScene {
protected:
    Shader* shader;

public:
    IScene(Shader *shader) : shader(shader) {}

    virtual ~IScene() {
        LOGI("~IScene destructor was called");
        if (shader) {
            delete shader;
            shader = NULL;
        }
    }

    virtual void draw() = 0;
};

#endif //OPENGL_SAMPLE_ANDROID_ISCENE_H
