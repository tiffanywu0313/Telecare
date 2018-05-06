package hackhealth2018.myapplication.views.chatSession;

import android.content.Context;
import android.os.Bundle;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import hackhealth2018.myapplication.R;
import hackhealth2018.myapplication.util.Strings;
import hackhealth2018.myapplication.views.BaseFragment;

public class DataFragment extends BaseFragment {
    boolean isDoctor;
    private ViewPager mViewPager;

    public static Fragment newInstance(boolean isDoctor) {
        Bundle bundle = new Bundle();
        Fragment dataFragment = new DataFragment();
        bundle.putBoolean(Strings.SHAREDPREF_IS_DOCTOR, isDoctor);
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
        View view2 = inflater.inflate(R.layout.fragment_chat_data2, container, false);

        Bundle args = getArguments();
        isDoctor = args.getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

        if (isDoctor == true)
            return view;
        else
            return view2;
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        mViewPager = (ViewPager) view.findViewById(R.id.viewpager);
        mViewPager.setAdapter(new FragmentPagerAdapter());
        TabLayout tablayout = getActivity().findViewById(R.id.tab_chatdata);
        tablayout.setupWithViewPager(mViewPager);
    }

    class FragmentPagerAdapter extends PagerAdapter {
        private String[] tabTitles = new String[]{"Heart Rate", "Breathing Rate"};

        @Override
        public CharSequence getPageTitle(int positon){
            return tabTitles[positon];
        }

        @Override
        public int getCount() {
            return 2;
        }

        @Override
        public boolean isViewFromObject(View view, Object o) {
            return o == view;
        }

        @Override
        public Object instantiateItem(ViewGroup container, int position) {
            View view = getActivity().getLayoutInflater().inflate(R.layout.contentindatafragment,
                    container, false);
            View view2 = getActivity().getLayoutInflater().inflate(R.layout.contentindatafragment2,
                    container, false);

            if(position == 0){
                container.addView(view);
                return view;}
            else{
                container.addView(view2);
                return view2;}
        }

        @Override
        public void destroyItem(ViewGroup container, int position, Object object) {
            container.removeView((View) object);
        }
    }
}