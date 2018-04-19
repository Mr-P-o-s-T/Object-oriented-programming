package com.example.lab1ballscollision.objects;

class Vector {
    public static Vector nullVector;

    static {
        nullVector = new Vector(0.0,0.0);
    }

    public double x, y;

    public Vector(double nX, double nY) {
        x = nX; y = nY;
    }

    public Vector () {
        this(nullVector);
    }

    public Vector(Vector origin) {
        x = origin.x;
        y = origin.y;
    }

    public double length() {
        return Math.sqrt(x * x + y * y);
    }

    public Vector add(Vector b) {
        return new Vector(x + b.x, y + b.y);
    }

    public Vector subtract(Vector b) {
        return new Vector(x - b.x, y - b.y);
    }

    public Vector multOnScalar(double scalar) {
        return new Vector(x * scalar,y * scalar);
    }

    public double scalarCompos(Vector b) {
        return x * b.x + y * b.y;
    }

    public double vectorCompos(Vector b) {
        return x * b.y - y * b.x;
    }

    public double alpha(Vector b) {
        return Math.asin(vectorCompos(b) / (length() * b.length()));
    }

}
