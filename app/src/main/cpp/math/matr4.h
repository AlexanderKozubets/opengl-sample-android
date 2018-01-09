//
// Created by Alexander Kozubets on 11/22/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_MATR4_H
#define OPENGL_SAMPLE_ANDROID_MATR4_H

#include <string.h>
#include <cmath>

class matr4 {
private:
    float m[16];

public:

    matr4(float matrix[16]) {
        memcpy(&m, matrix, 16 * sizeof(float));
    }

    ~matr4() {
    }

    float *ptr() {
        return m;
    }

    static matr4 ortho(float left, float right, float top, float bottom, float far, float near) {
        float sx = 2.0f / (right - left);
        float sy = 2.0f / (top - bottom);
        float sz = 2.0f / (far - near);
        float tx = -(right + left) / (right - left);
        float ty = -(top + bottom) / (top - bottom);
        float tz = -(far + near) / (far - near);
        return matr4(
                new float[16]{
                        sx, 0, 0, tx,
                        0, sy, 0, ty,
                        0, 0, sz, tz,
                        0, 0, 0, 1
                });
    }

    static matr4 identity() {
        return matr4(
                new float[16]{
                        1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1
                });
    }

    static matr4 scale(float sx, float sy, float sz) {
        return matr4(
                new float[16]{
                        sx, 0, 0, 0,
                        0, sy, 0, 0,
                        0, 0, sz, 0,
                        0, 0, 0, 1
                });
    }

    static matr4 translate(float tx, float ty, float tz) {
        return matr4(
                new float[16]{
                        1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        tx, ty, tz, 1
                });
    }

    static matr4 rotate(float angleRad) {
        const float a = angleRad;
        return matr4(
                new float[16]{
                        cosf(a), sinf(a), 0, 0,
                        -sinf(a), cosf(a), 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1
                });
    }
};

#endif //OPENGL_SAMPLE_ANDROID_MATR4_H
