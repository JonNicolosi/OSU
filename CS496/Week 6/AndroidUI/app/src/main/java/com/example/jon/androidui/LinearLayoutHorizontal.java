package com.example.jon.androidui;

import android.content.Intent;
import android.database.AbstractCursor;
import android.database.CharArrayBuffer;
import android.database.Cursor;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.CursorAdapter;
import android.widget.GridLayout;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

public class LinearLayoutHorizontal extends AppCompatActivity{

    @Override
    protected void onCreate(Bundle savedInstanceState){

        super.onCreate(savedInstanceState);
        setContentView(R.layout.linearlayouthorizontal);

        final Button button1 = (Button) findViewById(R.id.button8);
        button1.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_UP) {
                    button1.setBackgroundColor(Color.RED);
                } else if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    button1.setBackgroundColor(Color.BLUE);
                }
                return false;
            }

        });

        final Button button2 = (Button) findViewById(R.id.button9);
        button2.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_UP) {
                    button2.setBackgroundColor(Color.BLACK);
                } else if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    button2.setBackgroundColor(Color.RED);
                }
                return false;
            }

        });

        final Button button3 = (Button) findViewById(R.id.button10);
        button3.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_UP) {
                    button3.setBackgroundColor(Color.GREEN);
                } else if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    button3.setBackgroundColor(Color.YELLOW);
                }
                return false;
            }

        });

        final Button button4 = (Button) findViewById(R.id.button11);
        button4.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_UP) {
                    button4.setBackgroundColor(Color.RED);
                } else if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    button4.setBackgroundColor(Color.DKGRAY);
                }
                return false;
            }

        });

        final Button button5 = (Button) findViewById(R.id.button12);
        button5.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_UP) {
                    button5.setBackgroundColor(Color.GREEN);
                } else if(event.getAction() == MotionEvent.ACTION_DOWN) {
                    button5.setBackgroundColor(Color.MAGENTA);
                }
                return false;
            }

        });





    }



}
