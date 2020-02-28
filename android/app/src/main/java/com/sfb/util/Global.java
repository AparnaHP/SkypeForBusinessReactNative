package com.sfb.util;

import android.graphics.Color;
import com.google.android.material.snackbar.Snackbar;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class Global
{

    public static void setSnackbar(View v, String message) {

        try {
            if (v != null) {
                Snackbar snackbar = Snackbar.make(v, message, Snackbar.LENGTH_LONG);
                View view = snackbar.getView();
                TextView tv = view.findViewById(com.google.android.material.R.id.snackbar_text);
                tv.setTextColor(Color.WHITE);
                tv.setMaxLines(4);
                snackbar.show();
            }
        }
        catch (Exception ee){
            String tag = "error";
            Log.e(tag,ee.toString());
        }
    }
}
