package hackhealth2018.hackhealth2018.views;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.widget.Toast;

public class BaseFragment extends Fragment {
    protected static final String TAG = BaseFragment.class.getSimpleName();
    private BasicFragmentInteractor mFragmentInteractor;
    protected Context mContext;

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        mContext = context;

        if (context instanceof BasicFragmentInteractor) {
            mFragmentInteractor = (BasicFragmentInteractor) context;
        } else {
            throw new RuntimeException("Activity does not implement BasicFragmentInteractor");
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    protected void showToast(String message) {
        showToast(message, Toast.LENGTH_LONG);
    }

    protected void showToast(String message, int length) {
        mFragmentInteractor.showToast(message, length);
    }

    protected void showToast(int messageRes, int length) {
        mFragmentInteractor.showToast(messageRes, length);
    }

    protected void runOnUiThread(Runnable runnable) {
        mFragmentInteractor.uiChangeOnUiThread(runnable);
    }

    protected void showProgressDialog(String title, String message) {
        mFragmentInteractor.showProgressDialog(title, message);
    }

    protected void hideProgressDialog() {
        mFragmentInteractor.hideProgressDialog();
    }

    public interface BasicFragmentInteractor {
        void showProgressDialog(String title, String message);
        void hideProgressDialog();
        void showToast(int res, int duration);
        void showToast(String message, int duration);
        void uiChangeOnUiThread(Runnable uiRunnable);
    }
}
