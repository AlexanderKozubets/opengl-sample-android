#ifndef OPENGL_SAMPLE_ANDROID_GLDRAWELEMENTSMODE_H
#define OPENGL_SAMPLE_ANDROID_GLDRAWELEMENTSMODE_H

#include <GLES2/gl2.h>

enum GLDrawElementsMode {
    POINTS = GL_POINTS,
    LINE_STRIP = GL_LINE_STRIP,
    LINE_LOOP = GL_LINE_LOOP,
    LINES = GL_LINES,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,
    TRIANGLES = GL_TRIANGLES,
};

#endif //OPENGL_SAMPLE_ANDROID_GLDRAWELEMENTSMODE_H
