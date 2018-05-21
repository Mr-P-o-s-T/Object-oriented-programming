package com.example.lab1ballscollision.objects;

public final class PhysicBall extends Ball {
    public static double arithmeticMeanMass = 0.0;
    private static long N = 0;
    public static Force gravity;
    private Force friction;

    public PhysicBall(double x, double y, double m) {
        super(x, y, m);
        increaseArithmeticMeanMass(m);
        friction = new Friction(0.4);
    }

    public PhysicBall(PhysicBall origin) {
        super(origin);
        friction = new Friction(0.4);
    }

    static public void increaseArithmeticMeanMass(double newMass) {
        arithmeticMeanMass = ((double) N) / (N + 1) * arithmeticMeanMass + newMass / (N + 1);
        N++;
    }

    static public void decreaseArithmeticMeanMass(double newMass) {
        if (N > 1) arithmeticMeanMass = ((double) N) / (N - 1) * arithmeticMeanMass - newMass / (N - 1);
        else arithmeticMeanMass = 0.0;
        N--;
    }

    public void preDeletingActions() {
        decreaseArithmeticMeanMass(mass);
    }

    public double getX() {
        return position.x;
    }

    public double getY() {
        return position.y;
    }

    @Override
    public double getRadius() {
        return mass / arithmeticMeanMass * xMax / 20;
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
        Vector tmp = new Vector(impulse);
        relativeImpulseChanging(friction.x * deltaT + gravity.x * deltaT, friction.y * deltaT + gravity.y * deltaT);
        if (impulse.x * tmp.x < 0.0) impulse.x = 0.0;
        if (impulse.y * tmp.y < 0.0) impulse.y = 0.0;
    }

    public void horizontalRicochet() {
        if (impulse.x > 0.0) position.x -= 2 * (position.x - xMax + getRadius());
        else position.x += 2 * (getRadius() - position.x);
        impulseChanging(-impulse.x, impulse.y);
        friction.Update(mass, impulse, gravity);
    }

    public void verticalRicochet() {
        if (impulse.y > 0.0) position.y -= 2 * (position.y - yMax + getRadius());
        else position.y += 2 * (getRadius() - position.y);
        impulseChanging(impulse.x, -impulse.y);
        friction.Update(mass, impulse, gravity);
    }

    static public void resetMass() {
        N = 0;
        arithmeticMeanMass = 0.0;
    }
}
