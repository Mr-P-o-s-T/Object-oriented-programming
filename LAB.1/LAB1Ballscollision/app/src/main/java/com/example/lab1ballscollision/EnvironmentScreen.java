package com.example.lab1ballscollision;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.example.lab1ballscollision.environment.Environment;
import com.example.lab1ballscollision.objects.Vector;

import java.sql.Time;
import java.util.Timer;
import java.util.TimerTask;

public class EnvironmentScreen extends AppCompatActivity {
    private Environment environment;
    private Field f;
    private Timer t;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        f = new Field(this);
        setContentView(f);

        environment = new Environment();
        environment.addBall(10, 10, 10.0, new Vector(1000, 1000));
        environment.addBall(110, 30, 20.0, new Vector(1000, 200));
        environment.addBall(110, 40, 20.0, new Vector(1000, 400));

        t = new Timer();
        t.schedule(new Update(), 10);
    }

    public class Field extends View {
        public Field(Context context) {
            super(context);
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            canvas.drawColor(Color.RED | Color.GREEN);
            environment.drawBalls(canvas);
            invalidate();
        }
    }

    public class Update extends TimerTask {
        @Override
        public void run() {
            environment.ballsProcessing();
            t.schedule(new Update(), 10);
        }
    }
}
