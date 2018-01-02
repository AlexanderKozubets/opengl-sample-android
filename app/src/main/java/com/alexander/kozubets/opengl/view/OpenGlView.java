package com.alexander.kozubets.opengl.view;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class OpenGlView extends GLSurfaceView {

    private Renderer renderer;

    public OpenGlView(Context context) {
        super(context);
        init(context, null);
    }

    public OpenGlView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context, attrs);
    }

    private void init(Context context, AttributeSet attrs) {
        setEGLContextFactory(new ContextFactory());
    }

    @Override
    public void setRenderer(Renderer renderer) {
        super.setRenderer(renderer);
        if (this.renderer instanceof ShaderNativeRenderer) {
            ((ShaderNativeRenderer) this.renderer).destroy();
        }
        this.renderer = renderer;
    }
}
