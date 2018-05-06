package hackhealth2018.hackhealth2018.views.chatSession;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;

import hackhealth2018.hackhealth2018.R;
import hackhealth2018.hackhealth2018.util.Strings;
import hackhealth2018.hackhealth2018.views.BaseActivity;

public class SessionActivity extends BaseActivity {
    public boolean isDoctor;
    private static final int PERMISSION_REQ = 124;

    Fragment chatFrag;
    Fragment dataFrag;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (getIntent().getExtras() != null)
            isDoctor = getIntent().getExtras().getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

        chatFrag = ChatFragment.newInstance(isDoctor);
        dataFrag = DataFragment.newInstance(isDoctor);
        replaceFragment(R.id.frame_tokbox, chatFrag);
        replaceFragment(R.id.frame_data, dataFrag);
    }

    @Override
    protected void onStart() {
        super.onStart();
        if ((ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) &&
                ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
            // permission not granted
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.CAMERA, Manifest.permission.RECORD_AUDIO},
                    PERMISSION_REQ);
        } else {
            // permission granted
            startConnection();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (requestCode == PERMISSION_REQ) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED &&
                    grantResults[1] == PackageManager.PERMISSION_GRANTED)
                startConnection();
        }
    }

    private void startConnection() {
        ((ChatFragment) chatFrag).onChatStart();
//        ((DataFragment) dataFrag).onChatStart() //TODO
    }
}
