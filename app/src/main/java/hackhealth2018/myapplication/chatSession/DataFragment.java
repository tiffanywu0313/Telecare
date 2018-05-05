package hackhealth2018.myapplication.chatSession;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import hackhealth2018.myapplication.BaseFragment;
import hackhealth2018.myapplication.R;

public class DataFragment extends BaseFragment {
    public static Fragment newInstance() {
        Bundle bundle = new Bundle();
        Fragment dataFragment = new DataFragment();
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

        return view;
    }

}
