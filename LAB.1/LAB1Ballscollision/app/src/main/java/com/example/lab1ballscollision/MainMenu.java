package com.example.lab1ballscollision;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainMenu extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_menu);
    }

    public void onStartClick(View view) {
        Intent intent = new Intent(MainMenu.this, PropertiesActivity.class);
        startActivity(intent);
    }

    public void onExitClick(View view) {
        finish();
        Toast.makeText(this, "Already leaving?", Toast.LENGTH_SHORT).show();
    }
}
