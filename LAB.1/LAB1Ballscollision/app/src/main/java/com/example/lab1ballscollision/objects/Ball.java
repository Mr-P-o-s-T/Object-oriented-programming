package com.example.lab1ballscollision.objects;

public class Ball {
    protected Vector position, impulse;
    protected float radius;

    Ball(double x, double y, float r) {
        position = new Vector(x, y);
        impulse = new Vector();
        radius = r;
    }
    Ball(Ball origin) {
        position = new Vector(origin.position);
        impulse = new Vector(origin.impulse);
        radius = origin.radius;
    }

    void changePosition(double deltaT) {
        position = position.add(impulse.multOnScalar(deltaT).multOnScalar(1 / radius));
    }

    boolean areCollided(Ball secondBall) {
        Vector delta = position.subtract(secondBall.position);
        return delta.length() < radius + secondBall.radius;
    }
}
