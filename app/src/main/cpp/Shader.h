//
// Created by Alexander Kozubets on 11/8/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_SHADER_H
#define OPENGL_SAMPLE_ANDROID_SHADER_H


#include <GLES2/gl2.h>

class Shader {
private:

    GLuint id;

    GLuint loadShader(GLenum shaderType, const char *pSource);

    GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);

public:

    Shader(const char *vsh, const char *fsh);

    GLuint getId();

    void use();

    void unuse();
};


#endif //OPENGL_SAMPLE_ANDROID_SHADER_H
