//
// Created by Alexander Kozubets on 11/19/17.
//

#include "GL2.h"
#include "../utils/gl_error_check.h"

void GL2::activeTexture(GLenum texture) {
    GL(glActiveTexture(texture));
}

void GL2::attachShader(GLuint program, GLuint shader) {
    GL(glAttachShader(program, shader));
}

void GL2::bindAttribLocation(GLuint program, GLuint index, const GLchar *name) {
    GL(glBindAttribLocation(program, index, name));
}

void GL2::bindBuffer(GLenum target, GLuint buffer) {
    GL(glBindBuffer(target, buffer));
}

void GL2::bindFramebuffer(GLenum target, GLuint framebuffer) {
    GL(glBindFramebuffer(target, framebuffer));
}

void GL2::bindRenderbuffer(GLenum target, GLuint renderbuffer) {
    GL(glBindRenderbuffer(target, renderbuffer));
}

void GL2::bindTexture(GLenum target, GLuint texture) {
    GL(glBindTexture(target, texture));
}

void GL2::blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    GL(glBlendColor(red, green, blue, alpha));
}

void GL2::blendEquation(GLenum mode) {
    GL(glBlendEquation(mode));
}

void GL2::blendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    GL(glBlendEquationSeparate(modeRGB, modeAlpha));
}

void GL2::blendFunc(GLenum sfactor, GLenum dfactor) {
    GL(glBlendFunc(sfactor, dfactor));
}

void GL2::blendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha,
                            GLenum dfactorAlpha) {
    GL(glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha));
}

void GL2::bufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    GL(glBufferData(target, size, data, usage));
}

void GL2::bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) {
    GL(glBufferSubData(target, offset, size, data));
}

GLenum GL2::checkFramebufferStatus(GLenum target) {
    GLenum res = glCheckFramebufferStatus(target);
    checkGlError("glCheckFramebufferStatus");
    return res;
}

void GL2::clear(GLbitfield mask) {
    GL(glClear(mask));
}

void GL2::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    GL(glClearColor(red, green, blue, alpha));
}

void GL2::clearDepthf(GLfloat d) {
    GL(glClearDepthf(d));
}

void GL2::clearStencil(GLint s) {
    GL(glClearStencil(s));
}

void GL2::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    GL(glColorMask(red, green, blue, alpha));
}

void GL2::compileShader(GLuint shader) {
    GL(glCompileShader(shader));
}

void GL2::compressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width,
                               GLsizei height, GLint border, GLsizei imageSize,
                               const void *data) {
    GL(glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data));
}

void GL2::compressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,
                                  GLsizei width, GLsizei height, GLenum format, GLsizei imageSize,
                                  const void *data) {
    GL(glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data));
}

void GL2::copyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y,
                         GLsizei width, GLsizei height, GLint border) {
    GL(glCopyTexImage2D(target, level, internalformat, x, y, width, height, border));
}

void
GL2::copyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y,
                       GLsizei width, GLsizei height) {
    GL(glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height));
}

GLuint GL2::createProgram(void) {
    GLuint res = glCreateProgram();
    checkGlError("glCreateProgram");
    return res;
}

GLuint GL2::createShader(GLenum type) {
    GLuint res = glCreateShader(type);
    checkGlError("glCreateShader");
    return res;
}

void GL2::cullFace(GLenum mode) {
    GL(glCullFace(mode));
}

void GL2::deleteBuffers(GLsizei n, const GLuint *buffers) {
    GL(glDeleteBuffers(n, buffers));
}

void GL2::deleteFramebuffers(GLsizei n, const GLuint *framebuffers) {
    GL(glDeleteFramebuffers(n, framebuffers));
}

void GL2::deleteProgram(GLuint program) {
    GL(glDeleteProgram(program));
}

void GL2::deleteRenderbuffers(GLsizei n, const GLuint *renderbuffers) {
    GL(glDeleteRenderbuffers(n, renderbuffers));
}

void GL2::deleteShader(GLuint shader) {
    GL(glDeleteShader(shader));
}

void GL2::deleteTextures(GLsizei n, const GLuint *textures) {
    GL(glDeleteTextures(n, textures));
}

void GL2::depthFunc(GLenum func) {
    GL(glDepthFunc(func));
}

void GL2::depthMask(GLboolean flag) {
    GL(glDepthMask(flag));
}

