package com.alexander.kozubets.opengl.view;


import android.opengl.GLSurfaceView;
import android.os.Looper;
import android.support.annotation.NonNull;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public abstract class ShaderNativeRenderer implements GLSurfaceView.Renderer {

    @SuppressWarnings("unused")
    protected final ShaderRepository shaderRepository;

    @SuppressWarnings("unused")
    private final long nativePointer = 0;

    public ShaderNativeRenderer(@NonNull ShaderRepository shaderRepository) {
        this.shaderRepository = nonNull(shaderRepository);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        construct();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        init(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        draw();
    }

    protected void verifyNotMainThread() {
        if (Looper.getMainLooper().getThread() == Thread.currentThread()) {
            throw new RuntimeException("Method should NOT be called from Main Thread!");
        }
    }

    protected abstract void construct();

    protected abstract void init(int width, int height);

    protected abstract void draw();

    protected native void destroy();
}
