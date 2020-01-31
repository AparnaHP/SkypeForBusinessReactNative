package com.sfb.view.fragment;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;
import com.microsoft.office.sfb.appsdk.Conversation;
import com.microsoft.office.sfb.appsdk.DevicesManager;
import com.sfb.R;
import com.sfb.databinding.FragmentSkypeCallBinding;
import com.sfb.viewmodel.SkypeCallConnectionVM;

import java.util.Objects;


public class SkypeCallFragment extends Fragment {

    private OnFragmentInteractionListener mListener;
    public static Conversation mConversation;
    public static DevicesManager mDevicesManager;
    private SkypeCallConnectionVM skypeCallConnectionVM;


    public static SkypeCallFragment newInstance(Conversation conversation, DevicesManager devicesManager)
    {
        mConversation = conversation;
        mDevicesManager = devicesManager;
        return new SkypeCallFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        FragmentSkypeCallBinding fragmentSkypeCallBinding = DataBindingUtil.inflate(inflater, R.layout.fragment_skype_call, container, false);
        View mRootView = fragmentSkypeCallBinding.getRoot();

        mListener.onFragmentInteraction(Objects.requireNonNull(getActivity()).getString(R.string.callFragmentInflated));

        skypeCallConnectionVM = new SkypeCallConnectionVM(fragmentSkypeCallBinding,mListener,this);
        fragmentSkypeCallBinding.setSkypeConnVM(skypeCallConnectionVM);



        fragmentSkypeCallBinding.endCallButton.setOnClickListener(v -> skypeCallConnectionVM.endCall());

        fragmentSkypeCallBinding.muteAudioButton.setOnClickListener(v -> skypeCallConnectionVM.muteCall());

        fragmentSkypeCallBinding.muteVideoButton.setOnClickListener(v -> skypeCallConnectionVM.muteVideo());


        fragmentSkypeCallBinding.toggleButton.setOnClickListener(v -> skypeCallConnectionVM.toggle());

        fragmentSkypeCallBinding.speakerButton.setOnClickListener(v -> skypeCallConnectionVM.speaker());

        return mRootView;
    }


    @Override
    public void onAttach(@NonNull Context context) {
        super.onAttach(context);
        if (context instanceof OnFragmentInteractionListener)
        mListener = (OnFragmentInteractionListener) context;
    }

    /**
     * Used to interact with parent activity, can add view here as a parameter (View mRootView, String fragmentAction)
     */
    public interface OnFragmentInteractionListener {
        void onFragmentInteraction(String fragmentAction);
    }

}
