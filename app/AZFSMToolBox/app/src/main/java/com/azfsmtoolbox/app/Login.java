package com.azfsmtoolbox.app;

/**
 * Created by Terry Ulery and Kevin Halliwell on 5/25/14.
 */
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class Login extends Activity {
    EditText username;
    Button login;
    AZFSMToolBox mApp;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);
        username = (EditText)findViewById(R.id.username);
        login = (Button)findViewById(R.id.button);
        login.setOnClickListener(loginListener);
        mApp = (AZFSMToolBox) getApplication();
    }
    private OnClickListener loginListener = new OnClickListener() {
        public void onClick(View v) {
            mApp.processor.registerWWID(Integer.valueOf(username.getText().toString()));
            new MyAsyncTask(Login.this).execute();
        }


    };
    private class MyAsyncTask extends AsyncTask<Void, Void, Void> {
        private Context context;
        public MyAsyncTask(Context context) {
            this.context = context;
        }
        @Override
        protected Void doInBackground(Void... params) {
            int sleepCounter = 5000;
            try {
                while (sleepCounter > 0) {
                    Thread.sleep(100);
                    sleepCounter = sleepCounter - 100;
                    if (mApp.registered.get() && sleepCounter < 4000)
                        return null;
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) {
            super.onPostExecute(result);
            if (mApp.registered.get())
                {
                    Toast.makeText(Login.this, "Logged in to server! Access Level: " + mApp.processor.permissions.substring(0, 5), Toast.LENGTH_LONG).show();
                    Intent i = new Intent(Login.this, MainMenu.class);
                    startActivity(i);
                    finish();
                }
            else
                Toast.makeText(Login.this, "No response from server.", Toast.LENGTH_LONG).show();
        }
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            Toast.makeText(context, "WWID sent to server.", Toast.LENGTH_SHORT).show();
        }
    }



 }
