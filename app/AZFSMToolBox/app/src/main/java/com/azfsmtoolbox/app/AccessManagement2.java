package com.azfsmtoolbox.app;

/**
 * Created by Terry Ulery and Kevin Halliwell on 5/25/14.
 */
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class AccessManagement2 extends Activity {
    EditText username;
    Button button;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.accessmanagement2);
        username = (EditText)findViewById(R.id.username);
        button = (Button)findViewById(R.id.button);
        button.setOnClickListener(buttonListener);
    }

    private View.OnClickListener buttonListener = new View.OnClickListener() {
        public void onClick(View v) {

            if (username.getText().toString().equals("11412339")) {
                Toast.makeText(getApplicationContext(), "Access successfully changed for user 11412339", Toast.LENGTH_LONG).show();
            } else
                Toast.makeText(getApplicationContext(), "Error changing access for user", Toast.LENGTH_LONG).show();
        }

    };
}
