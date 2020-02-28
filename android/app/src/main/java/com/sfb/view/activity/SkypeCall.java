package com.sfb.view.activity;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.PowerManager;
import android.view.View;
import android.view.WindowManager;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.databinding.DataBindingUtil;

import com.microsoft.office.sfb.appsdk.Application;
import com.sfb.R;
import com.sfb.databinding.SkypeCallFrameBinding;
import com.sfb.util.RunTimeHandler;
import com.sfb.view.fragment.SkypeCallFragment;
import com.sfb.viewmodel.SkypeCallVM;

import java.util.Objects;


public class SkypeCall extends AppCompatActivity implements SkypeCallFragment.OnFragmentInteractionListener {


    private SkypeCallVM skypeCallVM;
    private SkypeCallFrameBinding skypeCallFrameBinding;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        skypeCallFrameBinding = DataBindingUtil.setContentView(this, R.layout.skype_call_frame);

        RunTimeHandler runTimeHandler = new RunTimeHandler(this, true);
        if (runTimeHandler.validatePermission(195))
        {
            loadActivity();
        }

    }


    @Override
    public void onFragmentInteraction(String fragmentAction)
    {
        try
        {
            if (fragmentAction.contentEquals(getString(R.string.callFragmentInflated)))
                return;
            if (fragmentAction.contentEquals(getString(R.string.leaveCall)))
                finish();

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if(skypeCallVM != null)
        skypeCallVM.destroy();
    }

    @Override public void onResume() {
        super.onResume();
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }

    @Override public void onPause() {
        super.onPause();
        getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }


    ///////
    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {

        onRequestPermissionsResult(requestCode);
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void onRequestPermissionsResult(int requestCode) {
        if (requestCode == 195 && !ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.READ_PHONE_STATE) && !ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.RECORD_AUDIO) && !ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.CAMERA)) {
            //never ask again, allow
            if (checkSelfPermission(Manifest.permission.READ_PHONE_STATE) == PackageManager.PERMISSION_GRANTED && checkSelfPermission(Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_GRANTED && checkSelfPermission(Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED) {
                loadActivity();
            } else {
                new RunTimeHandler(this, true).permissionDenied();
            }
        }
    }

    private void loadActivity()
    {
        PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        if (pm.isInteractive())
        {
            try
            {
                skypeCallFrameBinding.progressBar.setVisibility(View.VISIBLE);
                String meetingUrl = Objects.requireNonNull(getIntent().getExtras()).getString("meetingUrl");
                String userName = Objects.requireNonNull(getIntent().getExtras()).getString("userName");
                skypeCallVM = new SkypeCallVM(this, skypeCallFrameBinding, Application.getInstance(this.getBaseContext()), meetingUrl, userName);
                skypeCallFrameBinding.setSkypeVM(skypeCallVM);
            }
            catch (Exception e)
            {
                new AlertDialog.Builder(this, R.style.AppThemeAlert)
                .setMessage(getString(R.string.platform_not_supported))
                .setCancelable(false)
                .setPositiveButton(getString(R.string.cancel), (dialog, which) -> finish())
                .create()
                .show();
            }
        }
    }
}
