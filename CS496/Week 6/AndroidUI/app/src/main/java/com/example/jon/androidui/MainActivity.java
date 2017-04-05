package com.example.jon.androidui;

import android.content.Intent;
import android.database.AbstractCursor;
import android.database.CharArrayBuffer;
import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
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

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView llh = (TextView) findViewById(R.id.button);
        llh.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v){
                Intent intent = new Intent(MainActivity.this, LinearLayoutHorizontal.class);
                startActivity(intent);
            }

        });

        TextView llv = (TextView) findViewById(R.id.button2);
        llv.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, LinearLayoutVertical.class);
                startActivity(intent);
            }
        });

        TextView gridViewItem = (TextView) findViewById(R.id.button3);
        gridViewItem.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, GridLayoutView.class);
                startActivity(intent);
            }
        });

        TextView relativelayout = (TextView) findViewById(R.id.button4);
        relativelayout.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, RelativeLayoutView.class);
                startActivity(intent);
            }
        });



    }
}
