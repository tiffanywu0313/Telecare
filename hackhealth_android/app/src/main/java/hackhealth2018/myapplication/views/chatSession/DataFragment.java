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

public class DataFragment extends BaseFragment {
    boolean isDoctor;

    public static Fragment newInstance(boolean isDoctor) {
        Bundle bundle = new Bundle();
        Fragment dataFragment = new DataFragment();
        bundle.putBoolean(Strings.SHAREDPREF_IS_DOCTOR, isDoctor);
        dataFragment.setArguments(bundle);
        return dataFragment;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_chat_data, container, false);

        Bundle args = getArguments();
        isDoctor = args.getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

        return view;
    }

}
