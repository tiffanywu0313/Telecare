package hackhealth2018.myapplication.views.chatSession;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import hackhealth2018.myapplication.util.Strings;
import hackhealth2018.myapplication.views.BaseFragment;
import hackhealth2018.myapplication.R;

public class ChatFragment extends BaseFragment {

    boolean isDoctor;

    public static Fragment newInstance(boolean isDoctor) {
        Bundle bundle = new Bundle();
        bundle.putBoolean(Strings.SHAREDPREF_IS_DOCTOR, isDoctor);
        Fragment chatFragment = new ChatFragment();
        chatFragment.setArguments(bundle);
        return chatFragment;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_chat_video, container, false);

        Bundle args = getArguments();
        isDoctor = args.getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

        return view;
    }
}
