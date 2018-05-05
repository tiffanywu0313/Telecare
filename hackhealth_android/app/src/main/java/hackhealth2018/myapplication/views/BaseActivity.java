package hackhealth2018.myapplication.views;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import com.afollestad.materialdialogs.MaterialDialog;
import com.afollestad.materialdialogs.Theme;

public abstract class BaseActivity extends AppCompatActivity implements BaseFragment.BasicFragmentInteractor {
    protected Fragment mCurrentVisibleFragment;
    protected MaterialDialog mProgressDialog;

    @Override
    protected void onStop() {
        super.onStop();
        if (mProgressDialog != null && mProgressDialog.isShowing())
            hideProgressDialog();
        mProgressDialog = null;
    }

    protected void replaceFragment(int activityContainerId, Fragment fragment) {
        replaceFragment(activityContainerId, fragment, null);
    }

    protected void replaceFragment(int activityContainerId, Fragment fragment, String backstackTag) {
        replaceFragment(activityContainerId, fragment, backstackTag, null);
    }

    protected void replaceFragment(int activityContainerId, Fragment fragment, String backstackTag, Bundle args) {
        FragmentTransaction fragmentTransaction = getSupportFragmentManager().beginTransaction();
        //TODO add fun animations
        if (args != null) {
            fragment.setArguments(args);
        }
        if (backstackTag != null)
            fragmentTransaction.addToBackStack(backstackTag);
        fragmentTransaction.replace(activityContainerId, fragment).commit();
        mCurrentVisibleFragment = fragment;
    }

    // == Toasts ====
    @Override
    public void showToast(int res, int duration) {
        Toast.makeText(this, getString(res), duration).show();
    }

    @Override
    public void showToast(String message, int duration) {
        Toast.makeText(this, message, duration).show();
    }

    // === Progress Dialog ===
    @Override
    public void showProgressDialog(String title, String message) {
        if (mProgressDialog == null) createProgressDialog();
        mProgressDialog.setTitle(title);
        mProgressDialog.setContent(message);
        mProgressDialog.setCancelable(false);
        uiChangeOnUiThread(() -> mProgressDialog.show());
    }

    private void createProgressDialog() {
        mProgressDialog = new MaterialDialog.Builder(this)
                .cancelable(false)
                .progress(true, 0)
                .theme(Theme.LIGHT)
                .build();
    }

    @Override
    public void hideProgressDialog() {
        uiChangeOnUiThread(() -> {
            if (mProgressDialog != null && mProgressDialog.isShowing()) {
                mProgressDialog.dismiss();
                mProgressDialog = null;
            }
        });
    }

    @Override
    public void uiChangeOnUiThread(Runnable uiRunnable) {
        runOnUiThread(uiRunnable);
    }
}
