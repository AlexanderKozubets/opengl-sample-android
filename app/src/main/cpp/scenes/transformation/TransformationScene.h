#ifndef OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H
#define OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H

#include <scenes/Scene.h>

class TransformationScene : public Scene {
private:
    Shader* transformTextureShader;

    GLuint textureId;

    float angleX;

    float angleY;

    float angleZ;

    matr4 projMatr;

    matr4 viewMatr;

    matr4 modelMatr;

public:
    TransformationScene(ShaderRepository *shaderRepository);

    virtual ~TransformationScene();

    virtual void init(int w, int h);

    virtual void setTexture(GLuint texId);

    void setAngleX(float angleDeg);

    void setAngleY(float angleDeg);

    void setAngleZ(float angleDeg);

    virtual void draw();
};

#endif //OPENGL_SAMPLE_ANDROID_TRANSFORMATIONSCENE_H
