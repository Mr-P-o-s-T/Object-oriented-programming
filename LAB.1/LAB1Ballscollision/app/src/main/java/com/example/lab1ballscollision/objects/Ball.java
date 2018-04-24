package com.example.lab1ballscollision.objects;

abstract class Ball {
    Vector position, prevPosition, impulse;
    double mass;

    Ball(double x, double y, double m) {
        position = new Vector(x, y);
        prevPosition = new Vector(position);
        impulse = new Vector();
        mass = m;
    }

    Ball(Ball origin) {
        position = new Vector(origin.position);
        prevPosition = new Vector(position);
        impulse = new Vector(origin.impulse);
        mass = origin.mass;
    }

    abstract double getRadius();

    void positionChanging(double deltaT) {
        prevPosition = position;
        position = position.add(impulse.multOnScalar(deltaT).multOnScalar(1 / mass));
    }

    public boolean areCollided(Ball secondBall) {
        Vector delta = position.subtract(secondBall.position);
        return delta.length() < getRadius() + secondBall.getRadius();
    }

    private Vector getOffset() {
        return position.subtract(prevPosition);
    }

    private Vector getPrevPosDiff(Ball secondBall) {
        return secondBall.prevPosition.subtract(prevPosition);
    }

    private Vector getPosDiff(Ball secondBall) {
        return secondBall.position.subtract(position);
    }

    public Vector getVelocityDiff(Ball secondBall) {
        return secondBall.impulse.multOnScalar(1 / secondBall.mass).subtract(impulse.multOnScalar(1 / mass));
    }

    void impulseChanging(double speedX, double speedY) {
        impulse.x = speedX * mass;
        impulse.y = speedY * mass;
    }

    void relativeImpulseChanging(double deltaSpeedX, double deltaSpeedY) {
        impulse.x += deltaSpeedX * mass;
        impulse.y += deltaSpeedY * mass;
    }

    private double getCollisionTime(Ball secondBall) {
        Vector deltaPos = getPrevPosDiff(secondBall), deltaImp = getVelocityDiff(secondBall);
        double a = deltaImp.x * deltaImp.x + deltaImp.y * deltaImp.y,
                b = deltaPos.x * deltaImp.x + deltaPos.y * deltaImp.y,
                c = deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y - (getRadius() + getRadius())
                        * (getRadius() + getRadius());

        double D = b * b - 4 * a * c;
        if (D < 0) {

        }
    }
}

