package com.alexander.kozubets.opengl.utils;

import android.graphics.Bitmap;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.support.annotation.NonNull;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public abstract class CreateTexture implements Runnable {

    private Bitmap bitmap;

    public CreateTexture(@NonNull Bitmap bitmap) {
        this.bitmap = nonNull(bitmap);
    }

    @Override
    public void run() {
        int textureId = createTexture(bitmap);
        bitmap.recycle();
        onTextureCreated(textureId);
    }

    public abstract void onTextureCreated(int textureId);

    /**
     * Source http://www.learnopengles.com/android-lesson-four-introducing-basic-texturing/
     * <p>
     * Native implementation of {@link GLUtils#texImage2D(int, int, Bitmap, int)}
     * https://gitlab.com/SaberMod/pa-android-frameworks-base/blob/5e49b497ae2019586937aae0e8159292363728b5/core/jni/android/opengl/util.cpp
     * </p>
     */
    private int createTexture(@NonNull Bitmap bitmap) {
        final int textureId = genTextureId();
        boolean isValidTexId = textureId != 0;

        if (isValidTexId) {
            // Bind to the texture in OpenGL
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);

            // Set filtering
            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);

            // Load the bitmap into the bound texture.
            GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
        } else {
            throw new RuntimeException("Error loading texture.");
        }

        return textureId;
    }

    private int genTextureId() {
        return genTextureIds(1)[0];
    }

    private int[] genTextureIds(int n) {
        final int[] texturesId = new int[n];
        GLES20.glGenTextures(n, texturesId, 0);
        return texturesId;
    }
}