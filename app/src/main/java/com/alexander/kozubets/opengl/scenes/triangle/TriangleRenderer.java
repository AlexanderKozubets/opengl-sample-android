package com.alexander.kozubets.opengl.scenes.triangle;


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

    @Override
    protected void construct() {
        constructNative();
    }

    @Override
    protected void init(int width, int height) {
        initNative(width, height);
    }

    @Override
    protected void draw() {
        drawNative();
    }

    native void constructNative();

    native void initNative(int width, int height);

    native void drawNative();

    //    @Override
//    protected native void construct();
//
//    @Override
//    protected native void init(int width, int height);
//
//    @Override
//    protected native void draw();
}
