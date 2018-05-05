package hackhealth2018.myapplication;

import android.os.Bundle;
import android.support.v4.app.Fragment;

import hackhealth2018.myapplication.chatSession.ChatFragment;
import hackhealth2018.myapplication.chatSession.DataFragment;

public class MainActivity extends BaseActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Fragment chatFragment = ChatFragment.newInstance();
        Fragment dataFragment = DataFragment.newInstance();
        replaceFragment(R.id.frame_tokbox, chatFragment);
        replaceFragment(R.id.frame_data, dataFragment);
    }
}
