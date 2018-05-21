package com.example.lab1ballscollision;

import com.example.lab1ballscollision.objects.Ball;
import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Vector;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class PhysicBallUnitTests {
    @Test
    public void getCollisionTime_head_onCollision_isCorrect() {
        Vector.epsilon = 0.0001;
        Ball.xMax = 100;
        Ball a = new PhysicBall(0.0, 0.0, 0.2), b = new PhysicBall(100.0, 0.0, 0.2);
        a.speedChanging(1.0, 0.0); b.speedChanging(-1.0, 0.0);
        double dT = a.getCollisionTime(b);
        if (Math.abs(dT - 45) >= 0.01) assertFalse(true);
    }

    @Test
    public void getCollisionTime_lateralCollision_isCorrect() {
        Vector.epsilon = 0.0001;
        Ball.xMax = 100;
        Ball a = new PhysicBall(0.0, 0.0, 0.2), b = new PhysicBall(100.0, 0.0, 0.2);
        a.speedChanging(1.0, 0.0); b.speedChanging(-1.0, 0.0);
        double dT = a.getCollisionTime(b);
        if (Math.abs(dT - 45) >= 0.01) assertFalse(true);
    }

    @Test
    public void getCollisionTime_usualCollision_isCorrect() {
        Vector.epsilon = 0.0001;
        Ball.xMax = 100;
        Ball a = new PhysicBall(0.0, 0.0, 0.2), b = new PhysicBall(100.0, 0.0, 0.2);
        a.speedChanging(1.0, 0.5); b.speedChanging(-1.0, 2.0);
        double dT = a.getCollisionTime(b);
        if (Math.abs(dT - 45) >= 0.01) assertFalse(true);
    }
}