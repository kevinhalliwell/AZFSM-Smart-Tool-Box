package com.azfsmtoolbox.app;

/**
 * Created by Terry Ulery and Kevin Halliwell on 5/25/14.
 */
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


public class UnlockBox extends Activity {
    AZFSMToolBox mApp;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.unlockbox);
        mApp = (AZFSMToolBox) getApplication();
        final Button unlockButton = (Button) findViewById(R.id.unlockButton);
        unlockButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                mApp.processor.unlockBox();
            }
        });
    }
}
