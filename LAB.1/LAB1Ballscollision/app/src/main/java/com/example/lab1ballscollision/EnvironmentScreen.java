package com.example.lab1ballscollision;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;

import com.example.lab1ballscollision.environment.Environment;
import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Vector;

import java.util.Timer;
import java.util.TimerTask;

public class EnvironmentScreen extends AppCompatActivity implements View.OnTouchListener  {
    private Environment environment;
    private Field f;
    private Timer t;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        f = new Field(this);
        f.setOnTouchListener(this);
        setContentView(f);

        environment = new Environment();
        environment.addBall(0.1, 0.1, 1.0, new Vector(50, 50));
        environment.addBall(0.7, 0.4, 2.0, new Vector(50, 20));
        environment.addBall(0.7, 0.6, 2.0, new Vector(50, 30));

        t = new Timer();
        t.schedule(new Update(), 10);
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        double x = event.getX(), y = event.getY(), r = 0.0;
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                if (f.ballCreation) {
                    f.ballCreation = false;
                    f.impulseSetting = true;
                }
                else if (environment.paused) {
                    environment.paused = false;
                }
                else {
                    environment.paused = true;
                    t.schedule(new Update(), 10);
                }
                break;
            case MotionEvent.ACTION_MOVE:
                if (f.ballCreation && environment.areCollidedWithAny(f.x, f.y, (x - event.getX())
                        * (x - event.getX()) + (y - event.getY()) * (y - event.getY()))) f.r = r;
                break;
            case MotionEvent.ACTION_UP:
                if (f.ballCreation) {
                    f.ball = environment.addBall(f.x, f.y, f.r, new Vector());
                    f.ballCreation = false;
                }
                else if (f.impulseSetting) {
                    f.imp = new Vector(x - f.x, y - f.y);
                    f.impulseSetting = false;
                };
                break;
        }
        return true;
    }

    @Override
    public void finish() {
        super.finish();
        environment.clearBalls();
    }

    public class Field extends View {
        double x = -1.0, y = -1.0, r = 0.0;
        boolean ballCreation = false, impulseSetting = false;
        PhysicBall ball;
        Vector imp;
        Paint newBall = new Paint();

        public Field(Context context) {
            super(context);
            newBall.setColor(Color.RED);
            setOnLongClickListener(new OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {
                    x = getX();
                    y = getY();
                    environment.paused = true;
                    ballCreation = true;
                    return true;
                }
            });
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            canvas.drawColor(Color.RED | Color.GREEN);
            environment.drawBalls(canvas);
            if (ballCreation) canvas.drawCircle(((float) x), ((float) y), ((float) r), newBall);
            invalidate();
        }
    }

    public class Update extends TimerTask {
        @Override
        public void run() {
            environment.ballsProcessing();
            if (!environment.paused) {

                t.schedule(new Update(), 10);
            }
        }
    }
}
