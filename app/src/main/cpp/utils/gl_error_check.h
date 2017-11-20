//
// Created by Alexander Kozubets on 11/19/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_GL_ERROR_CHECK_H
#define OPENGL_SAMPLE_ANDROID_GL_ERROR_CHECK_H

#include <stdlib.h>
#include <GLES2/gl2.h>
#include "log_macros.h"

static void printGlValue(const char *name, GLenum glEnum) {
    const char *v = (const char *) glGetString(glEnum);
    LOGI("%s = %s\n", name, v);
}

static bool checkGlError(const char* operation) {
    while (GLint error = glGetError()) {
        LOGE("After %s glError (0x%x)\n", operation, error);
        abort();
    }
    return false;
}

#define GL(f) f; checkGlError(#f);
#define GL_enum(f) checkGlError(#f) ? -1 : glCheckFramebufferStatus(target);
#define GL_uint(f) GLuint res = f; checkGlError(#f); return res;

#endif //OPENGL_SAMPLE_ANDROID_GL_ERROR_CHECK_H
