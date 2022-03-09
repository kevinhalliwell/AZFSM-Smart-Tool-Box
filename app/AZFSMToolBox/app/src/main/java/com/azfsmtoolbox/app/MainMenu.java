package com.azfsmtoolbox.app;

/**
 * Created by Terry Ulery and Kevin Halliwell on 5/26/14.
 */
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


public class MainMenu extends Activity {


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mainmenu);

        final Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent launchactivity = new Intent(MainMenu.this, ToolSearch.class);
                startActivity(launchactivity);
            }
        });

        final Button button1 = (Button) findViewById(R.id.button1);
        button1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent launchactivity = new Intent(MainMenu.this, ViewInventory.class);
                startActivity(launchactivity);
            }
        });

        final Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent launchactivity = new Intent(MainMenu.this, ToolBoxManagement.class);
                startActivity(launchactivity);
            }
        });

        final Button button3 = (Button) findViewById(R.id.button3);
        button3.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent launchactivity = new Intent(MainMenu.this, AccessManagement.class);
                startActivity(launchactivity);
            }
        });

        final Button button4 = (Button) findViewById(R.id.button4);
        button4.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent launchactivity = new Intent(MainMenu.this, UnlockBox.class);
                startActivity(launchactivity);
            }
        });
    }
}