//
// Created by Alexander Kozubets on 11/22/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_MATR4_H
#define OPENGL_SAMPLE_ANDROID_MATR4_H

#include <string.h>

class matr4 {
private:
    float m[16];

public:

    matr4(float matrix[16]) {
        size_t sz1 = sizeof(matrix);
        size_t sz2 = sizeof(float);
        size_t length = sz1 / sz2;
        memcpy(&m, matrix, 16 * sizeof(float));
    }

    ~matr4() {
    }

    float* ptr() {
        return m;
    }

    static matr4 identity() {
        return matr4(
                new float[16] {
                        1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1
                });
    }

    static matr4 scale(float sx, float sy, float sz) {
        return matr4(
                new float[16] {
                        sx, 0,  0,  0,
                        0,  sy, 0,  0,
                        0,  0,  sz, 0,
                        0,  0,  0,  1
                });
    }

    static matr4 translate(float tx, float ty, float tz) {
        return matr4(
                new float[16] {
                        1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        tx,ty,tz,1
                });
    }
};

#endif //OPENGL_SAMPLE_ANDROID_MATR4_H
