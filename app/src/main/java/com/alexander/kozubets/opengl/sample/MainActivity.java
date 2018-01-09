package com.alexander.kozubets.opengl.sample;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import com.alexander.kozubets.opengl.renderer.TextureProjectionRenderer;
import com.alexander.kozubets.opengl.renderer.TextureRenderer;
import com.alexander.kozubets.opengl.renderer.TriangleRenderer;
import com.alexander.kozubets.opengl.task.LoadBitmapAsyncTask;
import com.alexander.kozubets.opengl.utils.CreateTexture;
import com.alexander.kozubets.opengl.utils.StreamUtils;
import com.alexander.kozubets.opengl.view.AssetsShaderRepository;
import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;

import java.io.IOException;
import java.io.InputStream;
import java.lang.ref.WeakReference;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonEmpty;

public class MainActivity extends AppCompatActivity {

    private static final int PICK_IMAGE_REQUEST_CODE = 0;

    private GLSurfaceView glSurfaceView;

    private ShaderNativeRenderer renderer;

    private AssetsShaderRepository shaderRepository;

    private LoadBitmapAsyncTask loadTextureBytesAsyncTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initGlView();
        initMenu();
    }

    protected void initGlView() {
        glSurfaceView = findViewById(R.id.glView);
        shaderRepository = new AssetsShaderRepository(getApplicationContext(), "shaders");
        renderer = new TextureRenderer(shaderRepository);
        glSurfaceView.setPreserveEGLContextOnPause(true);
        glSurfaceView.setRenderer(renderer);
        findViewById(R.id.btnLoadTexture).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                pickImage();
            }
        });
    }

    protected void initMenu() {
        NavigationView navigationView = findViewById(R.id.navigation);
        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                ShaderNativeRenderer renderer = null;

                switch (item.getItemId()) {
                    case R.id.btnTriangle: {
                        renderer = new TriangleRenderer(shaderRepository);
                    } break;

                    case R.id.btnSquare: {

                    } break;

                    case R.id.btnTexture: {
                        renderer = new TextureRenderer(shaderRepository);
                    } break;

                    case R.id.btnTransform: {
                        renderer = new TextureProjectionRenderer(shaderRepository);
                    } break;
                }

                if (renderer != null) {
                    MainActivity.this.renderer = renderer;
                    glSurfaceView.setRenderer(renderer);
                }

                return true;
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        glSurfaceView.onResume();
    }

    @Override
    protected void onStop() {
        glSurfaceView.onPause();
        super.onStop();
    }

    protected void runOnGlThread(Runnable action) {
        glSurfaceView.queueEvent(action);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == PICK_IMAGE_REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                Uri uri = data.getData();
                if (uri != null) {
                    loadTexture(uri);
                } else {
                    showMessage("Failed!");
                }
            } else {
                showMessage("Canceled!");
            }
        }
    }

    private void pickImage() {
        Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICK_IMAGE_REQUEST_CODE);
    }

    private void loadTexture(@NonNull Uri uri) {
        InputStream inputStream = null;
        try {
            inputStream = getContentResolver().openInputStream(uri);
            if (loadTextureBytesAsyncTask != null) {
                loadTextureBytesAsyncTask.cancel(true);
            }
            loadTextureBytesAsyncTask = new CreateTextureAsyncTask(this);
            loadTextureBytesAsyncTask.execute(inputStream);
        } catch (IOException e) {
            StreamUtils.log(e);
            StreamUtils.close(inputStream);
        }
    }

    private void onTextureLoaded(int textureId) {
        if (renderer instanceof TextureRenderer) {
            ((TextureRenderer) renderer).onTextureLoaded(textureId);
        } else if (renderer instanceof TextureProjectionRenderer) {
            ((TextureProjectionRenderer) renderer).onTextureLoaded(textureId);
        }
    }

    private void showMessage(@NonNull String message) {
        Toast.makeText(this, nonEmpty(message), Toast.LENGTH_SHORT);
    }

    private static class CreateTextureAsyncTask extends LoadBitmapAsyncTask {

        WeakReference<MainActivity> weakActivityRef;

        public CreateTextureAsyncTask(MainActivity activity) {
            this.weakActivityRef = new WeakReference<>(activity);
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            super.onPostExecute(bitmap);
            final MainActivity activity = weakActivityRef.get();
            if (activity != null && !activity.loadTextureBytesAsyncTask.isCancelled()) {
                activity.runOnGlThread(new CreateTexture(bitmap) {
                    @Override
                    public void onTextureCreated(int textureId) {
                        Log.i("CreateTexture", "Texture id: " + textureId);
                        activity.onTextureLoaded(textureId);
                    }
                });
                activity.loadTextureBytesAsyncTask = null;
            }
        }
    }
}
