package com.alexander.kozubets.opengl.view;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Looper;
import android.support.annotation.MainThread;
import android.support.annotation.Nullable;
import android.support.annotation.WorkerThread;
import android.util.AttributeSet;

import java.util.logging.Handler;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenGlView extends GLSurfaceView {

    private RendererWrapper rendererWrapper;

    private OnRendererChangeListener rendererChangeListener;

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
        if (this.rendererWrapper == null) {
            this.rendererWrapper = new RendererWrapper(renderer);
            super.setRenderer(this.rendererWrapper);
            this.queueEvent(new Runnable() {
                @Override
                public void run() {
                    // notify only after renderer is initialized
                    notifyRendererChanged(renderer);
                }
            });
        } else {
            this.queueEvent(new Runnable() {
                @Override
                public void run() {
                    OpenGlView.this.rendererWrapper.setRenderer(renderer);
                    notifyRendererChanged(renderer);
                }
            });
        }
    }

    public void setOnRendererChangeListener(OnRendererChangeListener rendererChangeListener) {
        this.rendererChangeListener = rendererChangeListener;
    }

    @WorkerThread
    private void notifyRendererChanged(final Renderer renderer) {
        if (rendererChangeListener != null) {
            post(new Runnable() {
                @Override
                public void run() {
                    rendererChangeListener.onRendererChanged(renderer);
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

            if (renderer != null) {
                // As these callbacks won't be called by the GCSurfaceView we call them manually
                // to initialize rendererWrapper.
                this.renderer.onSurfaceCreated(null, lastConfig.config);
                this.renderer.onSurfaceChanged(null, lastConfig.width, lastConfig.height);
            }
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

    public interface OnRendererChangeListener {
        @MainThread
        void onRendererChanged(Renderer renderer);
    }
}
