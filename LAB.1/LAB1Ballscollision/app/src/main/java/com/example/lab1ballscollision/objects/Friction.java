package com.example.lab1ballscollision.objects;

final class Friction extends Force {
    private double mu, maxStictionLength;

    Friction(double nMu, double maxStiction) {
        super();
        mu = nMu;
        maxStictionLength = maxStiction;
    }

    Friction(double nMu, double nForceX, double nForceY) {
        super(nForceX, nForceY);
        mu = nMu;
    }

    Friction(Friction source) {
        super(source);
        mu = source.mu;
    }

    @Override
    void Update(Vector[] dependencies) { // dependencies[0] - speed, // dependencies[1] - gravity force
        if (length() < maxStictionLength) x = y = z = 0.0;
        else {
            Vector tmp = new Vector();
            tmp = tmp.subtract(dependencies[0].normalise()); //tmp = -speed
            tmp = tmp.multOnScalar(mu).multOnScalar(dependencies[1].length());
            x = tmp.x;
            y = tmp.y;
            z = tmp.z;
        }
    }
}
