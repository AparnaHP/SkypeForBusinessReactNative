package com.sfb.viewmodel;

import android.view.View;
import android.widget.ProgressBar;

import androidx.fragment.app.FragmentTransaction;

import com.microsoft.office.sfb.appsdk.AnonymousSession;
import com.microsoft.office.sfb.appsdk.Application;
import com.microsoft.office.sfb.appsdk.ConfigurationManager;
import com.microsoft.office.sfb.appsdk.Conversation;
import com.microsoft.office.sfb.appsdk.Observable;
import com.sfb.R;
import com.sfb.databinding.SkypeCallFrameBinding;
import com.sfb.util.Global;
import com.sfb.view.activity.SkypeCall;
import com.sfb.view.fragment.SkypeCallFragment;

import java.net.URI;


public class SkypeCallVM
{
    private final SkypeCallFrameBinding skypeCallFrameBinding;
    private final SkypeCall activity;
    private final Application mApplication;
    private final String meetingURL;
    private final String userName;
    private final ProgressBar progressBar;
    private Conversation mConversation;

    public SkypeCallVM(SkypeCall activity, SkypeCallFrameBinding skypeCallFrameBinding, Application mApplication, String meetingUrl,String userName)
    {
        this.skypeCallFrameBinding=skypeCallFrameBinding;
        this.activity=activity;
        this.mApplication=mApplication;
        this.meetingURL=meetingUrl;
        this.userName=userName;
        progressBar=skypeCallFrameBinding.progressBar;
        mApplication.getConfigurationManager().setEndUserAcceptedVideoLicense();
        joinTheCall();
    }

    private void setMeetingConfiguration()
    {
        ConfigurationManager configurationManager = mApplication.getConfigurationManager();
        configurationManager.enablePreviewFeatures(true);
        configurationManager.setRequireWiFiForVideo(false);
        configurationManager.setRequireWiFiForAudio(false);
        configurationManager.setMaxVideoChannelCount(1);
    }


    private void joinTheCall()
    {
        try
        {
            progressBar.setVisibility(View.VISIBLE);

            setMeetingConfiguration();

            AnonymousSession mAnonymousSession = mApplication.joinMeetingAnonymously(userName, new URI(meetingURL));

            mConversation = mAnonymousSession.getConversation();
            if (mConversation != null)
                mConversation.addOnPropertyChangedCallback(new ConversationPropertyChangeListener());


        } catch (Exception ex) {
            ex.printStackTrace();
        }

    }

    private void loadCallFragment()
    {
        FragmentTransaction fragmentTransaction = activity.getSupportFragmentManager().beginTransaction();
        try
        {
            SkypeCallFragment mCallFragment = SkypeCallFragment.newInstance(mConversation, mApplication.getDevicesManager());
            fragmentTransaction.add(R.id.fragment_container, mCallFragment, "video");
            fragmentTransaction.commitAllowingStateLoss();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void destroy()
    {
        try
        {
            if (mConversation.canLeave())
            mConversation.leave();

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Callback implementation for listening for conversation property changes.
     */
    class ConversationPropertyChangeListener extends Observable.OnPropertyChangedCallback {

        ConversationPropertyChangeListener() {
        }

        /**
         * onProperty changed will be called by the Observable instance on a property change.
         *
         * @param sender     Observable instance.
         * @param propertyId property that has changed.
         */
        @Override
        public void onPropertyChanged(Observable sender, int propertyId)
        {

            Conversation conversation = (Conversation) sender;
            if (propertyId == Conversation.STATE_PROPERTY_ID) {
                if (conversation.getState() == Conversation.State.ESTABLISHED) {

                    try
                    {
                        loadCallFragment();
                        progressBar.setVisibility(View.GONE);
                    }
                    catch (Exception e) {

                        e.printStackTrace();
                        Global.setSnackbar(skypeCallFrameBinding.mainLayout,activity.getString(R.string.cannot_start_meeting));
                    }
                }
            }
        }
    }
}

