package com.example.lab1ballscollision.objects;

abstract class Ball {
    Vector position, impulse;
    private Vector prevPosition;
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
        double collisionTime = getCollisionTime(secondBall);
        if ((Math.abs(collisionTime) < Vector.epsilon) || ((0.0 < collisionTime) && (collisionTime < 1.0)) || (Math.abs(collisionTime) - 1 < Vector.epsilon)) return true;
        return false;
    }

    void impulseChanging(double speedX, double speedY) {
        impulse.x = speedX * mass;
        impulse.y = speedY * mass;
    }

    void relativeImpulseChanging(double deltaSpeedX, double deltaSpeedY) {
        impulse.x += deltaSpeedX * mass;
        impulse.y += deltaSpeedY * mass;
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

    private Vector getVelocityDiff(Ball secondBall) {
        return secondBall.impulse.multOnScalar(1 / secondBall.mass).subtract(impulse.multOnScalar(1 / mass));
    }

    double getCollisionTime(Ball secondBall) {
        Vector deltaPos = getPrevPosDiff(secondBall), deltaVel = getVelocityDiff(secondBall);
        double a = deltaVel.length() * deltaVel.length(),
                b = 2 * deltaPos.scalarCompos(deltaVel),
                c = deltaPos.length() * deltaPos.length() - (getRadius() + getRadius()) *
                        (getRadius() + getRadius());
        if (Math.abs(a) < Vector.epsilon) return Double.MAX_VALUE;
        else if (b < 0.0) {
            double D = b * b - 4 * a * c;
            if (Math.abs(D) < Vector.epsilon) return -b / (2 * a);
            else if (D < 0.0) return Double.MAX_VALUE;
            else return (-b - Math.sqrt(D)) / (2 * a);
        }
        else return Double.MAX_VALUE;
    }
}
