package hackhealth2018.hackhealth2018.views.sessionSelection;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;

import butterknife.ButterKnife;
import butterknife.OnClick;
import hackhealth2018.hackhealth2018.util.Strings;
import hackhealth2018.hackhealth2018.views.BaseActivity;
import hackhealth2018.hackhealth2018.R;
import hackhealth2018.hackhealth2018.views.chatSession.SessionActivity;

public class SelectSessionActivity extends BaseActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_session_select);

        ButterKnife.bind(this);
    }

    @OnClick(R.id.bttn_start_doc)
    public void startDocSession() {
        Intent intent = new Intent(this, SessionActivity.class);
        Bundle bundle = new Bundle();
        bundle.putBoolean(Strings.SHAREDPREF_IS_DOCTOR, true);
        intent.putExtras(bundle);
        startActivity(intent);
    }

    @OnClick(R.id.bttn_start_patient)
    public void startPatientSession() {
        Intent intent = new Intent(this, SessionActivity.class);
        Bundle bundle = new Bundle();
        bundle.putBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);
        intent.putExtras(bundle);
        startActivity(intent);
    }
}
