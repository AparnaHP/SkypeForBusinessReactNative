package com.sfb.viewmodel;

import android.view.TextureView;
import android.view.View;

import androidx.core.content.ContextCompat;

import com.microsoft.media.MMVRSurfaceView;
import com.microsoft.office.sfb.appsdk.AudioService;
import com.microsoft.office.sfb.appsdk.Conversation;
import com.microsoft.office.sfb.appsdk.MessageActivityItem;
import com.sfb.R;
import com.sfb.databinding.FragmentSkypeCallBinding;
import com.sfb.util.ConversationHelper;
import com.sfb.view.activity.SkypeCall;
import com.sfb.view.fragment.SkypeCallFragment;


public class SkypeCallConnectionVM implements ConversationHelper.ConversationCallback
{
    private final FragmentSkypeCallBinding fragmentSkypeCallBinding;
    private final SkypeCall activity;
    private ConversationHelper mConversationHelper;
    private SkypeCallFragment.OnFragmentInteractionListener mListener;
    private boolean canSetPausedFirstTime=true;
    public static final boolean isDefaultOptionsOn = true; //this will enable all the buttons when loading

    public SkypeCallConnectionVM(FragmentSkypeCallBinding fragmentSkypeCallBinding, SkypeCallFragment.OnFragmentInteractionListener mListener, SkypeCallFragment skypeCallFragment) {

        this.fragmentSkypeCallBinding=fragmentSkypeCallBinding;
        this.activity = (SkypeCall) skypeCallFragment.getActivity();
        this.mListener=mListener;

        init();
    }

    private void init()
    {
        TextureView mPreviewVideoTextureView = fragmentSkypeCallBinding.selfParticipantVideoView;
        MMVRSurfaceView mParticipantVideoSurfaceView = fragmentSkypeCallBinding.mmvrSurfaceViewId;
        mParticipantVideoSurfaceView.setActivated(true);
        mPreviewVideoTextureView.setActivated(true);

        if (mConversationHelper == null)
        mConversationHelper = new ConversationHelper(SkypeCallFragment.mConversation, SkypeCallFragment.mDevicesManager, mPreviewVideoTextureView, mParticipantVideoSurfaceView, this,activity,fragmentSkypeCallBinding,this);

        showHideButtons(true);
        mConversationHelper.initLoudSpeaker();

    }

    public void endCall()
    {
            try
            {
                if(SkypeCallFragment.mConversation.canLeave())
                    SkypeCallFragment.mConversation.leave();

                if (mListener != null)
                {
                    mListener.onFragmentInteraction(activity.getString(R.string.leaveCall));
                    mListener = null;
                    mConversationHelper.stopVideoService();
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
                if (mListener != null)
                {
                    mListener.onFragmentInteraction(activity.getString(R.string.leaveCall));
                    mListener = null;
                    mConversationHelper.stopVideoService();
                }
            }
    }

    public void muteCall()
    {
        mConversationHelper.toggleMute();
    }

    public void muteVideo()
    {
        if (SkypeCallFragment.mConversation.getVideoService().canSetPaused()) {
            mConversationHelper.toggleVideoPaused();
        }
    }


    public void toggle()
    {
        if (SkypeCallFragment.mConversation.getVideoService().canSetActiveCamera())
        mConversationHelper.changeActiveCamera();

    }

    public void speaker()
    {
        mConversationHelper.changeSpeakerEndpoint();
    }

    @Override
    public void onSelfAudioMuteChanged(AudioService.MuteState newMuteState)
    {
        switch (newMuteState) {
            case MUTED:
                fragmentSkypeCallBinding.muteAudioButton.setImageDrawable(ContextCompat.getDrawable(activity,R.drawable.microphone_off));
                break;
            case UNMUTED:
                fragmentSkypeCallBinding.muteAudioButton.setImageDrawable(ContextCompat.getDrawable(activity,R.drawable.microphone));
                break;
            case UNMUTING:
                fragmentSkypeCallBinding.muteAudioButton.setImageDrawable(ContextCompat.getDrawable(activity,R.drawable.dots_horizontal));
                break;
            default:
        }
    }


    @Override
    public void onConversationStateChanged(Conversation.State state)
    {
        //empty
    }


    @Override
    public void onCanStartVideoServiceChanged(boolean canStartVideoService) {

        if (canStartVideoService) {
            mConversationHelper.startOutgoingVideo();
            mConversationHelper.startIncomingVideo();
            mConversationHelper.ensureVideoIsStartedAndRunning();
        }
    }

    @Override
    public void onCanSetPausedVideoServiceChanged(boolean canSetPausedVideoService) {
        //edited-a1
        if(canSetPausedVideoService && canSetPausedFirstTime)
        {
            if(SkypeCallConnectionVM.isDefaultOptionsOn)
            {
                try
                {
                    stopCameraNotify();
                    SkypeCallFragment.mConversation.getVideoService().setPaused(false);
                    mConversationHelper.ensureVideoIsStartedAndRunning();
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }

            }
            else
            {
                fragmentSkypeCallBinding.muteVideoButton.setImageDrawable(ContextCompat.getDrawable(activity,R.drawable.video_off));
            }

            canSetPausedFirstTime=false;
        }
    }

    public void startCameraNotify()
    {
        fragmentSkypeCallBinding.connectingCamLabel.setVisibility(View.VISIBLE);
        showHideButtons(false);
        fragmentSkypeCallBinding.muteVideoButton.setEnabled(false);
    }

    private void stopCameraNotify()
    {
        fragmentSkypeCallBinding.connectingCamLabel.setVisibility(View.GONE);
        fragmentSkypeCallBinding.muteVideoButton.setEnabled(true);
    }

    public void showHideButtons(boolean isHide)
    {
        if(isHide) {
            fragmentSkypeCallBinding.muteAudioButton.setVisibility(View.INVISIBLE);
            fragmentSkypeCallBinding.muteVideoButton.setVisibility(View.INVISIBLE);
            fragmentSkypeCallBinding.speakerButton.setVisibility(View.INVISIBLE);
        }
        else
        {
            fragmentSkypeCallBinding.loadingView.setVisibility(View.GONE);
            fragmentSkypeCallBinding.muteAudioButton.setVisibility(View.VISIBLE);
            fragmentSkypeCallBinding.muteVideoButton.setVisibility(View.VISIBLE);
            fragmentSkypeCallBinding.speakerButton.setVisibility(View.VISIBLE);
        }

    }

    @Override
    public void onCanSetActiveCameraChanged(boolean canSetActiveCamera) {

        if (mListener != null)
            mListener.onFragmentInteraction(activity.getString(R.string.canToggleCamera));

        if(canSetActiveCamera)
        {
            fragmentSkypeCallBinding.muteVideoButton.setImageDrawable(ContextCompat.getDrawable(activity,R.drawable.video));
            fragmentSkypeCallBinding.textureViewFrame.setVisibility(View.VISIBLE);
        }
        else
        {
            fragmentSkypeCallBinding.muteVideoButton.setImageDrawable(ContextCompat.getDrawable(activity,R.drawable.video_off));
            fragmentSkypeCallBinding.textureViewFrame.setVisibility(View.GONE);
        }

    }

    @Override
    public void onCanSendMessage(boolean canSendMessage)
    {
        //empty
    }

    @Override
    public void onMessageReceived(MessageActivityItem newMessage)
    {
        //empty
    }
}

