package com.example.lab1ballscollision.objects;

public final class PhysicBall extends Ball {
    private static double arithmeticMeanMass = 0.0;
    private static long N = 0;
    public static Force gravity;
    private Force friction;

    public PhysicBall(double x, double y, double m) {
        super(x, y, m);
        arithmeticMeanMass = N / (N + 1) * arithmeticMeanMass + m / (N + 1);
        friction = new Friction();
    }

    public PhysicBall(PhysicBall origin) {
        super(origin);
        arithmeticMeanMass = N / (N + 1) * arithmeticMeanMass + origin.mass / (N + 1);
        friction = new Friction();
    }

    public void preDeletingActions() {
        arithmeticMeanMass = (N + 1) / N * arithmeticMeanMass - mass / N;
    }

    public double getX() {
        return position.x;
    }

    public  double getY() {
        return position.y;
    }

    @Override
    public double getRadius() {
        return mass / arithmeticMeanMass;
    }

    public void collisionProcessing(PhysicBall b) {
        // getting collision (C) axis
        Vector collisionAxis = b.position.subtract(position);

        // getting parallel to collision (C) axis impulse component (which is changeable)
        double i1 = impulse.scalarCompos(collisionAxis) / collisionAxis.length(), i2 = b.impulse.scalarCompos(collisionAxis) / collisionAxis.length();

        // saving orthogonal to collision (C) axis impulse component (which is unchangeable)
        impulse = impulse.subtract(collisionAxis.multOnScalar(i1));
        b.impulse = b.impulse.subtract(collisionAxis.multOnScalar(i2));

        // getting new impulses
        double _i1 = 0.95 * (2 * i2 + i1 - i1 * b.mass / mass) / (mass + b.mass),
                _i2 = 0.95 * (2 * i1 + i2 - i2 * mass / b.mass) / (mass + b.mass);

        // restoring default impulse vectors
        impulse = impulse.add(collisionAxis.multOnScalar(_i1));
        b.impulse = b.impulse.subtract(collisionAxis.multOnScalar(_i2));
    }

    public void positionChanging(double deltaT) {
        super.positionChanging(deltaT);
        updateImpulse(deltaT);
        friction.Update(impulse, gravity);
    }

    private void updateImpulse(double deltaT) {
        if (impulse.subtract(friction).length() < Vector.epsilon) impulse = new Vector();
        else relativeImpulseChanging(friction.x * deltaT, friction.y * deltaT);
    }

    public void horisontalRicochet() {
        impulseChanging(-impulse.x, impulse.y);
    }

    public void verticalRicochet() {
        impulseChanging(impulse.x, -impulse.y);
    }
}
