package com.alexander.kozubets.opengl.view;


import android.opengl.GLSurfaceView;
import android.support.annotation.NonNull;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public class NativeRenderer implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("native-lib");
    }

    private static NativeRenderer renderer;

    public static NativeRenderer get(@NonNull ShaderRepository shaderRepository) {
        if (renderer == null) {
            renderer = new NativeRenderer(shaderRepository);
        }
        return renderer;
    }

    private ShaderRepository shaderRepository;

    private NativeRenderer(@NonNull ShaderRepository shaderRepository) {
        this.shaderRepository = nonNull(shaderRepository);
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        init(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        draw();
    }

    public static native void init(int width, int height);

    public static native void draw();
}
