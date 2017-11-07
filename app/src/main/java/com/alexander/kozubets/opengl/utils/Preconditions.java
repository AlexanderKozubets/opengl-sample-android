package com.alexander.kozubets.opengl.utils;


import android.support.annotation.NonNull;

public class Preconditions {

    public static <T> T nonNull(@NonNull T ref) {
        if (ref == null) throw new NullPointerException("Should not be null!");
        return ref;
    }

    public static <T extends CharSequence> T nonEmpty(@NonNull T ref) {
        if (nonNull(ref).length() == 0) throw new IllegalArgumentException("Should not be empty!");
        return ref;
    }

    private Preconditions() throws IllegalAccessException {
        throw new IllegalAccessException();
    }
}
