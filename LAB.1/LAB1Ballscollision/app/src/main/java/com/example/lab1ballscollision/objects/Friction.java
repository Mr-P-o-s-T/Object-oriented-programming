package com.example.lab1ballscollision.objects;

final class Friction extends Force {
    private double mu;

    Friction(double nMu) {
        super();
        mu = nMu;
    }

    Friction(double nMu, double nForceX, double nForceY) {
        super(nForceX, nForceY);
        mu = nMu;
    }

    Friction(Friction origin) {
        super(origin);
        mu = origin.mu;
    }

    @Override
    public void Update(double mass, Vector... dependencies) { // dependencies[0] - impulse, // dependencies[1] - gravity force
        Vector tmp = new Vector();
        tmp = tmp.subtract(dependencies[0].normalise()); //tmp = -(normalised impulse)
        tmp = tmp.multOnScalar(mu).multOnScalar(mass).multOnScalar(dependencies[1].z);
        x = tmp.x;
        y = tmp.y;
        z = tmp.z;
    }
}
