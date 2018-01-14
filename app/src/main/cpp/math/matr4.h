//
// Created by Alexander Kozubets on 11/22/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_MATR4_H
#define OPENGL_SAMPLE_ANDROID_MATR4_H

#include <string.h>
#include <cmath>
#include <utils/log_macros.h>

class matr4;
static void logMatrix(const char *name, matr4 m);

class matr4 {
private:
    float m[16];

public:

    matr4(float matrix[16]) {
        memcpy(&m, matrix, 16 * sizeof(float));
    }

    ~matr4() {
    }

    const float *ptr() const {
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

    static matr4 frustum(float left, float right, float bottom, float top, float near, float far) {
        float r_width = 1.0f / (right - left);
        float r_height = 1.0f / (top - bottom);
        float r_depth = 1.0f / (near - far);

        float x = 2.0f * (near * r_width);
        float y = 2.0f * (near * r_height);

        float A = (right + left) * r_width;
        float B = (top + bottom) * r_height;
        float C = (far + near) * r_depth;
        float D = 2.0f * (far * near * r_depth);

        return matr4(
                new float[16]{
                        x, 0, 0, 0,
                        0, y, 0, 0,
                        A, B, C, -1.0f,
                        0, 0, D, 0
                });
    }
    static matr4 lookAt(float eyeX, float eyeY, float eyeZ,
                        float centerX, float centerY, float centerZ,
                        float upX, float upY, float upZ) {

        // See the OpenGL GLUT documentation for gluLookAt for a description
        // of the algorithm. We implement it in a straightforward way:

        float fx = centerX - eyeX;
        float fy = centerY - eyeY;
        float fz = centerZ - eyeZ;

        // Normalize f
        float rlf = 1.0f / length(fx, fy, fz);
        fx *= rlf;
        fy *= rlf;
        fz *= rlf;

        // compute s = f x up (x means "cross product")
        float sx = fy * upZ - fz * upY;
        float sy = fz * upX - fx * upZ;
        float sz = fx * upY - fy * upX;

        // and normalize s
        float rls = 1.0f / length(sx, sy, sz);
        sx *= rls;
        sy *= rls;
        sz *= rls;

        // compute u = s x f
        float ux = sy * fz - sz * fy;
        float uy = sz * fx - sx * fz;
        float uz = sx * fy - sy * fx;

        const matr4 m = matr4(
                new float[16]{
                        sx, ux, -fx, 0,
                        sy, uy, -fy, 0,
                        sz, uz, -fz, 0,
                        0, 0, 0, 1
                });
        
        const matr4 t = translate(-eyeX, -eyeY, -eyeZ);

        const matr4 result = t * m;

        logMatrix("m", m);
        logMatrix("Translate", t);
        logMatrix("Result", result);

        return result;
    }

    static float length(float x, float y, float z) {
        return (float) sqrt(x * x + y * y + z * z);
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
        float *m = new float[16]{0};
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

static void logMatrix(const char *name, matr4 m) {
    const float *p = m.ptr();
    LOGI("Matrix %s: "
                 "\n[%2.1f] [%2.1f] [%2.1f] [%2.1f] "
                 "\n[%2.1f] [%2.1f] [%2.1f] [%2.1f] "
                 "\n[%2.1f] [%2.1f] [%2.1f] [%2.1f] "
                 "\n[%2.1f] [%2.1f] [%2.1f] [%2.1f] \n",
         name,
         p[0], p[1], p[2], p[3],
         p[4], p[5], p[6], p[7],
         p[8], p[9], p[10], p[11],
         p[12], p[13], p[14], p[15]);
}

#endif //OPENGL_SAMPLE_ANDROID_MATR4_H
