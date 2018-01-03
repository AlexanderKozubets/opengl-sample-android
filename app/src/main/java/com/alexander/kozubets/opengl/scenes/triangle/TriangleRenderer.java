package com.alexander.kozubets.opengl.scenes.triangle;


import android.support.annotation.NonNull;

import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;
import com.alexander.kozubets.opengl.view.ShaderRepository;

public class TriangleRenderer extends ShaderNativeRenderer {

    public TriangleRenderer(@NonNull ShaderRepository shaderRepository) {
        super(shaderRepository);
    }

    @Override
    protected native void construct();

    @Override
    protected native void init(int width, int height);

    @Override
    protected native void draw();
}
