package com.alexander.kozubets.opengl.sample;

import android.annotation.SuppressLint;
import android.content.ContentUris;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.DocumentsContract;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

import com.alexander.kozubets.opengl.task.LoadTextureBytesAsyncTask;
import com.alexander.kozubets.opengl.utils.StreamUtils;
import com.alexander.kozubets.opengl.view.NativeRenderer;

import java.io.IOException;
import java.io.InputStream;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonEmpty;

public class MainActivity extends AppCompatActivity {

    private static final int PICK_IMAGE_REQUEST_CODE = 0;

    private NativeRenderer renderer;

    private LoadTextureBytesAsyncTask loadTextureBytesAsyncTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    protected void initView() {
        GLSurfaceView glSurfaceView = (GLSurfaceView) findViewById(R.id.glView);
        renderer = NativeRenderer.get(new AssetsShaderRepository(getApplicationContext(), "shaders"));
        glSurfaceView.setRenderer(renderer);
        findViewById(R.id.btnLoadTexture).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                pickImage();
            }
        });
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
            loadTextureBytesAsyncTask = new LoadTextureBytesAsyncTask() {
                @Override
                protected void onPostExecute(byte[] bytes) {
                    super.onPostExecute(bytes);
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
}
