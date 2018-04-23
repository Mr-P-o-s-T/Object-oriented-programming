package com.example.lab1ballscollision.enviroment;

import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Force;
import com.example.lab1ballscollision.objects.Vector;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Enviroment {
    public static double dT, xMax, yMax;
    public static Force gravity;
    private ArrayList<PhysicBall> ballsCollection = new ArrayList<>();

    private class Pair {
        PhysicBall first, last;

        Pair(PhysicBall f, PhysicBall l) {
            first = f;
            last = l;
        }

        void Reaction() {
                first.collisionProcessing(last);
        }
    }

    private Queue<Pair> collisionQueue = new LinkedList<>();

    public Enviroment() {

    }

    public void addBall(double x, double y, double m) {
        PhysicBall newBall = new PhysicBall(x, y, m);
        ballsCollection.add(newBall);
    }

    private void movementProcessing() {
        for (PhysicBall item: ballsCollection) item.positionChanging(dT);

    }

    private void collisionsProcessing() {
        for (int i = 0; i < ballsCollection.size(); i++) {
            for (int j = i + 1; j < ballsCollection.size(); j++) {
                double dX, dY, dVx, dVy;
                {
                    Vector prevDiff = ballsCollection.get(i).getPrevPosDiff(ballsCollection.get(j)),
                            velocityDiff = ballsCollection.get(i).getVelocityDiff(ballsCollection.get(j));
                    dX = prevDiff.x; dY = prevDiff.y; dVx = velocityDiff.x; dVy = velocityDiff.y;
                }
                double D = 4 * (2 * dX * dY * dVx * dVy - dX * dX * dVy * dVy + dY * dY * dVx * dVx
                        + (ballsCollection.get(i).getRadius() + ballsCollection.get(j).getRadius())
                        * (ballsCollection.get(i).getRadius() + ballsCollection.get(j).getRadius())
                        * (dVx * dVx + dVy * dVy));
                
            }
        }
        for (Pair item : collisionQueue) item.Reaction();
    }

    public void ballsProcessing() {

    }
}
