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

public class LinearLayoutVertical extends AppCompatActivity{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.linearlayoutvertical);
        changeTextonce();
    }

    private void changeTextonce(){

        final TextView changingText = (TextView) findViewById(R.id.textView);
        Button button5 = (Button) findViewById(R.id.button5);
        final TextView changingText2 = (TextView) findViewById(R.id.textView2);
        Button button6 = (Button) findViewById(R.id.button6);
        final TextView changingText3 = (TextView) findViewById(R.id.textView3);
        Button button7 = (Button) findViewById(R.id.button7);
        final TextView changingText4 = (TextView) findViewById(R.id.textView4);
        Button button13 = (Button) findViewById(R.id.button13);
        final TextView changingText5 = (TextView) findViewById(R.id.textView5);
        Button button14 = (Button) findViewById(R.id.button14);

        button5.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                changingText.setText("First Button");
            }
        });

        button6.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                changingText2.setText("Second Button");
            }
        });
        button7.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                changingText3.setText("Third Button");
            }
        });
        button13.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                changingText4.setText("Fourth Button");
            }
        });
        button14.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                changingText5.setText("Fifth Button");
            }
        });


    }

}