void GL2::depthRangef(GLfloat n, GLfloat f) {
    GL(glDepthRangef(n, f));
}

void GL2::detachShader(GLuint program, GLuint shader) {
    GL(glDetachShader(program, shader));
}

void GL2::disable(GLenum cap) {
    GL(glDisable(cap));
}

void GL2::disableVertexAttribArray(GLuint index) {
    GL(glDisableVertexAttribArray(index));
}

void GL2::drawArrays(GLenum mode, GLint first, GLsizei count) {
    GL(glDrawArrays(mode, first, count));
}

void GL2::drawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    GL(glDrawElements(mode, count, type, indices));
}

void GL2::enable(GLenum cap) {
    GL(glEnable(cap));
}

void GL2::enableVertexAttribArray(GLuint index) {
    GL(glEnableVertexAttribArray(index));
}

void GL2::finish(void) {
    GL(glFinish());
}

void GL2::flush(void) {
    GL(glFlush());
}

void GL2::framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget,
                                  GLuint renderbuffer) {
    GL(glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer));
}

void GL2::framebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
                               GLint level) {
    GL(glFramebufferTexture2D(target, attachment, textarget, texture, level));
}

void GL2::frontFace(GLenum mode) {
    GL(glFrontFace(mode));
}

void GL2::genBuffers(GLsizei n, GLuint *buffers) {
    GL(glGenBuffers(n, buffers));
}

void GL2::generateMipmap(GLenum target) {
    GL(glGenerateMipmap(target));
}

void GL2::genFramebuffers(GLsizei n, GLuint *framebuffers) {
    GL(glGenFramebuffers(n, framebuffers));
}

void GL2::genRenderbuffers(GLsizei n, GLuint *renderbuffers) {
    GL(glGenRenderbuffers(n, renderbuffers));
}

void GL2::genTextures(GLsizei n, GLuint *textures) {
    GL(glGenTextures(n, textures));
}

void
GL2::getActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size,
                     GLenum *type, GLchar *name) {
    GL(glGetActiveAttrib(program, index, bufSize, length, size, type, name));
}

void
GL2::getActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size,
                      GLenum *type, GLchar *name) {
    GL(glGetActiveUniform(program, index, bufSize, length, size, type, name));
}

void GL2::getAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) {
    GL(glGetAttachedShaders(program, maxCount, count, shaders));
}

GLint GL2::getAttribLocation(GLuint program, const GLchar *name) {
    GLint res = glGetAttribLocation(program, name);
    checkGlError("glGetAttribLocation");
    return res;
}

void GL2::getBooleanv(GLenum pname, GLboolean *data) {
    GL(glGetBooleanv(pname, data));
}

void GL2::getBufferParameteriv(GLenum target, GLenum pname, GLint *params) {
    GL(glGetBufferParameteriv(target, pname, params));
}

GLenum GL2::getError(void) {
    return glGetError();
}

void GL2::getFloatv(GLenum pname, GLfloat *data) {
    GL(glGetFloatv(pname, data));
}

void GL2::getFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname,
                                              GLint *params) {
    GL(glGetFramebufferAttachmentParameteriv(target, attachment, pname, params));
}

void GL2::getIntegerv(GLenum pname, GLint *data) {
    GL(glGetIntegerv(pname, data));
}

void GL2::getProgramiv(GLuint program, GLenum pname, GLint *params) {
    GL(glGetProgramiv(program, pname, params));
}

void GL2::getProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    GL(glGetProgramInfoLog(program, bufSize, length, infoLog));
}

void GL2::getRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params) {
    GL(glGetRenderbufferParameteriv(target, pname, params));
}

void GL2::getShaderiv(GLuint shader, GLenum pname, GLint *params) {
    GL(glGetShaderiv(shader, pname, params));
}

void GL2::getShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog) {
    GL(glGetShaderInfoLog(shader, bufSize, length, infoLog));
}

void GL2::getShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range,
                                   GLint *precision) {
    GL(glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision));
}

void GL2::getShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) {
    GL(glGetShaderSource(shader, bufSize, length, source));
}

const GLubyte *GL2::getString(GLenum name) {
    return glGetString(name);
}

void GL2::getTexParameterfv(GLenum target, GLenum pname, GLfloat *params) {
    GL(glGetTexParameterfv(target, pname, params));
}

