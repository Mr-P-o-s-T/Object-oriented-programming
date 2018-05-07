package com.example.lab1ballscollision;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.RelativeLayout;

import com.example.lab1ballscollision.environment.Environment;
import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Vector;

import java.util.Timer;
import java.util.TimerTask;

public class EnvironmentScreen extends AppCompatActivity implements View.OnTouchListener  {
    private Environment environment;
    private RelativeLayout RL;
    Field f;
    private Timer t;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        RL = (RelativeLayout) getDelegate().findViewById(R.id.newRelLayout);

        /*f = new Field(this);
        f.setOnTouchListener(this);
        f.setLayoutParams(new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT));

        RL.addView(f);*/
        setContentView(R.layout.activity_environment_screen);

        environment = new Environment();
        environment.addBall(0.1, 0.1, 10.0, new Vector(50, 50));
        environment.addBall(0.7, 0.4, 20.0, new Vector(50, 20));
        environment.addBall(0.7, 0.6, 20.0, new Vector(50, 30));

        t = new Timer();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        double x = event.getX(), y = event.getY(), m;
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                if (!environment.highligntBall(x, y)) {
                    environment.unhighlightBall();
                    environment.paused = !environment.paused;
                    if (!environment.paused) t.schedule(new Update(), 10);
                }
                else {

                }
                break;
            case MotionEvent.ACTION_MOVE:
                if (f.ballCreation && !environment.areCollidedWithAny(f.xC, f.yC, m = Math.sqrt((f.xC - event.getX()) * (f.xC - event.getX()) + (f.yC - event.getY()) * (f.yC - event.getY())))) {
                    environment.returnMass();
                    f.m = m;
                    environment.increaseMass(f.m);
                }
                else if (f.impulseSetting) {
                    f.x = x; f.y = y;
                }
                break;
            case MotionEvent.ACTION_CANCEL:
            case MotionEvent.ACTION_UP:
                if (f.ballCreation) {
                    environment.returnMass();
                    f.ball = environment.addBall(f.xC / f.getWidth(), f.yC / f.getHeight(), f.m, new Vector());
                    f.impulseSetting = true;
                }
                else if (f.impulseSetting) {
                    f.imp = new Vector(f.x - x, f.y - y);
                    f.impulseSetting = false;
                }
                break;
        }
        return false;
    }

    @Override
    public void finish() {
        super.finish();
        environment.clearBalls();
    }

    public class Field extends View {
        double xC, yC, m, x, y;
        boolean ballCreation = false, impulseSetting = false;
        PhysicBall ball;
        Vector imp;
        Paint newBall = new Paint(), line = new Paint();

        public Field(Context context) {
            super(context);
            newBall.setColor(Color.RED);
            line.setColor(Color.RED);
            line.setStrokeWidth(3.0f);
            setOnLongClickListener(new OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {
                    if (f.ballCreation) {
                        f.ballCreation = false;
                        f.impulseSetting = true;
                    }
                    else {
                        f.xC = x; f.yC = y;
                        environment.paused = true;
                        f.ballCreation = true;
                    }
                    return true;
                }
            });
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            canvas.drawColor(Color.RED | Color.GREEN);
            environment.drawBalls(canvas);
            if (ballCreation) {
                canvas.drawCircle(((float) xC), ((float) yC), (float) (m / environment.getMass() / environment.xMax * getWidth()), newBall);
            }
            else if (impulseSetting) {
                canvas.drawLine(((float) xC), ((float) yC), (float) (2 * xC - x), (float) (2 * yC - y), line);
            }
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
