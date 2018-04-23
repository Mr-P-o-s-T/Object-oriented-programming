package com.example.lab1ballscollision.objects;

public abstract class Force extends Vector {

    public Force(double nForceX, double nForceY, double nForceZ) {
        super(nForceX, nForceY, nForceZ);
    }

    public Force(double nForceX, double nForceY) {
        super(nForceX, nForceY);
    }

    public Force() {
        super();
    }

    public Force(Force origin) {
        super(origin);
    }

    public abstract void Update(Vector ... dependencies);
}
