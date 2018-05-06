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
    public static double dT, xMax, yMax, epsilon;
    public static Force gravity;
    public boolean paused = true;
    private PhysicBall highlighted;
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

    public Environment() {
        PhysicBall.gravity = gravity;
        PhysicBall.xMax = xMax;
        PhysicBall.yMax = yMax;
        Vector.epsilon = epsilon;
    }

    public PhysicBall addBall(double x, double y, double r, Vector startImp) {
        PhysicBall newBall = new PhysicBall(x * xMax, y * yMax, r);
        newBall.impulseChanging(startImp.x, startImp.y);
        ballsCollection.add(newBall);
        return newBall;
    }

    void deleteBall() {
        highlighted.preDeletingActions();
        ballsCollection.remove(highlighted);
    }

    public void highligntBall(double x, double y) {
        for (PhysicBall item: ballsCollection)
            if ((x - item.getX()) * (x - item.getX()) + (y - item.getY()) * (y - item.getY()) < item.getRadius() * item.getRadius()) {
                highlighted = item;
                break;
            }
    }

    public void clearBalls() {
        ballsCollection.clear();
        PhysicBall.resetMass();
    }

    private void checkRicochets() {
        for (PhysicBall item: ballsCollection) {
            if ((item.getX() < item.getRadius()) || (item.getX() > xMax - item.getRadius()))
                item.horizontalRicochet();
            if ((item.getY() < item.getRadius()) || (item.getY() > yMax - item.getRadius()))
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
            Pair tmp = collisionQueue.poll();
            move(tmp.dT);
            tmp.Reaction();
            checkCollisions(tmp.first, tmp.dT);
            checkCollisions(tmp.last, tmp.dT);
            checkRicochets();
            currT -= tmp.dT;
        }
        for (PhysicBall item: ballsCollection) {
            item.positionChanging(currT);
            checkRicochets();
        }
    }

    public void drawBalls(Canvas canvas) {
        Paint circle = new Paint();
        circle.setColor(Color.GREEN);
        for (PhysicBall item: ballsCollection) item.drawMe(canvas, circle);
    }

    public boolean areCollidedWithAny(double x, double y, double r) {
        for (PhysicBall item: ballsCollection)
            if ((item.getX() - x) * (item.getX() - x) + (item.getY() - y) * (item.getY() - y) <= r + item.getRadius()) return true;
        return false;
    }
}
