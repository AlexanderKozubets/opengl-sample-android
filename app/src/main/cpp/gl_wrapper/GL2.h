//
// Created by Alexander Kozubets on 11/19/17.
//

#ifndef OPENGL_SAMPLE_ANDROID_GL2_H
#define OPENGL_SAMPLE_ANDROID_GL2_H

#include <GLES2/gl2.h>

class GL2 {
public:
    static void activeTexture(GLenum texture);
    static void attachShader(GLuint program, GLuint shader);
    static void bindAttribLocation(GLuint program, GLuint index, const GLchar *name);
    static void bindBuffer(GLenum target, GLuint buffer);
    static void bindFramebuffer(GLenum target, GLuint framebuffer);
    static void bindRenderbuffer(GLenum target, GLuint renderbuffer);
    static void bindTexture(GLenum target, GLuint texture);
    static void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    static void blendEquation(GLenum mode);
    static void blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
    static void blendFunc(GLenum sfactor, GLenum dfactor);
    static void blendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
                                  GLenum dfactorAlpha);
    static void bufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
    static void bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
    static GLenum checkFramebufferStatus(GLenum target);
    static void clear(GLbitfield mask);
    static void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    static void clearDepthf(GLfloat d);
    static void clearStencil(GLint s);
    static void colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    static void compileShader(GLuint shader);
    static void compressedTexImage2D(GLenum target, GLint level, GLenum internalformat,
                                     GLsizei width, GLsizei height, GLint border, GLsizei imageSize,
                                     const void *data);
    static void compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                                        GLsizei width, GLsizei height, GLenum format,
                                        GLsizei imageSize, const void *data);
    static void copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
                               GLsizei width, GLsizei height, GLint border);
    static void copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x,
                                  GLint y, GLsizei width, GLsizei height);
    static GLuint createProgram (void);
    static GLuint createShader (GLenum type);
    static void cullFace (GLenum mode);
    static void deleteBuffers (GLsizei n, const GLuint *buffers);
    static void deleteFramebuffers (GLsizei n, const GLuint *framebuffers);
    static void deleteProgram (GLuint program);
    static void deleteRenderbuffers (GLsizei n, const GLuint *renderbuffers);
    static void deleteShader (GLuint shader);
    static void deleteTextures (GLsizei n, const GLuint *textures);
    static void depthFunc (GLenum func);
    static void depthMask (GLboolean flag);
    static void depthRangef (GLfloat n, GLfloat f);
    static void detachShader (GLuint program, GLuint shader);
    static void disable (GLenum cap);
    static void disableVertexAttribArray (GLuint index);
    static void drawArrays (GLenum mode, GLint first, GLsizei count);
    static void drawElements (GLenum mode, GLsizei count, GLenum type, const void *indices);
    static void enable (GLenum cap);
    static void enableVertexAttribArray (GLuint index);
    static void finish (void);
    static void flush (void);
    static void framebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
    static void framebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    static void frontFace (GLenum mode);
    static void genBuffers (GLsizei n, GLuint *buffers);
    static void generateMipmap (GLenum target);
    static void genFramebuffers (GLsizei n, GLuint *framebuffers);
    static void genRenderbuffers (GLsizei n, GLuint *renderbuffers);
    static void genTextures (GLsizei n, GLuint *textures);
    static void getActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
    static void getActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
    static void getAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
    static GLint getAttribLocation (GLuint program, const GLchar *name);
    static void getBooleanv (GLenum pname, GLboolean *data);
    static void getBufferParameteriv (GLenum target, GLenum pname, GLint *params);
    static GLenum getError (void);
    static void getFloatv (GLenum pname, GLfloat *data);
    static void getFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
    static void getIntegerv (GLenum pname, GLint *data);
    static void getProgramiv (GLuint program, GLenum pname, GLint *params);
    static void getProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    static void getRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
    static void getShaderiv (GLuint shader, GLenum pname, GLint *params);
    static void getShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
    static void getShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
    static void getShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
    static const GLubyte *getString (GLenum name);
    static void getTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
    static void getTexParameteriv (GLenum target, GLenum pname, GLint *params);
    static void getUniformfv (GLuint program, GLint location, GLfloat *params);
    static void getUniformiv (GLuint program, GLint location, GLint *params);
    static GLint getUniformLocation (GLuint program, const GLchar *name);
    static void getVertexAttribfv (GLuint index, GLenum pname, GLfloat *params);
    static void getVertexAttribiv (GLuint index, GLenum pname, GLint *params);
    static void getVertexAttribPointerv (GLuint index, GLenum pname, void **pointer);
    static void hint (GLenum target, GLenum mode);
    static GLboolean isBuffer (GLuint buffer);
    static GLboolean isEnabled (GLenum cap);
    static GLboolean isFramebuffer (GLuint framebuffer);
    static GLboolean isProgram (GLuint program);
    static GLboolean isRenderbuffer (GLuint renderbuffer);
    static GLboolean isShader (GLuint shader);
    static GLboolean isTexture (GLuint texture);
    static void lineWidth (GLfloat width);
    static void linkProgram (GLuint program);
    static void pixelStorei (GLenum pname, GLint param);
    static void polygonOffset (GLfloat factor, GLfloat units);
    static void readPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
    static void releaseShaderCompiler (void);
    static void renderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    static void sampleCoverage (GLfloat value, GLboolean invert);
    static void scissor (GLint x, GLint y, GLsizei width, GLsizei height);
    static void shaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
    static void shaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    static void stencilFunc (GLenum func, GLint ref, GLuint mask);
    static void stencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask);
    static void stencilMask (GLuint mask);
    static void stencilMaskSeparate (GLenum face, GLuint mask);
    static void stencilOp (GLenum fail, GLenum zfail, GLenum zpass);
    static void stencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
    static void texImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
    static void texParameterf (GLenum target, GLenum pname, GLfloat param);
    static void texParameterfv (GLenum target, GLenum pname, const GLfloat *params);
    static void texParameteri (GLenum target, GLenum pname, GLint param);
    static void texParameteriv(GLenum target, GLenum pname, const GLint *params);
    static void texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                              GLsizei width, GLsizei height, GLenum format, GLenum type,
                              const void *pixels);
    static void uniform1f(GLint location, GLfloat v0);
    static void uniform1fv(GLint location, GLsizei count, const GLfloat *value);
    static void uniform1i(GLint location, GLint v0);
    static void uniform1iv(GLint location, GLsizei count, const GLint *value);
    static void uniform2f(GLint location, GLfloat v0, GLfloat v1);
    static void uniform2fv(GLint location, GLsizei count, const GLfloat *value);
    static void uniform2i(GLint location, GLint v0, GLint v1);
    static void uniform2iv(GLint location, GLsizei count, const GLint *value);
    static void uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    static void uniform3fv(GLint location, GLsizei count, const GLfloat *value);
    static void uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
    static void uniform3iv(GLint location, GLsizei count, const GLint *value);
    static void uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    static void uniform4fv(GLint location, GLsizei count, const GLfloat *value);
    static void uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
    static void uniform4iv(GLint location, GLsizei count, const GLint *value);
    static void uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose,
                                 const GLfloat *value);
    static void uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                                 const GLfloat *value);
    static void uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                                 const GLfloat *value);
    static void useProgram(GLuint program);
    static void validateProgram(GLuint program);
    static void vertexAttrib1f(GLuint index, GLfloat x);
    static void vertexAttrib1fv(GLuint index, const GLfloat *v);
    static void vertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
    static void vertexAttrib2fv(GLuint index, const GLfloat *v);
    static void vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
    static void vertexAttrib3fv(GLuint index, const GLfloat *v);
    static void vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    static void vertexAttrib4fv(GLuint index, const GLfloat *v);
    static void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                    GLsizei stride, const void *pointer);
    static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
};

#endif //OPENGL_SAMPLE_ANDROID_GL2_H
