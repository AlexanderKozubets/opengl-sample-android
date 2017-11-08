package com.alexander.kozubets.opengl.sample;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.alexander.kozubets.opengl.task.LoadBitmapAsyncTask;
import com.alexander.kozubets.opengl.utils.StreamUtils;
import com.alexander.kozubets.opengl.view.NativeRenderer;

import java.io.IOException;
import java.io.InputStream;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonEmpty;
import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public class MainActivity extends AppCompatActivity {

    private static final int PICK_IMAGE_REQUEST_CODE = 0;

    private GLSurfaceView glSurfaceView;

    private NativeRenderer renderer;

    private LoadBitmapAsyncTask loadTextureBytesAsyncTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    protected void initView() {
        glSurfaceView = (GLSurfaceView) findViewById(R.id.glView);
        renderer = NativeRenderer.get(new AssetsShaderRepository(getApplicationContext(), "shaders"));
        glSurfaceView.setRenderer(renderer);
        findViewById(R.id.btnLoadTexture).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                pickImage();
            }
        });
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
            loadTextureBytesAsyncTask = new LoadBitmapAsyncTask() {
                @Override
                protected void onPostExecute(Bitmap bitmap) {
                    super.onPostExecute(bitmap);
                    runOnGlThread(new CreateTexture(bitmap) {
                        @Override
                        public void onTextureCreated(int textureId) {
                            Log.i("CreateTexture", "Texture id: " + textureId);
                            renderer.onTextureLoaded();
                        }
                    });
                    loadTextureBytesAsyncTask = null;
                }
            };
            loadTextureBytesAsyncTask.execute(inputStream);
        } catch (IOException e) {
            StreamUtils.log(e);
            StreamUtils.close(inputStream);
        }
    }

    private void showMessage(@NonNull String message) {
        Toast.makeText(this, nonEmpty(message), Toast.LENGTH_SHORT);
    }

    private static abstract class CreateTexture implements Runnable {

        private Bitmap bitmap;

        public CreateTexture(@NonNull Bitmap bitmap) {
            this.bitmap = nonNull(bitmap);
        }

        @Override
        public void run() {
            int textureId = createTexture(bitmap);
            bitmap.recycle();
            onTextureCreated(textureId);
        }

        public abstract void onTextureCreated(int textureId);

        /**
         * Source http://www.learnopengles.com/android-lesson-four-introducing-basic-texturing/
         * <p>
         * Native implementation of {@link GLUtils#texImage2D(int, int, Bitmap, int)}
         * https://gitlab.com/SaberMod/pa-android-frameworks-base/blob/5e49b497ae2019586937aae0e8159292363728b5/core/jni/android/opengl/util.cpp
         * </p>
         */
        private int createTexture(@NonNull Bitmap bitmap) {
            final int textureId = genTextureId();
            boolean isValidTexId = textureId != 0;

            if (isValidTexId) {
                // Bind to the texture in OpenGL
                GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);

                // Set filtering
                GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
                GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);

                // Load the bitmap into the bound texture.
                GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
            } else {
                throw new RuntimeException("Error loading texture.");
            }

            return textureId;
        }

        private int genTextureId() {
            return genTextureIds(1)[0];
        }

        private int[] genTextureIds(int n) {
            final int[] texturesId = new int[n];
            GLES20.glGenTextures(n, texturesId, 0);
            return texturesId;
        }
    }
}
