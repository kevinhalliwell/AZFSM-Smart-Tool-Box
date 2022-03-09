package com.azfsmtoolbox.app;
/**
 * Created by Terry Ulery and Kevin Halliwell on 5/25/14.
 */

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v7.app.ActionBarActivity;
import android.content.Intent;

import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicBoolean;


public class MainActivity extends ActionBarActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {


        super.onCreate(savedInstanceState);
        setContentView(R.layout.splash);
        Thread splashScreen = new Thread() {
            public void run(){
            try{
               int splashScreen = 0;
               while(splashScreen < 3000){
                   sleep(100);
                   splashScreen = splashScreen +100;
               }
               startActivity(new Intent("com.azfsmtoolbox.Clear"));
             }catch (InterruptedException e) {
                 e.printStackTrace();
             }finally{
                 finish();
             }
            }
        };

        splashScreen.start();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
    }


}
