package com.sfb;

import android.content.Intent;

import com.sfb.view.activity.SkypeCall;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;

import javax.annotation.Nonnull;

class ActivityStarterModule extends ReactContextBaseJavaModule
{

    ActivityStarterModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Nonnull
    @Override
    public String getName() {
        return "ActivityStarter";
    }

    @ReactMethod
    void loadSkypeForBusiness(String meetingUrl, String displayName)
    {
        ReactApplicationContext context = getReactApplicationContext();
        Intent intent = new Intent(context, SkypeCall.class);
        intent.putExtra("meetingUrl", meetingUrl);
        intent.putExtra("userName", displayName);
        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent);
    }
}