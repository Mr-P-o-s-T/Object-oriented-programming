package com.example.lab1ballscollision.objects;

public final class PhysicBall extends Ball {
    private static double arithmeticMeanMass = 0.0;
    private static long N = 0;
    public static Force gravity;
    private Force friction;

    public PhysicBall(double x, double y, double m) {
        super(x, y, m);
        arithmeticMeanMass += N / (N + 1) * arithmeticMeanMass + m / (N + 1);
        friction = new Friction();
    }

    public PhysicBall(PhysicBall origin) {
        super(origin);
        arithmeticMeanMass += origin.mass;
        friction = new Friction();
    }

    @Override
    public double getRadius() {
        return mass / arithmeticMeanMass;
    }

    public void Collision(PhysicBall b) {
            // todo: fill with code
    }

    void positionChanging(double deltaT) {
        super.positionChanging(deltaT);
        updateImpulse(deltaT);
        friction.Update(impulse, gravity);
    }

    private void updateImpulse(double deltaT) {
        if (impulse.subtract(friction).length() < 0.001) impulse = Vector.nullVector;
        else relativeImpulseChanging(friction.x * deltaT, friction.y * deltaT);
    }

    public void horisontalRicochet() {
        impulseChanging(-impulse.x, impulse.y);
    }

    public void verticalRicochet() {
        impulseChanging(impulse.x, -impulse.y);
    }
}
