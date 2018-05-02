package com.example.lab1ballscollision;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.example.lab1ballscollision.environment.Environment;
import com.example.lab1ballscollision.objects.Gravity;

public class PropertiesActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_properties);
    }

    public void onStartButtonClick(View v) {
        Environment.xMax = Double.parseDouble(((EditText) findViewById(R.id.xMax)).getText().toString());
        Environment.yMax = Double.parseDouble(((EditText) findViewById(R.id.yMax)).getText().toString());
        Environment.dT = Double.parseDouble(((EditText) findViewById(R.id.secsPerSec)).getText().toString());
        Environment.gravity = new Gravity(
                Double.parseDouble(((EditText) findViewById(R.id.X)).getText().toString()),
                Double.parseDouble(((EditText) findViewById(R.id.Y)).getText().toString()),
                Double.parseDouble(((EditText) findViewById(R.id.Z)).getText().toString()));
        int id = ((RadioGroup) findViewById(R.id.accuracyRG)).getCheckedRadioButtonId();
        switch (id) {
            case R.id.lowRB: Environment.epsilon = 0.1;
                break;
            case R.id.mediumRB: Environment.epsilon = 0.01;
                break;
            case R.id.highRB: Environment.epsilon = 0.001;
                break;
            case R.id.ultraRB: Environment.epsilon = 0.0001;
                break;
        }
        finish();
        Toast.makeText(this, Double.toString(Environment.xMax) + " " + Environment.yMax + " " + Environment.dT + " " + Environment.epsilon, Toast.LENGTH_LONG).show();
    }
}
