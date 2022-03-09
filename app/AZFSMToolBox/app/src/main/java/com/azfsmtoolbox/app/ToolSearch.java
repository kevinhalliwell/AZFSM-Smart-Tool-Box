package com.azfsmtoolbox.app;

/**
 * Created by Terry Ulery and Kevin Halliwell on 5/25/14.
 */
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class ToolSearch extends Activity {
    EditText username;
    Button button;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.toolsearch);
        username = (EditText)findViewById(R.id.username);
        button = (Button)findViewById(R.id.button);
        button.setOnClickListener(buttonListener);
    }

    private View.OnClickListener buttonListener = new View.OnClickListener() {
        public void onClick(View v) {

            if (username.getText().toString().equals("306")) {
                Toast.makeText(getApplicationContext(), "Tool located in bay 202", Toast.LENGTH_LONG).show();
            } else
                Toast.makeText(getApplicationContext(), "Tool located in bay 308", Toast.LENGTH_LONG).show();
        }

    };

}