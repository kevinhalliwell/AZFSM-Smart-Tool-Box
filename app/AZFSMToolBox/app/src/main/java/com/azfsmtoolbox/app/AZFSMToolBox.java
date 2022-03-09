package com.azfsmtoolbox.app;
import android.app.Application;
import android.content.Context;
import android.os.Bundle;

import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by Terry on 6/3/2014.
 */
public class AZFSMToolBox extends Application {
    private static Context sContext;
    public MessageProcessor processor;
    public MessageReader reader;
    public LinkedList inBuffer;
    public LinkedList outBuffer;
    public AtomicBoolean registered = new AtomicBoolean(false);
    AZFSMToolBox mApp;

       @Override
    public void onCreate() {
        super.onCreate();
           AZFSMToolBox.sContext = getApplicationContext();
           inBuffer = new LinkedList();
           outBuffer = new LinkedList();
        processor = new MessageProcessor(outBuffer, inBuffer, registered);
        reader = new MessageReader(inBuffer);
        (new Thread(processor)).start();
        (new Thread(reader)).start();
    }

    public void testMethod()
    {
        //do something
    }
    public static Context getContext()
    {
        return sContext;
    }
}
