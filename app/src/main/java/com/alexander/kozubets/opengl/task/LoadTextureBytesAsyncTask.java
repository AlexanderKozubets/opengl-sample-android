package com.alexander.kozubets.opengl.task;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;

import com.alexander.kozubets.opengl.utils.StreamUtils;

import java.io.InputStream;
import java.nio.ByteBuffer;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public class LoadTextureBytesAsyncTask extends AsyncTask<InputStream, Float, byte[]> {

    @Override
    protected byte[] doInBackground(InputStream... streams) {
        InputStream inputStream = nonNull(streams[0]);
        Bitmap bitmap = loadBitmap(inputStream);
        StreamUtils.close(inputStream);
        byte[] pixels = getPixels(bitmap);
        bitmap.recycle();
        return pixels;
    }

    private Bitmap loadBitmap(InputStream inputStream) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inSampleSize = 2;
        Bitmap bitmap = BitmapFactory.decodeStream(inputStream, null, options);
        return bitmap;
    }

    private byte[] getPixels(Bitmap src) {
        int bytes = src.getByteCount();
        ByteBuffer buffer = ByteBuffer.allocate(bytes);
        src.copyPixelsToBuffer(buffer);
        return buffer.array();
    }
}
