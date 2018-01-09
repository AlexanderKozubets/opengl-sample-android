package com.alexander.kozubets.opengl.renderer;


import android.support.annotation.NonNull;

import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;
import com.alexander.kozubets.opengl.view.ShaderRepository;

public class TextureRenderer extends ShaderNativeRenderer {

    static {
        System.loadLibrary("native-lib");
    }

    public TextureRenderer(@NonNull ShaderRepository shaderRepository) {
        super(shaderRepository);
    }

    public void onTextureLoaded(int textureId) {
        onTextureLoadedNative(textureId);
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

    private native void onTextureLoadedNative(int textureId);

    private native void drawNative();
}
