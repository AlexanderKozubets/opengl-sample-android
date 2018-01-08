//
// Created by Alexander Kozubets on 11/8/17.
//

#include <malloc.h>
#include <utils/log_macros.h>
#include "Shader.h"
#include "GL2.h"

Shader::Shader(const char *vsh, const char *fsh) {
    id = createProgram(vsh, fsh);
}

GLuint Shader::getId() {
    return id;
}

void Shader::use() {
    GL2::useProgram(id);
}

void Shader::unuse() {
    glUseProgram(0);
}

GLuint Shader::loadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = GL2::createShader(shaderType);
    LOGI("Created shader with id %d", shader);

    if (shader) {
        GL2::shaderSource(shader, 1, &pSource, NULL);
        GL2::compileShader(shader);
        GLint compiled = 0;
        GL2::getShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            LOGE("Failed to compile source: %s", pSource);
            GLint infoLen = 0;
            GL2::getShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    GL2::getShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                GL2::deleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint Shader::createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        LOGE("Vertex shader creation failed!");
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        LOGE("Fragment shader creation failed!");
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        GL2::attachShader(program, vertexShader);
        GL2::attachShader(program, pixelShader);
        GL2::linkProgram(program);
        GLint linkStatus = GL_FALSE;
        GL2::getProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            GL2::getProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    GL2::getProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            GL2::deleteProgram(program);
            program = 0;
        }
    }
    return program;
}
