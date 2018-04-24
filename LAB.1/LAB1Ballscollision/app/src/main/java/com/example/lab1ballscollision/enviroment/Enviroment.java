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

    }

    public void ballsProcessing() {

    }
}
