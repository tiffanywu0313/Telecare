package hackhealth2018.myapplication.views.chatSession;

import android.os.Bundle;
import android.support.v4.app.Fragment;

import hackhealth2018.myapplication.util.Strings;
import hackhealth2018.myapplication.views.BaseActivity;
import hackhealth2018.myapplication.R;

public class SessionActivity extends BaseActivity {
    public boolean isDoctor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (getIntent().getExtras() != null)
            isDoctor = getIntent().getExtras().getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

        Fragment chatFragment = ChatFragment.newInstance(isDoctor);
        Fragment dataFragment = DataFragment.newInstance(isDoctor);
        replaceFragment(R.id.frame_tokbox, chatFragment);
        replaceFragment(R.id.frame_data, dataFragment);
    }
}
