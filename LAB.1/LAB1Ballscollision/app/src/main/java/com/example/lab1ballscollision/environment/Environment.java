package com.example.lab1ballscollision.environment;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

import com.example.lab1ballscollision.objects.Ball;
import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Force;
import com.example.lab1ballscollision.objects.Vector;

import java.util.ArrayList;
import java.util.PriorityQueue;

public final class Environment {
    public static double dT, epsilon;
    public static Force gravity;
    private double lastMass = 0.0;
    public boolean paused = true;
    public PhysicBall highlighted;
    private ArrayList<PhysicBall> ballsCollection = new ArrayList<>();

    private class Pair implements Comparable<Pair> {
        PhysicBall first, last;
        double dT;

        Pair(PhysicBall f, PhysicBall l) {
            first = f;
            last = l;
            dT = first.getCollisionTime(last);
        }

        void Reaction() {
            first.collisionProcessing(last);
        }

        public int compareTo(Pair p) {
            if (Math.abs(dT - p.dT) < epsilon) return 0;
            else if (dT < p.dT) return -1;
            return 1;
        }
    }

    private PriorityQueue<Pair> collisionQueue = new PriorityQueue<>();

    public Environment(double xMax, double yMax) {
        PhysicBall.gravity = gravity;
        PhysicBall.xMax = xMax;
        PhysicBall.yMax = yMax;
        Vector.epsilon = epsilon;
    }

    public void increaseMass(double byMass) {
        if (!(Math.abs(byMass) < Vector.epsilon)) {
            lastMass = byMass;
            PhysicBall.increaseArithmeticMeanMass(byMass);
        }
    }

    public void returnMass() {
        if (!(Math.abs(lastMass) < Vector.epsilon)) {
            PhysicBall.decreaseArithmeticMeanMass(lastMass);
        }
    }

    public double getMass() {
        return PhysicBall.arithmeticMeanMass;
    }

    public void addBall(double x, double y, double m, Vector startImp) {
        PhysicBall newBall = new PhysicBall(x * PhysicBall.xMax, y * PhysicBall.yMax, m);
        newBall.impulseChanging(startImp);
        ballsCollection.add(newBall);
    }

    public void addBall(double x, double y, double m) {
        PhysicBall newBall = new PhysicBall(x, y, m);
        ballsCollection.add(newBall);
        highlighted = newBall;
        lastMass = 0.0;
    }

    void deleteBall() {
        highlighted.preDeletingActions();
        ballsCollection.remove(highlighted);
    }

    public boolean highligntBall(double x, double y) {
        for (PhysicBall item: ballsCollection)
            if ((x - item.getX()) * (x - item.getX()) + (y - item.getY()) * (y - item.getY()) < item.getRadius() * item.getRadius()) {
                highlighted = item;
                return true;
            }
        return false;
    }

    public void  unhighlightBall() {
        highlighted = null;
    }

    public void clearBalls() {
        ballsCollection.clear();
        PhysicBall.resetMass();
    }

    private void checkRicochets() {
        for (PhysicBall item: ballsCollection) {
            if ((item.getX() < item.getRadius()) || (item.getX() > PhysicBall.xMax - item.getRadius()))
                item.horizontalRicochet();
            if ((item.getY() < item.getRadius()) || (item.getY() > PhysicBall.yMax - item.getRadius()))
                item.verticalRicochet();
        }
    }

    private void move(double dT) {
        for (PhysicBall item: ballsCollection) item.positionChanging(dT);
        for (Pair item: collisionQueue) item.dT -= dT;
    }

    private void checkCollisions(int i, double currT) {
        for (int j = i + 1; j < ballsCollection.size(); j++)
            if (ballsCollection.get(i).areCollided(ballsCollection.get(j), currT))
                collisionQueue.add(new Pair(ballsCollection.get(i), ballsCollection.get(j)));
    }

    private void checkCollisions(PhysicBall b, double currT) {
        for (int i = 0; i < ballsCollection.size(); i++)
            if ((ballsCollection.get(i) != b) && (b.areCollided(ballsCollection.get(i), currT)))
                collisionQueue.add(new Pair(b, ballsCollection.get(i)));
    }

    public void ballsProcessing() {
        double currT = dT;
        for (int i = 0; i < ballsCollection.size(); i++) {
            checkCollisions(i, currT);
        }
        while (!collisionQueue.isEmpty()) {
            checkRicochets();
            Pair tmp = collisionQueue.poll();
            move(tmp.dT);
            tmp.Reaction();
            checkCollisions(tmp.first, tmp.dT);
            checkCollisions(tmp.last, tmp.dT);
            currT -= tmp.dT;
        }
        for (PhysicBall item: ballsCollection) {
            checkRicochets();
            item.positionChanging(currT);
        }
    }

    public void drawBalls(Canvas canvas) {
        Paint circle = new Paint();
        circle.setColor(Color.parseColor("#7BE61E"));
        for (PhysicBall item: ballsCollection) item.drawMe(canvas, circle);
        if (highlighted != null) {
            circle.setColor(Color.MAGENTA);
            highlighted.drawMe(canvas, circle);
        }
    }

    public boolean areCollidedWithAny(double x, double y, double m) {
        for (PhysicBall item: ballsCollection) {
            double r = m / getMass() * PhysicBall.xMax / 10;
            if ((item.getX() - x) * (item.getX() - x) + (item.getY() - y) * (item.getY() - y) <= r + item.getRadius()) return true;
        }
        return false;
    }
}
