package com.alexander.kozubets.opengl.task;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;

import com.alexander.kozubets.opengl.utils.StreamUtils;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public class LoadBitmapAsyncTask extends AsyncTask<InputStream, Float, Bitmap> {

    final int maxSideSize;

    public LoadBitmapAsyncTask(int maxSideSize) {
        this.maxSideSize = maxSideSize;
    }

    @Override
    protected Bitmap doInBackground(InputStream... streams) {
        InputStream inputStream = nonNull(streams[0]);
        Bitmap bitmap = loadBitmap(inputStream);
        StreamUtils.close(inputStream);
        return bitmap;
    }

    private Bitmap loadBitmap(InputStream inputStream) {
        // Wrap input stream to BufferedInputStream to be able to perform reset later.
        // Solution from https://stackoverflow.com/questions/6716777/inputstream-will-not-reset-to-beginning
        InputStream bufferedInputStream = new BufferedInputStream(inputStream);
        final int bufferLimitInBytes = 1024 * 1024; // 1Kb should be enough to read image header
        bufferedInputStream.mark(bufferLimitInBytes);

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeStream(bufferedInputStream, null, options);

        int width = options.outWidth;
        int height = options.outHeight;

        if (width > maxSideSize || height > maxSideSize) {
            final double inSampleSize = Math.ceil(Math.max(((float) width) / maxSideSize, ((float) height) / maxSideSize));
            options.inSampleSize = (int) inSampleSize;
        }

        try {
            bufferedInputStream.reset();
        } catch (IOException e) {
            e.printStackTrace();
        }
        options.inJustDecodeBounds = false;
        Bitmap bitmap = BitmapFactory.decodeStream(bufferedInputStream, null, options);
        return bitmap;
    }

    // TODO: pass pixels to native code and create texture there?
    /*private byte[] getPixels(Bitmap src) {
        int bytes = src.getByteCount();
        ByteBuffer buffer = ByteBuffer.allocate(bytes);
        src.copyPixelsToBuffer(buffer);
        return buffer.array();
    }*/
}
