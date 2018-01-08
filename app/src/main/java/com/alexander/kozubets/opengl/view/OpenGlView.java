package com.alexander.kozubets.opengl.view;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.support.annotation.Nullable;
import android.util.AttributeSet;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenGlView extends GLSurfaceView {

    private RendererWrapper renderer;

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
    public void setRenderer(final Renderer renderer) {
        // Hack to be able to change renderers at the runtime.
        if (this.renderer == null) {
            this.renderer = new RendererWrapper(renderer);
            super.setRenderer(this.renderer);
        } else {
            this.queueEvent(new Runnable() {
                @Override
                public void run() {
                    OpenGlView.this.renderer.setRenderer(renderer);
                }
            });
        }
    }

    private static final class RendererWrapper implements Renderer {

        private Renderer renderer;

        private final LastConfig lastConfig = new LastConfig();

        public RendererWrapper(@Nullable Renderer renderer) {
            this.renderer = renderer;
        }

        /**
         * Should be called from GL thread.
         */
        public void setRenderer(Renderer renderer) {
            if (this.renderer instanceof ShaderNativeRenderer) {
                ((ShaderNativeRenderer) this.renderer).destroy();
            }
            this.renderer = renderer;

            // As these callbacks won't be called by the GCSurfaceView we call them manually
            // to initialize renderer.
            this.renderer.onSurfaceCreated(null, lastConfig.config);
            this.renderer.onSurfaceChanged(null, lastConfig.width, lastConfig.height);
        }

        @Override
        public void onSurfaceCreated(@Deprecated GL10 gl, EGLConfig config) {
            if (renderer != null) {
                renderer.onSurfaceCreated(gl, config);
            }
            lastConfig.config = config;
        }

        @Override
        public void onSurfaceChanged(@Deprecated GL10 gl, int width, int height) {
            if (renderer != null) {
                renderer.onSurfaceChanged(gl, width, height);
            }
            lastConfig.width = width;
            lastConfig.height = height;
        }

        @Override
        public void onDrawFrame(@Deprecated GL10 gl) {
            if (renderer != null) {
                renderer.onDrawFrame(gl);
            }
        }

        private static class LastConfig {
            EGLConfig config;

            int width;

            int height;
        }
    }
}
