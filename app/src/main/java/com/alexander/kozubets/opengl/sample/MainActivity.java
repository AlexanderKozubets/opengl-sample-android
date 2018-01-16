package com.alexander.kozubets.opengl.sample;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.annotation.IntRange;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.alexander.kozubets.opengl.renderer.CubeTransformRenderer;
import com.alexander.kozubets.opengl.renderer.TextureRenderer;
import com.alexander.kozubets.opengl.renderer.PrimitivesRenderer;
import com.alexander.kozubets.opengl.task.LoadBitmapAsyncTask;
import com.alexander.kozubets.opengl.utils.CreateTexture;
import com.alexander.kozubets.opengl.utils.StreamUtils;
import com.alexander.kozubets.opengl.view.AssetsShaderRepository;
import com.alexander.kozubets.opengl.view.OpenGlView;
import com.alexander.kozubets.opengl.view.ShaderNativeRenderer;

import java.io.IOException;
import java.io.InputStream;
import java.lang.ref.WeakReference;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonEmpty;

public class MainActivity extends AppCompatActivity {

    private static final int PICK_IMAGE_REQUEST_CODE = 0;

    private OpenGlView glView;

    private ViewGroup paramContainer;

    private GLSurfaceView.Renderer renderer;

    private AssetsShaderRepository shaderRepository;

    private LoadBitmapAsyncTask loadTextureBytesAsyncTask;

