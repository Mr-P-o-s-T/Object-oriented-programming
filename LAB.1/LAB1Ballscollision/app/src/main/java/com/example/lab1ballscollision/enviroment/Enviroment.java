package com.example.lab1ballscollision.enviroment;

import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Gravity;

public class Enviroment {
    static {
        PhysicBall.gravity = new Gravity(0.0, 0.0, 9.0);
    }
}
