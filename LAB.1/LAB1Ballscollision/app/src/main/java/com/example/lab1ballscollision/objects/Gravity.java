package com.example.lab1ballscollision.objects;

public final class Gravity extends Force {

    public Gravity(double nForceX, double nForceY, double nForceZ) {
        super(nForceX, nForceY, nForceZ);
    }

    public Gravity() {
        super();
    }

    public Gravity(Gravity origin) {
        super(origin);
    }

    @Override
    void Update(Vector ... dependencies) { // no arguments needed

    }
}
