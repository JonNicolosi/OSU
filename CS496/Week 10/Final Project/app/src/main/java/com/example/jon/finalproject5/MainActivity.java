package com.example.jon.finalproject5;

import android.app.Dialog;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.login.LoginResult;
import com.facebook.login.widget.LoginButton;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity implements
        GoogleApiClient.ConnectionCallbacks, GoogleApiClient.OnConnectionFailedListener{


    LoginButton loginButton;
    CallbackManager callbackManager;
    AccessToken accessToken;
    TextView textView;


    private GoogleApiClient mGoogleApiClient;
    private LocationRequest mLocationRequest;
    private Location mLastLocation;
    private LocationListener mLocationListener;
    private static final int LOCATION_PERMISSON_RESULT = 17;
    private TextView mLatText;
    private TextView mLonText;
    String commentID;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        loginButton = (LoginButton)findViewById(R.id.login_button);
        loginButton.setReadPermissions(Arrays.asList("user_education_history", "user_relationships"));
        textView = (TextView) findViewById(R.id.textView);
        callbackManager = CallbackManager.Factory.create();
        loginButton.registerCallback(callbackManager, new FacebookCallback<LoginResult>() {
            @Override
            public void onSuccess(LoginResult loginResult) {
                accessToken = loginResult.getAccessToken();
                GraphRequest request = GraphRequest.newMeRequest(
                        accessToken,
                        new GraphRequest.GraphJSONObjectCallback() {
                            @Override
                            public void onCompleted(JSONObject object, GraphResponse response) {
                                // Insert your code here



                                try {
                                    textView.setText("Name: " + object.getString("name"));

                                } catch (JSONException e) {
                                    e.printStackTrace();
                                }
                            }
                        });

                Bundle parameters = new Bundle();
                parameters.putString("fields", "relationship_status,education,name");
                request.setParameters(parameters);
                request.executeAsync();


            }

            @Override
            public void onCancel() {

            }

            @Override
            public void onError(FacebookException e) {

            }
        });

        //BUTTON LISTENERS

        Button post = (Button)findViewById(R.id.post);

        post.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                postGPStoStatus();
            }
        });

        Button edit = (Button)findViewById(R.id.edit);

        edit.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                editComment();
            }
        });


        if (mGoogleApiClient == null) {
            mGoogleApiClient = new GoogleApiClient.Builder(this)
                    .addConnectionCallbacks(this)
                    .addOnConnectionFailedListener(this)
                    .addApi(LocationServices.API)
                    .build();
        }
        mLatText = (TextView) findViewById(R.id.lat_output);
        mLonText = (TextView) findViewById(R.id.lon_output);

        mLocationRequest = LocationRequest.create();
        mLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        mLocationRequest.setInterval(5000);
        mLocationRequest.setFastestInterval(5000);
        mLocationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                if (location != null) {
                    mLonText.setText(String.valueOf(location.getLongitude()));
                    mLatText.setText(String.valueOf(location.getLatitude()));
                } else {
                    mLonText.setText("No Location Available");
                    mLatText.setText("No Location Available");
                }
            }
        };

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        callbackManager.onActivityResult(requestCode,resultCode,data);
    }





    public void postGPStoStatus(){

        TextView lattextView = (TextView)findViewById(R.id.lat_output);
        TextView lonttextView = (TextView)findViewById(R.id.lon_output);
        String sendLatAndLon = "Latitude: " + lattextView.getText().toString() + ", Longitude: " + lonttextView.getText().toString();

        GraphRequest request = null;
        try {
            request = GraphRequest.newPostRequest(
                    accessToken,
                    "/me/feed",
                    new JSONObject().put("message", sendLatAndLon),
                    new GraphRequest.Callback() {
                        @Override
                        public void onCompleted(GraphResponse response) {
                            // Insert your code here

                        }
                    });
        } catch (JSONException e) {
            e.printStackTrace();
        }
        request.executeAsync();

    }

    public void editComment(){

        GraphRequest request = GraphRequest.newGraphPathRequest(
                accessToken,
                "/me/feed",
                new GraphRequest.Callback() {
                    @Override
                    public void onCompleted(GraphResponse response) {
                        // Insert your code here
                        try {
                            JSONObject obj = new JSONObject(response.getRawResponse());
                            JSONArray jsonarray = new JSONArray(obj.getString("data"));
                            commentID = jsonarray.getJSONObject(0).getString("id");
                            postChangeComment();
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }




                    }
                });

        Bundle parameters = new Bundle();
        parameters.putString("name", "null");
        request.setParameters(parameters);
        request.executeAsync();

    }



    public void postChangeComment(){

        GraphRequest request = null;
        try{
            request = GraphRequest.newPostRequest(
                accessToken,
                commentID,
                new JSONObject("{\"message\":\"Whoopsie\"}"),
                new GraphRequest.Callback() {
                    @Override
                    public void onCompleted(GraphResponse response) {
                        // Insert your code here
                    }
                });
    } catch (JSONException e) {
        e.printStackTrace();
    }
        request.executeAsync();

    }



    @Override
    protected void onStart() {
        mGoogleApiClient.connect();

        super.onStart();
    }

    @Override
    protected void onStop() {
        mGoogleApiClient.disconnect();
        super.onStop();
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {

        if (ActivityCompat.checkSelfPermission(this,
                android.Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED &&
                ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{android.Manifest.permission.ACCESS_FINE_LOCATION, android.Manifest.permission.ACCESS_COARSE_LOCATION}, LOCATION_PERMISSON_RESULT);
            return;
        }
        updateLocation();
    }

    @Override
    public void onConnectionSuspended(int i) {

    }

    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {
        Dialog errDialog = GoogleApiAvailability.getInstance().getErrorDialog(this, connectionResult.getErrorCode(), 0);
        errDialog.show();
        return;
    }

    private void updateLocation() {
        if (ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            return;
        }
        mLastLocation = LocationServices.FusedLocationApi.getLastLocation(mGoogleApiClient);

        if(mLastLocation != null){
            mLonText.setText(String.valueOf(mLastLocation.getLongitude()));
            mLatText.setText(String.valueOf(mLastLocation.getLatitude()));
        } else {
            LocationServices.FusedLocationApi.requestLocationUpdates(mGoogleApiClient,mLocationRequest,mLocationListener);
        }
    }

}
