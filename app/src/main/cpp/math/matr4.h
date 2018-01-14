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

    const float * ptr() const {
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
                        sx, 0, 0, 0,
                        0, sy, 0, 0,
                        0, 0, sz, 0,
                        tx, ty, tz, 1
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

    static matr4 rotateX(float angleRad) {
        const float a = angleRad;
        return matr4(
                new float[16]{
                        1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, cosf(a), sinf(a), 0,
                        0, -sinf(a), cosf(a), 1
                });
    }

    static matr4 rotateY(float angleRad) {
        const float a = angleRad;
        return matr4(
                new float[16]{
                        cosf(a), 0, -sinf(a), 0,
                        0, 1, 0, 0,
                        sinf(a), 0, cosf(a), 0,
                        0, 0, 0, 1
                });
    }

    static matr4 rotateZ(float angleRad) {
        const float a = angleRad;
        return matr4(
                new float[16]{
                        cosf(a), sinf(a), 0, 0,
                        -sinf(a), cosf(a), 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1
                });
    }

    // friends defined inside class body are inline and are hidden from non-ADL lookup
    friend matr4 operator*(matr4 lhs, const matr4 &rhs) {
        float* m = new float[16]{0};
        const float *l = lhs.ptr();
        const float *r = rhs.ptr();

        m[0] = l[0] * r[0] + l[1] * r[4] + l[2] * r[8] + l[3] * r[12];
        m[1] = l[0] * r[1] + l[1] * r[5] + l[2] * r[9] + l[3] * r[13];
        m[2] = l[0] * r[2] + l[1] * r[6] + l[2] * r[10] + l[3] * r[14];
        m[3] = l[0] * r[3] + l[1] * r[7] + l[2] * r[11] + l[3] * r[15];

        m[4] = l[4] * r[0] + l[5] * r[4] + l[6] * r[8] + l[7] * r[12];
        m[5] = l[4] * r[1] + l[5] * r[5] + l[6] * r[9] + l[7] * r[13];
        m[6] = l[4] * r[2] + l[5] * r[6] + l[6] * r[10] + l[7] * r[14];
        m[7] = l[4] * r[3] + l[5] * r[7] + l[6] * r[11] + l[7] * r[15];

        m[8] = l[8] * r[0] + l[9] * r[4] + l[10] * r[8] + l[11] * r[12];
        m[9] = l[8] * r[1] + l[9] * r[5] + l[10] * r[9] + l[11] * r[13];
        m[10] = l[8] * r[2] + l[9] * r[6] + l[10] * r[10] + l[11] * r[14];
        m[11] = l[8] * r[3] + l[9] * r[7] + l[10] * r[11] + l[11] * r[15];

        m[12] = l[12] * r[0] + l[13] * r[4] + l[14] * r[8] + l[15] * r[12];
        m[13] = l[12] * r[1] + l[13] * r[5] + l[14] * r[9] + l[15] * r[13];
        m[14] = l[12] * r[2] + l[13] * r[6] + l[14] * r[10] + l[15] * r[14];
        m[15] = l[12] * r[3] + l[13] * r[7] + l[14] * r[11] + l[15] * r[15];

        return matr4(m); // return the result by value (uses move constructor)
    }
};

#endif //OPENGL_SAMPLE_ANDROID_MATR4_H
