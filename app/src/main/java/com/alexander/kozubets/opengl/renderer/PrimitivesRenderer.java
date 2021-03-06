package com.alexander.kozubets.opengl.renderer;


import android.support.annotation.NonNull;

import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;
import com.alexander.kozubets.opengl.view.ShaderRepository;

public class PrimitivesRenderer extends ShaderNativeRenderer {

    static {
        System.loadLibrary("native-lib");
    }

    public PrimitivesRenderer(@NonNull ShaderRepository shaderRepository) {
        super(shaderRepository);
    }

    public void setMode(int mode) {
        verifyNotMainThread();
        setModeNative(mode);
    }

    public void setVerticesCount(int count) {
        verifyNotMainThread();
        setVerticesCountNative(count);
    }

    @Override
    protected void construct() {
        verifyNotMainThread();
        constructNative(shaderRepository);
    }

    @Override
    protected void init(int width, int height) {
        initNative(width, height);
    }

    @Override
    protected void draw() {
        drawNative();
    }

    private native void constructNative(ShaderRepository shaderRepository);

    private native void initNative(int width, int height);

    private native void setModeNative(int mode);

    private native void setVerticesCountNative(int count);

    private native void drawNative();
}