void GL2::getTexParameteriv(GLenum target, GLenum pname, GLint *params) {
    GL(glGetTexParameteriv(target, pname, params));
}

void GL2::getUniformfv(GLuint program, GLint location, GLfloat *params) {
    GL(glGetUniformfv(program, location, params));
}

void GL2::getUniformiv(GLuint program, GLint location, GLint *params) {
    GL(glGetUniformiv(program, location, params));
}

GLint GL2::getUniformLocation(GLuint program, const GLchar *name) {
    GLint res = glGetUniformLocation(program, name);
    checkGlError("glGetUniformLocation");
    return res;
}

void GL2::getVertexAttribfv(GLuint index, GLenum pname, GLfloat *params) {
    GL(glGetVertexAttribfv(index, pname, params));
}

void GL2::getVertexAttribiv(GLuint index, GLenum pname, GLint *params) {
    GL(glGetVertexAttribiv(index, pname, params));
}

void GL2::getVertexAttribPointerv(GLuint index, GLenum pname, void **pointer) {
    GL(glGetVertexAttribPointerv(index, pname, pointer));
}

void GL2::hint(GLenum target, GLenum mode) {
    GL(glHint(target, mode));
}

GLboolean GL2::isBuffer(GLuint buffer) {
    GLboolean res = glIsBuffer(buffer);
    checkGlError("glIsBuffer");
    return res;
}

GLboolean GL2::isEnabled(GLenum cap) {
    GLboolean res = glIsEnabled(cap);
    checkGlError("glIsEnabled");
    return res;
}

GLboolean GL2::isFramebuffer(GLuint framebuffer) {
    GLboolean res = glIsFramebuffer(framebuffer);
    checkGlError("glIsFramebuffer");
    return res;
}

GLboolean GL2::isProgram(GLuint program) {
    GLboolean res = glIsProgram(program);
    checkGlError("glIsProgram");
    return res;
}

GLboolean GL2::isRenderbuffer(GLuint renderbuffer) {
    GLboolean res = glIsRenderbuffer(renderbuffer);
    checkGlError("glIsRenderbuffer");
    return res;
}

GLboolean GL2::isShader(GLuint shader) {
    GLboolean res = glIsShader(shader);
    checkGlError("glIsShader");
    return res;
}

GLboolean GL2::isTexture(GLuint texture) {
    GLboolean res = glIsTexture(texture);
    checkGlError("glIsTexture");
    return res;
}

void GL2::lineWidth(GLfloat width) {
    GL(glLineWidth(width));
}

void GL2::linkProgram(GLuint program) {
    GL(glLinkProgram(program));
}

void GL2::pixelStorei(GLenum pname, GLint param) {
    GL(glPixelStorei(pname, param));
}

void GL2::polygonOffset(GLfloat factor, GLfloat units) {
    GL(glPolygonOffset(factor, units));
}

void GL2::readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
                     void *pixels) {
    GL(glReadPixels(x, y, width, height, format, type, pixels));
}

void GL2::releaseShaderCompiler(void) {
    GL(glReleaseShaderCompiler());
}

void GL2::renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    GL(glRenderbufferStorage(target, internalformat, width, height));
}

void GL2::sampleCoverage(GLfloat value, GLboolean invert) {
    GL(glSampleCoverage(value, invert));
}

void GL2::scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    GL(glScissor(x, y, width, height));
}

void
GL2::shaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary,
                  GLsizei length) {
    GL(glShaderBinary(count, shaders, binaryformat, binary, length));
}

void
GL2::shaderSource(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length) {
    GL(glShaderSource(shader, count, string, length));
}

void GL2::stencilFunc(GLenum func, GLint ref, GLuint mask) {
    GL(glStencilFunc(func, ref, mask));
}

void GL2::stencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    GL(glStencilFuncSeparate(face, func, ref, mask));
}

void GL2::stencilMask(GLuint mask) {
    GL(glStencilMask(mask));
}

void GL2::stencilMaskSeparate(GLenum face, GLuint mask) {
    GL(glStencilMaskSeparate(face, mask));
}

void GL2::stencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    GL(glStencilOp(fail, zfail, zpass));
}

void GL2::stencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    GL(glStencilOpSeparate(face, sfail, dpfail, dppass));
}

