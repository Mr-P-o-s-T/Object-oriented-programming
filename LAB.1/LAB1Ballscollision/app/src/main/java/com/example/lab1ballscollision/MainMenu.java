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

<<<<<<< HEAD
    @Override
    public void finish() {
        super.finish();
        Toast.makeText(this, "Already leaving?", Toast.LENGTH_SHORT).show();
    }

=======
>>>>>>> 8cdc784043e14292c85a80b590f34591e0e9263c
    public void onStartClick(View view) {
        Intent intent = new Intent(MainMenu.this, PropertiesActivity.class);
        startActivity(intent);
    }

    public void onExitClick(View view) {
        finish();
<<<<<<< HEAD
=======
        Toast.makeText(this, "Already leaving?", Toast.LENGTH_SHORT).show();
>>>>>>> 8cdc784043e14292c85a80b590f34591e0e9263c
    }
}
