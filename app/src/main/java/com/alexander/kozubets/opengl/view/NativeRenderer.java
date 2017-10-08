package com.alexander.kozubets.opengl.view;


import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class NativeRenderer implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("native-lib");
    }

    private static NativeRenderer renderer;

    public static NativeRenderer get() {
        if (renderer == null) {
            renderer = new NativeRenderer();
        }
        return renderer;
    }

    private NativeRenderer() {
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
