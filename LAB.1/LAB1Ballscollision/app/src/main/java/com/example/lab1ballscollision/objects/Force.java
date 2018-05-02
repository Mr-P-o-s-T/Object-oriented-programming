package com.example.lab1ballscollision.objects;

public abstract class Force extends Vector {

    Force(double nForceX, double nForceY, double nForceZ) {
        super(nForceX, nForceY, nForceZ);
    }

    Force(double nForceX, double nForceY) {
        super(nForceX, nForceY);
    }

    Force() {
        super();
    }

    Force(Force origin) {
        super(origin);
    }

    public abstract void Update(double mass, Vector ... dependencies);
}
