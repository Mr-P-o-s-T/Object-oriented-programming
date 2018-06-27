package com.example.lab1ballscollision;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

import com.example.lab1ballscollision.environment.Environment;
import com.example.lab1ballscollision.objects.PhysicBall;
import com.example.lab1ballscollision.objects.Vector;

import java.util.Timer;
import java.util.TimerTask;

public class EnvironmentScreen extends AppCompatActivity implements View.OnTouchListener  {
    private Environment environment;
    private RelativeLayout RL;
    private ImageButton imgB;
    private double x, y;
    private Field f;
    private Timer t;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_environment_screen);

        RL = findViewById(R.id.newRelLayout);

        f = new Field(this);
        f.setOnTouchListener(this);
        f.setLayoutParams(new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT));
        f.setLongClickable(true);

        RL.addView(f);

        imgB = findViewById(R.id.play_pause);
        imgB.bringToFront();

        Point size = new Point();
        getWindowManager().getDefaultDisplay().getSize(size);
        environment = new Environment(size.x, size.y - 60);
        /*environment.addBall(0.1, 0.1, 1.0, new Vector(500, 500));
        environment.addBall(0.7, 0.4, 2.0, new Vector(500, 200));
        environment.addBall(0.7, 0.6, 2.0, new Vector(500, 300));*/

        t = new Timer();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        x = event.getX();
        y = event.getY();
        double m;
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                if (!environment.highligntBall(x, y)) {
                    environment.unhighlightBall();
                }
                break;
            case MotionEvent.ACTION_MOVE:
                if (f.ballCreation && !environment.areCollidedWithAny(f.xC, f.yC, m =
                        Math.sqrt((f.xC - x) * (f.xC - x) + (f.yC - y) * (f.yC - y)) / 10.0)) {
                    environment.returnMass();
                    f.m = m;
                    environment.increaseMass(f.m);
                }
                else if (f.impulseSetting) {
                    f.xS = x; f.yS = y;
                }
                break;
            case MotionEvent.ACTION_CANCEL:
            case MotionEvent.ACTION_UP:
                if (f.ballCreation) {
                    environment.returnMass();
                    environment.addBall(f.xC, f.yC, f.m);
                    f.ballCreation = false;
                }
                else if (f.impulseSetting) {
                    environment.highlighted.speedChanging(new Vector(environment.highlighted.getX()
                            - x,environment.highlighted.getY() - y).multOnScalar(10));
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
        double xC, yC, xS, yS, m;
        boolean ballCreation = false, impulseSetting = false;
        Paint newBall = new Paint(), line = new Paint();

        public Field(Context context) {
            super(context);
            newBall.setColor(Color.RED);
            line.setColor(Color.RED);
            line.setStrokeWidth(3.0f);
            setOnLongClickListener(new OnLongClickListener() {
                @Override
                public boolean onLongClick(View v) {
                    if (environment.highlighted != null) {
                        f.impulseSetting = true;
                    }
                    else if (!f.ballCreation) {
                        f.xC = x; f.yC = y;
                        environment.paused = true;
                        imgB.setImageURI(Uri.parse("android.resource://com.example.lab1ballscollision/" + R.drawable.play));
                        f.ballCreation = true;
                    }
                    return true;
                }
            });
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            canvas.drawColor(Color.parseColor("#FFF5EE"));
            environment.drawBalls(canvas);
            if (ballCreation) {
                canvas.drawCircle((float) xC, (float) yC, (float) (m / environment.getMass() *
                        getWidth() / 20), newBall);
            }
            else if (impulseSetting) {
                double lx = environment.highlighted.getX(),
                        ly = environment.highlighted.getY();
                canvas.drawLine((float) lx, (float) ly, (float) (2 * lx - xS),
                        (float) (2 * ly - yS), line);
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

    public void onPlayPauseClick(View v) {
        environment.paused = !environment.paused;
        if (!environment.paused) {
            imgB.setImageURI(Uri.parse("android.resource://com.example.lab1ballscollision/" + R.drawable.pause));
            t.schedule(new Update(), 10);
        }
        else {
            imgB.setImageURI(Uri.parse("android.resource://com.example.lab1ballscollision/" + R.drawable.play));
        }
    }
}
