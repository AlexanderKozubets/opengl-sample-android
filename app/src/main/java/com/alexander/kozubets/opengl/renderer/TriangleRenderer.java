package com.alexander.kozubets.opengl.renderer;


import android.support.annotation.NonNull;

import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;
import com.alexander.kozubets.opengl.view.ShaderRepository;

public class TriangleRenderer extends ShaderNativeRenderer {

    static {
        System.loadLibrary("native-lib");
    }

    public TriangleRenderer(@NonNull ShaderRepository shaderRepository) {
        super(shaderRepository);
    }

    public void setMode(int mode) {
        setModeNative(mode);
    }

    @Override
    protected void construct() {
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

    private native void drawNative();
}
