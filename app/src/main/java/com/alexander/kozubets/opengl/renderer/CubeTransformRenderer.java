package com.alexander.kozubets.opengl.renderer;


import android.support.annotation.NonNull;

import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;
import com.alexander.kozubets.opengl.view.ShaderRepository;

public class CubeTransformRenderer extends ShaderNativeRenderer {

    static {
        System.loadLibrary("native-lib");
    }

    public CubeTransformRenderer(@NonNull ShaderRepository shaderRepository) {
        super(shaderRepository);
    }

    public void setRotationX(float angleDegrees) {
        verifyNotMainThread();
        setRotationXNative(angleDegrees);
    }

    public void setRotationY(float angleDegrees) {
        verifyNotMainThread();
        setRotationYNative(angleDegrees);
    }

    public void setRotationZ(float angleDegrees) {
        verifyNotMainThread();
        setRotationZNative(angleDegrees);
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

    private native void setRotationXNative(float angleDegrees);

    private native void setRotationYNative(float angleDegrees);

    private native void setRotationZNative(float angleDegrees);

    private native void drawNative();
}
