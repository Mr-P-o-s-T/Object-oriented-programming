package com.example.lab1ballscollision.objects;

public final class PhysicBall extends Ball {
    private static double wholeMass = 0.0;
    public static Force gravity;
    private Force friction;

    public PhysicBall(double x, double y, float m) {
        super(x, y, m);
        wholeMass += m;
        friction = new Friction();
    }

    public PhysicBall(PhysicBall origin) {
        super(origin);
        wholeMass += origin.mass;
        friction = new Friction();
    }

    @Override
    public double getRadius() {
        return mass / wholeMass;
    }

    void positionChanging(double deltaT) {
        super.positionChanging(deltaT);
        updateImpulse(deltaT);
        friction.Update(impulse, gravity);
    }

    private void updateImpulse(double deltaT) {
        if (impulse.subtract(friction).length() < 0.001) impulse = Vector.nullVector;
        else relativeImpluseChanging(friction.x * deltaT, friction.y * deltaT);
    }

    public void horisontalRicochet() {
        relativeImpluseChanging(-impulse.x, impulse.y);
    }

    public void verticalRicochet() {
        relativeImpluseChanging(impulse.x, -impulse.y);
    }
}
