#ifndef OPENGL_SAMPLE_ANDROID_LOG_MACROS_H
#define OPENGL_SAMPLE_ANDROID_LOG_MACROS_H

#include <android/log.h>

#define DEBUG true

#ifdef DEBUG
#include <stdlib.h>
#endif

#define  LOG_TAG    "OpenGL ES 2.0 Sample"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__); \
                    if (DEBUG) { \
                        abort(); \
                    }

#endif //OPENGL_SAMPLE_ANDROID_LOG_MACROS_H
