package hackhealth2018.hackhealth2018.views.chatSession;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import hackhealth2018.hackhealth2018.R;
import hackhealth2018.hackhealth2018.util.Strings;
import hackhealth2018.hackhealth2018.views.BaseFragment;

public class ChatFragment extends BaseFragment {
    private static final String TAG = ChatFragment.class.getSimpleName();
    boolean isDoctor;

//    private Session mSession;

//    private static String API_KEY = "46113352";
//    private static String SESSION_ID = "";
//    private static String TOKEN = "9b4dfb5f819424cf7c8924ee649e39a4ce97290c";
//    private static final int RC_SETTINGS_SCREEN_PERM = 123;
//    private static final int RC_VIDEO_APP_PERM = 124;

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

//    public void onChatStart() {
//        OkHttpClient client = new OkHttpClient();
//
//        String role = isDoctor ? "doctor" : "patient";
//        Request request = new Request.Builder()
//                .url("https://hackhealth2018.herokuapp.com/" + "room/" +"12894/" + role)
//                .build();
//
//        client.newCall(request).enqueue(new Callback() {
//            @Override
//            public void onFailure(@NonNull Call call, @NonNull IOException e) {
//                Log.d(TAG, "Session start failed: " + e.getMessage());
//            }
//
//            @Override
//            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
//                String responseBody = response.body().string();
//                if (response.isSuccessful()) {
//                    SessionResponse sessionResponse = new Gson().fromJson(responseBody, SessionResponse.class);
//                    if (sessionResponse != null)
//                        sessionStart(sessionResponse);
//                    else
//                        Log.d(TAG, "Session response error");
//                    response.close();
//                }
//            }
//        });
//        mSession = new Session.Builder(mContext, API_KEY, SESSION_ID).build();
//        mSession.setSessionListener(this);
//        mSession.connect(TOKEN);
//    }
//
//    private void sessionStart(SessionResponse sessionData) {
//        API_KEY = sessionData.getApiKey();
//        SESSION_ID = sessionData.getSessionId();
//        TOKEN = sessionData.getToken();
//
//        Log.i(TAG, "API_KEY: " + API_KEY);
//        Log.i(TAG, "SESSION_ID: " + SESSION_ID);
//        Log.i(TAG, "TOKEN: " + TOKEN);
//
//        mSession = new Session.Builder(mContext, API_KEY, SESSION_ID).build();
//        mSession.setSessionListener(this);
//        mSession.connect(TOKEN);
//    }
//
//    // == session listener ===
//    // SessionListener methods
//
//    @Override
//    public void onConnected(Session session) {
//        Log.i(TAG, "Session Connected");
//    }
//
//    @Override
//    public void onDisconnected(Session session) {
//        Log.i(TAG, "Session Disconnected");
//    }
//
//    @Override
//    public void onStreamReceived(Session session, Stream stream) {
//        Log.i(TAG, "Stream Received");
//    }
//
//    @Override
//    public void onStreamDropped(Session session, Stream stream) {
//        Log.i(TAG, "Stream Dropped");
//    }
//
//    @Override
//    public void onError(Session session, OpentokError opentokError) {
//        Log.e(TAG, "Session error: " + opentokError.getMessage());
//    }

}
