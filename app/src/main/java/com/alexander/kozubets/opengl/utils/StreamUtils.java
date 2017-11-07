package com.alexander.kozubets.opengl.utils;


import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import com.alexander.kozubets.opengl.sample.BuildConfig;

import java.io.Closeable;
import java.io.IOException;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public final class StreamUtils {

    public static void close(@Nullable Closeable resource) {
        if (resource != null) {
            try {
                resource.close();
            } catch (IOException e) {
                if (BuildConfig.DEBUG) {
                    log(e);
                }
            }
        }
    }

    public static void log(@NonNull Throwable throwable) {
        if (BuildConfig.DEBUG) {
            nonNull(throwable).printStackTrace();
        }
    }

    private StreamUtils() throws IllegalAccessException {
        throw new IllegalAccessException();
    }
}
