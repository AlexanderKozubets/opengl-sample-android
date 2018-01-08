package com.alexander.kozubets.opengl.task;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;

import com.alexander.kozubets.opengl.utils.StreamUtils;

import java.io.InputStream;

import static com.alexander.kozubets.opengl.utils.Preconditions.nonNull;

public class LoadBitmapAsyncTask extends AsyncTask<InputStream, Float, Bitmap> {

    @Override
    protected Bitmap doInBackground(InputStream... streams) {
        InputStream inputStream = nonNull(streams[0]);
        Bitmap bitmap = loadBitmap(inputStream);
        StreamUtils.close(inputStream);
        return bitmap;
    }

    private Bitmap loadBitmap(InputStream inputStream) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inSampleSize = 2;
        Bitmap bitmap = BitmapFactory.decodeStream(inputStream, null, options);
        return bitmap;
    }

    // TODO: pass pixels to native code and create texture there
    /*private byte[] getPixels(Bitmap src) {
        int bytes = src.getByteCount();
        ByteBuffer buffer = ByteBuffer.allocate(bytes);
        src.copyPixelsToBuffer(buffer);
        return buffer.array();
    }*/
}
