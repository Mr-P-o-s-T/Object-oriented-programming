package com.example.lab1ballscollision;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Layout;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.example.lab1ballscollision.environment.Environment;
import com.example.lab1ballscollision.objects.Vector;

import java.sql.Time;
import java.util.Timer;
import java.util.TimerTask;

public class EnvironmentScreen extends AppCompatActivity implements View.OnTouchListener  {
    private Environment environment;
    private Timer t;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Field f = new Field(this);
        f.setOnTouchListener(this);
        setContentView(f);

        environment = new Environment();
        environment.addBall(0.1, 0.1, 1.0, new Vector(50, 50));
        environment.addBall(0.7, 0.4, 2.0, new Vector(50, 20));
        environment.addBall(0.7, 0.6, 2.0, new Vector(50, 30));

        t = new Timer();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        double x = event.getX(), y = event.getY();
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                environment.paused = !environment.paused;
                if (!environment.paused) t.schedule(new Update(), 10);
                break;
            case MotionEvent.ACTION_UP:
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
            if (!environment.paused) t.schedule(new Update(), 10);
        }
    }
}
