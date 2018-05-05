package hackhealth2018.myapplication;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

public abstract class BaseActivity extends AppCompatActivity implements BaseFragment.BasicFragmentInteractor {
    protected Fragment mCurrentVisibleFragment;

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

    @Override
    public void showToast(int res, int duration) {
        Toast.makeText(this, getString(res), duration).show();
    }

    @Override
    public void showToast(String message, int duration) {
        Toast.makeText(this, message, duration).show();
    }

    @Override
    public void uiChangeOnUiThread(Runnable uiRunnable) {
        runOnUiThread(uiRunnable);
    }
}
