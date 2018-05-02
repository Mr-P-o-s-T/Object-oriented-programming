package com.example.lab1ballscollision.objects;

public final class PhysicBall extends Ball {
    private static double arithmeticMeanMass = 0.0;
    private static long N = 0;
    public static Force gravity;
    private Force friction;

    public PhysicBall(double x, double y, double m) {
        super(x, y, m);
        arithmeticMeanMass = N / (N + 1) * arithmeticMeanMass + m / (N + 1);
        N++;
        friction = new Friction(0.4);
    }

    public PhysicBall(PhysicBall origin) {
        super(origin);
        arithmeticMeanMass = N / (N + 1) * arithmeticMeanMass + origin.mass / (N + 1);
        N++;
        friction = new Friction(0.4);
    }

    public void preDeletingActions() {
        arithmeticMeanMass = N / (N - 1) * arithmeticMeanMass - mass / (N - 1);
        N--;
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
        Vector collisionAxis = b.position.subtract(position).normalise();

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
        b.impulse = b.impulse.add(collisionAxis.multOnScalar(_i2));
    }

    public void positionChanging(double deltaT) {
        super.positionChanging(deltaT);
        updateImpulse(deltaT);
        friction.Update(mass, impulse, gravity);
    }

    private void updateImpulse(double deltaT) {
        if (impulse.subtract(friction).length() < Vector.epsilon) impulse = new Vector();
        else relativeImpulseChanging(friction.x * deltaT, friction.y * deltaT);
    }

    public void horizontalRicochet(double dT) {
        impulseChanging(impulse.multOnScalar(1.0 / 0.95));
        double outRangedTime;
        if (impulse.x > 0.0) outRangedTime = (position.x - xMax + getRadius()) / (impulse.x / mass * dT);
        else outRangedTime = (getRadius() - position.x) / (impulse.x / mass * dT);
        position.subtract(impulse.multOnScalar(1.0 / mass).multOnScalar(outRangedTime));
        updateImpulse(1.0 - outRangedTime);
        impulseChanging(-impulse.x, impulse.y);
        positionChanging(outRangedTime);
    }

    public void verticalRicochet(double dT) {
        impulseChanging(impulse.multOnScalar(1.0 / 0.95));
        double outRangedTime;
        if (impulse.y > 0.0) outRangedTime = (position.y - yMax + getRadius()) / (impulse.y / mass * dT);
        else outRangedTime = (getRadius() - position.y) / (impulse.y / mass * dT);
        position.subtract(impulse.multOnScalar(1.0 / mass).multOnScalar(outRangedTime));
        updateImpulse(1.0 - outRangedTime);
        impulseChanging(impulse.x, -impulse.y);
        positionChanging(outRangedTime);
    }
}
