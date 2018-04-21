package com.example.lab1ballscollision.objects;

abstract class Force extends Vector {

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

    abstract void Update(Vector ... dependencies);
}
