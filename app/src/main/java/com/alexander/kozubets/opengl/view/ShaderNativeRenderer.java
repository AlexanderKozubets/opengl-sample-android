package com.alexander.kozubets.opengl.view;


import android.opengl.GLSurfaceView;
import android.support.annotation.NonNull;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public abstract class ShaderNativeRenderer implements GLSurfaceView.Renderer {

    @SuppressWarnings("unused")
    private ShaderRepository shaderRepository;

    @SuppressWarnings("unused")
    private final long nativePointer = 0;

    public ShaderNativeRenderer(@NonNull ShaderRepository shaderRepository) {
        this.shaderRepository = nonNull(shaderRepository);
        construct();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        init(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        draw();
    }

    protected abstract void construct();

    protected abstract void init(int width, int height);

    protected abstract void draw();

    protected native void destroy();
}
