package hackhealth2018.hackhealth2018.views.chatSession;

import android.content.Context;
import android.os.Bundle;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import butterknife.BindView;
import butterknife.ButterKnife;
import hackhealth2018.hackhealth2018.R;
import hackhealth2018.hackhealth2018.util.Strings;
import hackhealth2018.hackhealth2018.views.BaseFragment;


public class DataFragment extends BaseFragment {
    boolean isDoctor;
    boolean isHeartRateTab = true;
    Integer heartRate;
    String heartBPM = "Beats per Min";
    Integer breathingRate;
    String breathBPM = "Breathe per Min";

    @BindView(R.id.text_live_data)
    TextView mLiveData;
    @BindView(R.id.text_desc)
    TextView mLiveDesc;
    @BindView(R.id.tab_data) TabLayout mTabLayout;

    DatabaseReference mDatabase = FirebaseDatabase.getInstance().getReference();

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
        ButterKnife.bind(this, view);

        Bundle args = getArguments();
        isDoctor = args.getBoolean(Strings.SHAREDPREF_IS_DOCTOR, false);

//        if (isDoctor == true)
//            return view;
//        else
//            return view2;

        if (isDoctor) {
            mTabLayout.addTab(mTabLayout.newTab().setText("Heart Rate"));
            mTabLayout.addTab(mTabLayout.newTab().setText("Breathing Rate"));

            mTabLayout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
                @Override
                public void onTabSelected(TabLayout.Tab tab) {
                    Log.d(TAG, "tab selected: " + tab.getPosition());
                    isHeartRateTab = tab.getPosition() == 0;
                    if (isHeartRateTab) {
                        if (heartRate == null)
                            mLiveData.setText("Calibrating...");
                        else
                            mLiveData.setText(String.valueOf(heartRate));
                        mLiveDesc.setText(heartBPM);
                    } else {
                        if (breathingRate == null)
                            mLiveData.setText("Calibrating...");
                        else
                            mLiveData.setText(String.valueOf(breathingRate));
                        mLiveDesc.setText(breathBPM);
                    }
                }

                @Override
                public void onTabUnselected(TabLayout.Tab tab) {

                }

                @Override
                public void onTabReselected(TabLayout.Tab tab) {

                }
            });

            mDatabase.child("Rooms").child("room2").child("heartRate").addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    if (dataSnapshot == null || dataSnapshot.getValue() == null) {
                        return;
                    }

                    Log.d(TAG, dataSnapshot.toString());
                        Double d = Double.valueOf(dataSnapshot.getValue().toString());
                        heartRate = (int) Math.round(d);
                    if (isHeartRateTab) {
                        String live = String.valueOf(heartRate);
                        if (heartRate == null)
                            mLiveData.setText("Calibrating...");
                        else
                            mLiveData.setText(live);
                        mLiveDesc.setText(heartBPM);
                    }
                }

                @Override
                public void onCancelled(DatabaseError databaseError) {

                }
            });

            mDatabase.child("Rooms").child("room2").child("breathingRate").addValueEventListener(new ValueEventListener() {

                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    if (dataSnapshot == null || dataSnapshot.getValue() == null)
                        return;
                    Log.d(TAG, dataSnapshot.toString());
                        Double d = Double.valueOf(dataSnapshot.getValue().toString());
                        breathingRate = (int) Math.round(d);
                    if (!isHeartRateTab) {
                        String live = String.valueOf(breathingRate);
                        if (breathingRate == null)
                            mLiveData.setText("Calibrating...");
                        else
                            mLiveData.setText(live);
                        mLiveDesc.setText(breathBPM);
                    }
                }

                @Override
                public void onCancelled(DatabaseError databaseError) {

                }
            });
        } else {
            mLiveData. setText("");
            mLiveData.setTextSize(15);
            mLiveDesc.setText("Connected to Dr. Vegas");
            mLiveDesc.setTextSize(20);
        }

        return view;
    }

//    @Override
//    public void onViewCreated(View view, Bundle savedInstanceState) {
//        mViewPager = (ViewPager) view.findViewById(R.id.viewpager);
//        mViewPager.setAdapter(new FragmentPagerAdapter());
//        TabLayout tablayout = getActivity().findViewById(R.id.tab_chatdata);
//        tablayout.setupWithViewPager(mViewPager);
//    }

//    class FragmentPagerAdapter extends PagerAdapter {
//        private String[] tabTitles = new String[]{"Heart Rate", "Breathing Rate"};
//
//        @Override
//        public CharSequence getPageTitle(int positon){
//            return tabTitles[positon];
//        }
//
//        @Override
//        public int getCount() {
//            return 2;
//        }
//
//        @Override
//        public boolean isViewFromObject(View view, Object o) {
//            return o == view;
//        }
//
//        @Override
//        public Object instantiateItem(ViewGroup container, int position) {
//            View view = getActivity().getLayoutInflater().inflate(R.layout.contentindatafragment,
//                    container, false);
//            View view2 = getActivity().getLayoutInflater().inflate(R.layout.contentindatafragment2,
//                    container, false);
//
//            if(position == 0){
//                container.addView(view);
//                return view;}
//            else{
//                container.addView(view2);
//                return view2;}
//        }
//
//        @Override
//        public void destroyItem(ViewGroup container, int position, Object object) {
//            container.removeView((View) object);
//        }
//    }
}