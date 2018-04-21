package com.example.lab1ballscollision.objects;

public abstract class Ball {
    Vector position, impulse;
    float mass;

    Ball(double x, double y, float m) {
        position = new Vector(x, y);
        impulse = new Vector();
        mass = m;
    }

    Ball(Ball origin) {
        position = new Vector(origin.position);
        impulse = new Vector(origin.impulse);
        mass = origin.mass;
    }

    abstract double getRadius();

    void positionChanging(double deltaT) {
        position = position.add(impulse.multOnScalar(deltaT).multOnScalar(1 / mass));
    }

    boolean areCollided(Ball secondBall) {
        Vector delta = position.subtract(secondBall.position);
        return delta.length() < getRadius() + secondBall.getRadius();
    }

    void impulseChanging(double speedX, double speedY) {
        impulse.x = speedX * mass;
        impulse.y = speedY * mass;
    }

    void relativeImpluseChanging(double deltaSpeedX, double deltaSpeedY) {
        impulse.x += deltaSpeedX * mass;
        impulse.y += deltaSpeedY * mass;
    }
}
