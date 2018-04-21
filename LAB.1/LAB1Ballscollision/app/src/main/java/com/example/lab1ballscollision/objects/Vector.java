package com.example.lab1ballscollision.objects;

class Vector {
    public static Vector nullVector;

    static {
        nullVector = new Vector(0.0,0.0, 0.0);
    }

    public double x, y, z;

    public Vector(double nX, double nY, double nZ) {
        x = nX; y = nY; z = nZ;
    }

    public Vector(double nX, double nY) {
        this(nX, nY, 0.0);
    }

    public Vector () {
        this(nullVector);
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

    public double alpha(Vector b) {
        return Math.asin(vectorCompos(b).length() / (length() * b.length()));
    }

}
