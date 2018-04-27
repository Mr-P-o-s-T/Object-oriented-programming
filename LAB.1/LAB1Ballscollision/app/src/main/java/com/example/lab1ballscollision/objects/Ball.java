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
        Vector deltaPos = getPrevPosDiff(secondBall), deltaVel = getVelocityDiff(secondBall);
        double a = deltaVel.length() * deltaVel.length(),
                b = 2 * deltaPos.scalarCompos(deltaVel),
                c = deltaPos.length() * deltaPos.length() - (getRadius() + getRadius()) *
                        (getRadius() + getRadius());
        if (Math.abs(a) < Vector.epsilon) return Double.MAX_VALUE;
        else {
            double D = b * b - 4 * a * c;
            double dT;
            if (D < 0) return Double.MAX_VALUE;
            else if (Math.abs(D) < Vector.epsilon) dT = -b / (2 * a);
            else dT = (-b - Math.sqrt(D)) / (2 * a);
            if ((0 <= dT) && (dT <= 1)) return dT;
            else return Double.MAX_VALUE;
        }
    }
}
