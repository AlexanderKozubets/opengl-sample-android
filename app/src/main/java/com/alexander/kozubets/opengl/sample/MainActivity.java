package com.alexander.kozubets.opengl.sample;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.alexander.kozubets.opengl.view.NativeRenderer;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        GLSurfaceView glSurfaceView = (GLSurfaceView) findViewById(R.id.glView);
        glSurfaceView.setRenderer(NativeRenderer.get(new AssetsShaderRepository(getApplicationContext(), "shaders")));
    }
}
