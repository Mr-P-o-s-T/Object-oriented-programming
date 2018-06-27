package com.example.lab1ballscollision.objects;

public class Vector {
    public static double epsilon;
    public double x, y, z;

    public Vector(double nX, double nY, double nZ) {
        x = nX; y = nY; z = nZ;
    }

    public Vector(double nX, double nY) {
        this(nX, nY, 0.0);
    }

    public Vector () {
        this(0.0, 0.0);
    }

    public Vector(Vector origin) {
        x = origin.x;
        y = origin.y;
        z = origin.z;
    }

    public double length() {
        return Math.sqrt(x * x + y * y + z * z);
    }

    public Vector normalise() {
        double len = length();
        if (len < epsilon) return new Vector();
        return new Vector(x / len, y / len, z / len);
    }

    public Vector add(Vector b) {
        return new Vector(x + b.x, y + b.y, z + b.z);
    }

    public Vector subtract(Vector b) {
        return new Vector(x - b.x, y - b.y, z - b.z);
    }

    public Vector multOnScalar(double scalar) {
        return new Vector(x * scalar,y * scalar, z * scalar);
    }

    public double scalarCompos(Vector b) {
        return x * b.x + y * b.y + z * b.z;
    }

    public Vector vectorCompos(Vector b) {
        return new Vector(y * b.z - z * b.y, z * b.x
                 - x * b.z,x * b.y - y * b.x);
    }

    public double cosAlpha(Vector b) {
        return b.length() < epsilon ? scalarCompos(b) / (length() * b.length()) : 0.0;
    }

    public double sinAlpha(Vector b) {
        return b.length() < epsilon ? vectorCompos(b).length() / (length() * b.length()) : 0.0;
    }

}