    private int maxSideSize;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        paramContainer = findViewById(R.id.containerParams);
        initGlView();
        initMenu();
    }

    protected void initGlView() {
        glView = findViewById(R.id.glView);
        glView.setPreserveEGLContextOnPause(true);

        glView.setOnRendererChangeListener(new OpenGlView.OnRendererChangeListener() {
            @Override
            public void onRendererChanged(GLSurfaceView.Renderer renderer) {
                showParameters(renderer);
            }
        });

        shaderRepository = new AssetsShaderRepository(getApplicationContext(), "shaders");
        renderer = new PrimitivesRenderer(shaderRepository);
        glView.setRenderer(renderer);
    }

    protected void initMenu() {
        NavigationView navigationView = findViewById(R.id.navigation);
        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                ShaderNativeRenderer renderer = null;

                switch (item.getItemId()) {
                    case R.id.btnPrimitives: {
                        renderer = new PrimitivesRenderer(shaderRepository);
                    }
                    break;

                    case R.id.btnTexture: {
                        renderer = new TextureRenderer(shaderRepository);
                    }
                    break;

                    case R.id.btnTransform: {
                        renderer = new CubeTransformRenderer(shaderRepository);
                    }
                    break;
                }

                if (renderer != null) {
                    MainActivity.this.renderer = renderer;
                    glView.setRenderer(renderer);
                }

                return true;
            }
        });
    }

    protected void showParameters(final GLSurfaceView.Renderer renderer) {
        paramContainer.removeAllViews();
        if (renderer instanceof PrimitivesRenderer) {
            inflateParameters(paramContainer, R.layout.params_primitives);
            initParameters((PrimitivesRenderer) renderer);
        } else if (renderer instanceof TextureRenderer) {
            inflateParameters(paramContainer, R.layout.params_texture);
            initParameters((TextureRenderer) renderer);
        } else if (renderer instanceof CubeTransformRenderer) {
            inflateParameters(paramContainer, R.layout.params_transform);
            initParameters((CubeTransformRenderer) renderer);
        }
    }

    protected void inflateParameters(ViewGroup paramContainer, @LayoutRes int layoutId) {
        LayoutInflater inflater = LayoutInflater.from(this);
        inflater.inflate(layoutId, paramContainer, true);
    }

    protected void initParameters(final PrimitivesRenderer renderer) {
        SeekBar seekBar = findViewById(R.id.sbVerticesCount);
        final TextView verticesCountTitle = findViewById(R.id.tvVerticesCountTitle);

        final int MAX_VERTICES_COUNT = 6;
        seekBar.setMax(MAX_VERTICES_COUNT - 1);
        seekBar.setOnSeekBarChangeListener(new DefaultSeekBarListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                final int verticesCount = progress + 1;
                glView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        renderer.setVerticesCount(verticesCount);
                    }
                });
                verticesCountTitle.setText(getString(R.string.vertices_count_d, verticesCount));
            }
        });

        View.OnClickListener onModeClickListener = new DrawElementsModeClickListener(glView, renderer);

        int[] ids = {R.id.rbPoints, R.id.rbLineLoop, R.id.rbLineStrip, R.id.rbLineStrip,
                R.id.rbTriangleStrip, R.id.rbTriangleFan, R.id.rbTriangles};
        for (int id : ids) {
            paramContainer.findViewById(id).setOnClickListener(onModeClickListener);
        }

        seekBar.setProgress(2); // 3 vertices as counting starts from zero
        findViewById(R.id.rbTriangles).performClick();
    }

    protected void initParameters(TextureRenderer renderer) {
        findViewById(R.id.btnSelectTexture).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                glView.getMaxTextureSize(new OpenGlView.OnGetMaxTextureSize() {
                    @Override
                    public void onGetMaxTexturesSize(int maxTexSize) {
                        pickImage(maxTexSize);
                    }
                });
            }
        });
    }

    protected void initParameters(final CubeTransformRenderer renderer) {
        SeekBar sbRotateX = findViewById(R.id.sbRotateX);
        SeekBar sbRotateY = findViewById(R.id.sbRotateY);
        SeekBar sbRotateZ = findViewById(R.id.sbRotateZ);

        sbRotateX.setOnSeekBarChangeListener(new DefaultSeekBarListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, final int progress, boolean fromUser) {
                glView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        renderer.setRotationX(progressToAngle(progress));
                    }
                });
            }
        });

        sbRotateY.setOnSeekBarChangeListener(new DefaultSeekBarListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, final int progress, boolean fromUser) {
                glView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        renderer.setRotationY(progressToAngle(progress));
                    }
                });
            }
        });

        sbRotateZ.setOnSeekBarChangeListener(new DefaultSeekBarListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, final int progress, boolean fromUser) {
                glView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        renderer.setRotationZ(progressToAngle(progress));
                    }
                });
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        glView.onResume();
    }

    @Override
    protected void onStop() {
        glView.onPause();
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        glView.setRenderer(null);
        super.onDestroy();
    }

    protected void runOnGlThread(Runnable action) {
        glView.queueEvent(action);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == PICK_IMAGE_REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                Uri uri = data.getData();
                if (uri != null) {
                    loadTexture(uri, maxSideSize);
                } else {
                    showMessage("Failed!");
                }
            } else {
                showMessage("Canceled!");
            }
        }
    }

    private void pickImage(int maxSideSize) {
        this.maxSideSize = maxSideSize;

        Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICK_IMAGE_REQUEST_CODE);
    }

    private void loadTexture(@NonNull Uri uri, int maxSideSize) {
        InputStream inputStream = null;
        try {
            inputStream = getContentResolver().openInputStream(uri);
            if (loadTextureBytesAsyncTask != null) {
                loadTextureBytesAsyncTask.cancel(true);
            }
            loadTextureBytesAsyncTask = new CreateTextureAsyncTask(this, maxSideSize);
            loadTextureBytesAsyncTask.execute(inputStream);
        } catch (IOException e) {
            StreamUtils.log(e);
            StreamUtils.close(inputStream);
        }
    }

    private void onTextureLoaded(int textureId) {
        if (renderer instanceof TextureRenderer) {
            ((TextureRenderer) renderer).onTextureLoaded(textureId);
        }
    }

    /**
     * Get angle in degrees that corresponds to {@link SeekBar#getProgress()}.
     * Minimum progress corresponds to -180 degrees and maximum progress corresponds to 180 degrees.
     *
     * @param progress value from range [0; 100]
     * @return angle in degrees.
     */
    private float progressToAngle(@IntRange(from = 0, to = 100) int progress) {
        final int maxProgress = 100;
        final int center = maxProgress / 2;
        final float angleDegrees = (progress - center) * 180.0f / center;
        return angleDegrees;
    }

    private void showMessage(@NonNull String message) {
        Toast.makeText(this, nonEmpty(message), Toast.LENGTH_SHORT);
    }

    private static class CreateTextureAsyncTask extends LoadBitmapAsyncTask {

        WeakReference<MainActivity> weakActivityRef;

        public CreateTextureAsyncTask(MainActivity activity, int maxSideSize) {
            super(maxSideSize);
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
