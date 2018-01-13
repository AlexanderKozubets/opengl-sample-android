package com.alexander.kozubets.opengl.sample;


import android.opengl.GLES20;
import android.util.SparseIntArray;
import android.view.View;

import com.alexander.kozubets.opengl.renderer.TriangleRenderer;

public class DrawElementsModeClickListener implements View.OnClickListener {

    private static final SparseIntArray viewIdRenderModePairs = new SparseIntArray();

    static {
        viewIdRenderModePairs.put(R.id.rbPoints, GLES20.GL_POINTS);
        viewIdRenderModePairs.put(R.id.rbLineLoop, GLES20.GL_LINE_LOOP);
        viewIdRenderModePairs.put(R.id.rbLineStrip, GLES20.GL_LINE_STRIP);
        viewIdRenderModePairs.put(R.id.rbLines, GLES20.GL_LINES);
        viewIdRenderModePairs.put(R.id.rbTriangleFan, GLES20.GL_TRIANGLE_FAN);
        viewIdRenderModePairs.put(R.id.rbTriangleStrip, GLES20.GL_TRIANGLE_STRIP);
        viewIdRenderModePairs.put(R.id.rbTriangles, GLES20.GL_TRIANGLES);
    }

    private final TriangleRenderer renderer;

    public DrawElementsModeClickListener(TriangleRenderer renderer) {
        this.renderer = renderer;
    }

    @Override
    public void onClick(View v) {
        final int mode = viewIdRenderModePairs.get(v.getId());
        renderer.setMode(mode);
    }
}
