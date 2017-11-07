package com.alexander.kozubets.opengl.sample;


import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import com.alexander.kozubets.opengl.view.ShaderRepository;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonEmpty;
import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;
import static com.alexander.kozubets.opengl.utils.StreamUtils.close;
import static com.alexander.kozubets.opengl.utils.StreamUtils.log;

public class AssetsShaderRepository implements ShaderRepository {

    Context context;

    String assetFolder;

    public AssetsShaderRepository(@NonNull Context context, @NonNull String assetFolder) {
        this.context = nonNull(context);
        this.assetFolder = nonEmpty(assetFolder);
    }

    @Nullable
    @Override
    public String getShader(@NonNull String name) {
        StringBuilder shader = new StringBuilder();
        InputStream json;
        BufferedReader inStream = null;

        boolean error = false;

        try {
            json = context.getAssets().open(getPath(assetFolder, nonEmpty(name)));
            inStream = new BufferedReader(new InputStreamReader(json, "UTF-8"));
            String line;

            while ((line = inStream.readLine()) != null) {
                shader.append(line);
            }
        } catch (IOException e) {
            error = true;
            log(e);
        } finally {
            close(inStream);
        }

        return error ? null : shader.toString();
    }

    protected String getPath(String folder, String name) {
        return String.format("%s/%s", folder, name);
    }
}
