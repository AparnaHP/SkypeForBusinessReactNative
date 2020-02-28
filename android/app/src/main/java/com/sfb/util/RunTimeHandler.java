package com.sfb.util;

import android.Manifest;
import android.app.Activity;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;
import androidx.fragment.app.Fragment;
import androidx.appcompat.app.AlertDialog;
import android.widget.Toast;

import com.sfb.R;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Aparna Prasad on 9/11/2017.
 */

@SuppressWarnings({"Convert2Lambda", "unused"})
public class RunTimeHandler
{
    //permission no
    //195 - camera, audio, phone

    private final Activity activity;
    private Fragment fragment;
    private boolean isActivity;


    public RunTimeHandler(Activity act, Fragment frag)
    {
        activity=act;
        fragment=frag;
    }

    public RunTimeHandler(Activity act, boolean isAct)
    {
        activity=act;
        isActivity = isAct;
    }



    public boolean validatePermission(int permissionno)
    {
        if(permissionno == 195)
        {
           String[] permissions = {Manifest.permission.READ_PHONE_STATE,Manifest.permission.CAMERA,Manifest.permission.RECORD_AUDIO};
           String message=activity.getString(R.string.phonePermission);
           return addPermissionToList(permissions, message, permissionno);
        }
        return false;
    }

    private String[] getPermissionNotGrantedList(String[] permissions)
    {
        final List<String> permissionList = new ArrayList<>();
        for (String permission : permissions)
        {
            if (activity.checkSelfPermission(permission) != PackageManager.PERMISSION_GRANTED)
            {
                permissionList.add(permission);
            }
        }

        return permissionList.toArray(new String[0]);
    }

    private void requestPermission(String[] arrayList, int permissionNo)
    {
        if (isActivity)
            activity.requestPermissions(arrayList, permissionNo);
        else
            fragment.requestPermissions(arrayList, permissionNo);
    }

    private boolean addPermissionToList(final String[] permissions, String message, final int permissionNo)
    {
        if (Build.VERSION.SDK_INT >= 23)// Marshmallow+
        {

            final String[] arrayList = getPermissionNotGrantedList(permissions);

            if (arrayList.length > 0)
            {
                        if (!activity.shouldShowRequestPermissionRationale(arrayList[0]))
                        {
                            //asking permission for the first time and after never ask again
                            showMessageOKCancel(message, new DialogInterface.OnClickListener() {
                                        @Override
                                        public void onClick(DialogInterface dialog, int which)
                                        {
                                            requestPermission(arrayList,permissionNo);
                                        }
                            });
                            return false;

                        }
                        else
                        {
                            //asking permission after denying
                            requestPermission(arrayList,permissionNo);
                            return false;
                        }

            }
            else
            {
                //permission has granted
                return true;
            }

        }
        return true;
    }

    private void showMessageOKCancel(final String message, final DialogInterface.OnClickListener okListener)
    {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                new AlertDialog.Builder(activity, R.style.AppThemeAlert)
                        .setMessage(message)
                        .setPositiveButton(activity.getString(R.string.grant), okListener)
                        .setNegativeButton(activity.getString(R.string.deny), null)
                        .create()
                        .show();
            }
        });
    }

    public void permissionDenied(){
        Intent intent = new Intent();
        intent.setAction(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
        Uri uri = Uri.fromParts("package", activity.getPackageName(), null);
        intent.setData(uri);
        activity.startActivity(intent);

        Toast.makeText(activity,activity.getString(R.string.permissionDenied), Toast.LENGTH_SHORT).show();
    }
}
