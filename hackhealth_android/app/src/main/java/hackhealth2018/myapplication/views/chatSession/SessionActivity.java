package hackhealth2018.myapplication.views.chatSession;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.widget.FrameLayout;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.gson.Gson;
import com.opentok.android.OpentokError;
import com.opentok.android.Publisher;
import com.opentok.android.PublisherKit;
import com.opentok.android.Session;
import com.opentok.android.Stream;
import com.opentok.android.Subscriber;

import java.io.IOException;

import butterknife.BindView;
import butterknife.ButterKnife;
import hackhealth2018.myapplication.R;
import hackhealth2018.myapplication.model.SessionResponse;
import hackhealth2018.myapplication.util.Strings;
import hackhealth2018.myapplication.views.BaseActivity;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class SessionActivity extends BaseActivity implements Session.SessionListener {
    public boolean isDoctor;
    private static final int PERMISSION_REQ = 124;
    private static final String TAG = SessionActivity.class.getSimpleName();

    private static String API_KEY = "46113352";
    private static String SESSION_ID = "";
    private static String TOKEN = "";
    private static final int RC_SETTINGS_SCREEN_PERM = 123;
    private static final int RC_VIDEO_APP_PERM = 124;
    private static FirebaseDatabase db = FirebaseDatabase.getInstance();

    @BindView(R.id.frame_tokbox) FrameLayout tokBoxFrame;
    @BindView(R.id.frame_tokbox_self) FrameLayout tokBoxSelfFrame;
//    @BindView(R.id.frame_data) FrameLayout dataFrame;
//    Fragment chatFrag;
    Fragment dataFrag;

    Session mSession;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);

        if (getIntent().getExtras() != null)
            isDoctor = getIntent().getExtras().getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

//        chatFrag = ChatFragment.newInstance(isDoctor);
        dataFrag = DataFragment.newInstance(isDoctor);
//        replaceFragment(R.id.frame_tokbox, chatFrag);
//        replaceFragment(R.id.frame_data, dataFrag);
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
    protected void onStop() {
        super.onStop();
        mPublisher.destroy();
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
        if (!isDoctor)
            onChatStart();
//        ((ChatFragment) chatFrag).onChatStart();
//        ((DataFragment) dataFrag).onChatStart() //TODO
    }

    public void onChatStart() {
        OkHttpClient client = new OkHttpClient();

        String role = isDoctor ? "doctor" : "patient";
        Request request = new Request.Builder()
                .url("https://hackhealth2018.herokuapp.com/" + "room/" +"12894/" + role)
                .build();

        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                Log.d(TAG, "Session start failed: " + e.getMessage());
            }

            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                String responseBody = response.body().string();
                if (response.isSuccessful()) {
                    SessionResponse sessionResponse = new Gson().fromJson(responseBody, SessionResponse.class);
                    if (sessionResponse != null)
                        sessionStart(sessionResponse);
                    else
                        Log.d(TAG, "Session response error");
                    response.close();
                }
            }
        });
        mSession = new Session.Builder(this, API_KEY, SESSION_ID).build();
        mSession.setSessionListener(this);
        mSession.connect(TOKEN);
    }

    private void sessionStart(SessionResponse sessionData) {
        API_KEY = sessionData.getApiKey();
        SESSION_ID = sessionData.getSessionId();
        TOKEN = sessionData.getToken();

        Log.i(TAG, "API_KEY: " + API_KEY);
        Log.i(TAG, "SESSION_ID: " + SESSION_ID);
        Log.i(TAG, "TOKEN: " + TOKEN);

        DatabaseReference myRef = db.getReference().child("Rooms").child("room2");
        myRef.child("sessionID").setValue(SESSION_ID);
        myRef.child("token").setValue(TOKEN);

        mSession = new Session.Builder(this, API_KEY, SESSION_ID).build();
        mSession.setSessionListener(this);
        mSession.connect(TOKEN);
    }

    // == session listener ===
    // SessionListener methods
    private Publisher mPublisher;
    private Subscriber mSubscriber;

    @Override
    public void onConnected(Session session) {
        Log.i(TAG, "Session Connected");
        mPublisher = new Publisher.Builder(this).build();
        mPublisher.setPublisherListener(new PublisherKit.PublisherListener() {
            @Override
            public void onStreamCreated(PublisherKit publisherKit, Stream stream) {
                Log.d(TAG, "Stream created");
            }

            @Override
            public void onStreamDestroyed(PublisherKit publisherKit, Stream stream) {
                Log.d(TAG, "Stream destroyed");
            }

            @Override
            public void onError(PublisherKit publisherKit, OpentokError opentokError) {
                Log.d(TAG, "Stream error: " + opentokError.getMessage());
            }
        });

        tokBoxSelfFrame.addView(mPublisher.getView());
        mSession.publish(mPublisher);
    }

    @Override
    public void onDisconnected(Session session) {
        Log.i(TAG, "Session Disconnected");
    }

    @Override
    public void onStreamReceived(Session session, Stream stream) {
        Log.i(TAG, "Stream Received");
        if (mSubscriber == null) {
            mSubscriber = new Subscriber.Builder(this, stream).build();
            mSession.subscribe(mSubscriber);
            tokBoxFrame.addView(mSubscriber.getView());
        }
    }

    @Override
    public void onStreamDropped(Session session, Stream stream) {
        Log.i(TAG, "Stream Dropped");
    }

    @Override
    public void onError(Session session, OpentokError opentokError) {
        Log.e(TAG, "Session error: " + opentokError.getMessage());
    }
}