void
GL2::texImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
                GLint border, GLenum format, GLenum type, const void *pixels) {
    GL(glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels));
}

void GL2::texParameterf(GLenum target, GLenum pname, GLfloat param) {
    GL(glTexParameterf(target, pname, param));
}

void GL2::texParameterfv(GLenum target, GLenum pname, const GLfloat *params) {
    GL(glTexParameterfv(target, pname, params));
}

void GL2::texParameteri(GLenum target, GLenum pname, GLint param) {
    GL(glTexParameteri(target, pname, param));
}

void GL2::texParameteriv(GLenum target, GLenum pname, const GLint *params) {
    GL(glTexParameteriv(target, pname, params));
}

void GL2::texSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                        GLsizei height, GLenum format, GLenum type, const void *pixels) {
    GL(glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels));
}

void GL2::uniform1f(GLint location, GLfloat v0) {
    GL(glUniform1f(location, v0));
}

void GL2::uniform1fv(GLint location, GLsizei count, const GLfloat *value) {
    GL(glUniform1fv(location, count, value));
}

void GL2::uniform1i(GLint location, GLint v0) {
    GL(glUniform1i(location, v0));
}

void GL2::uniform1iv(GLint location, GLsizei count, const GLint *value) {
    GL(glUniform1iv(location, count, value));
}

void GL2::uniform2f(GLint location, GLfloat v0, GLfloat v1) {
    GL(glUniform2f(location, v0, v1));
}

void GL2::uniform2fv(GLint location, GLsizei count, const GLfloat *value) {
    GL(glUniform2fv(location, count, value));
}

void GL2::uniform2i(GLint location, GLint v0, GLint v1) {
    GL(glUniform2i(location, v0, v1));
}

void GL2::uniform2iv(GLint location, GLsizei count, const GLint *value) {
    GL(glUniform2iv(location, count, value));
}

void GL2::uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    GL(glUniform3f(location, v0, v1, v2));
}

void GL2::uniform3fv(GLint location, GLsizei count, const GLfloat *value) {
    GL(glUniform3fv(location, count, value));
}

void GL2::uniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    GL(glUniform3i(location, v0, v1, v2));
}

void GL2::uniform3iv(GLint location, GLsizei count, const GLint *value) {
    GL(glUniform3iv(location, count, value));
}

void GL2::uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    GL(glUniform4f(location, v0, v1, v2, v3));
}

void GL2::uniform4fv(GLint location, GLsizei count, const GLfloat *value) {
    GL(glUniform4fv(location, count, value));
}

void GL2::uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    GL(glUniform4i(location, v0, v1, v2, v3));
}

void GL2::uniform4iv(GLint location, GLsizei count, const GLint *value) {
    GL(glUniform4iv(location, count, value));
}

void
GL2::uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    GL(glUniformMatrix2fv(location, count, transpose, value));
}

void
GL2::uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    GL(glUniformMatrix3fv(location, count, transpose, value));
}

void
GL2::uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) {
    GL(glUniformMatrix4fv(location, count, transpose, value));
}

void GL2::useProgram(GLuint program) {
    GL(glUseProgram(program));
}

void GL2::validateProgram(GLuint program) {
    GL(glValidateProgram(program));
}

void GL2::vertexAttrib1f(GLuint index, GLfloat x) {
    GL(glVertexAttrib1f(index, x));
}

void GL2::vertexAttrib1fv(GLuint index, const GLfloat *v) {
    GL(glVertexAttrib1fv(index, v));
}

void GL2::vertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    GL(glVertexAttrib2f(index, x, y));
}

void GL2::vertexAttrib2fv(GLuint index, const GLfloat *v) {
    GL(glVertexAttrib2fv(index, v));
}

void GL2::vertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    GL(glVertexAttrib3f(index, x, y, z));
}

void GL2::vertexAttrib3fv(GLuint index, const GLfloat *v) {
    GL(glVertexAttrib3fv(index, v));
}

void GL2::vertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    GL(glVertexAttrib4f(index, x, y, z, w));
}

void GL2::vertexAttrib4fv(GLuint index, const GLfloat *v) {
    GL(glVertexAttrib4fv(index, v));
}

void GL2::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                              GLsizei stride, const void *pointer) {
    GL(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
}

void GL2::viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    GL(glViewport(x, y, width, height));
}
