#include <iostream>
#include <iomanip>
#include <cmath>
#include <RadarBeamCoord_util.hpp>

using namespace std;
main(){

cout<<" test elev_sd_2_beamHeight"<<endl;

float elev, sd;
RadarBeamCoord_util p;
	for (int i=0; i<10; i++){
	  cout<<"elevazione : "<<setprecision (1)<<(float)i*0.5<<"  --  ";
	  for(int j=10; j<=100; j=j+10){
	   cout.width(10);
	   cout.precision(1);
	   cout<<fixed<<right<<p.elev_sd_2_beamHeight(i*0.5,j*1000.);
	  }
	  cout<<endl;
	}
cout<<" test elev_br_2_beamHeight"<<endl;

	for (int i=0; i<10; i++){
	  cout<<"elevazione : "<<setprecision (1)<<(float)i*0.5<<"  --  ";
	  for(int j=10; j<=100; j=j+10){
	   cout.width(10);
	   cout.precision(1);
	   cout<<fixed<<right<<p.elev_br_2_beamHeight(i*0.5,j*1000.);
	  }
	  cout<<endl;
	}

cout<<" test elev_br_2_surfDistance"<<endl;

	for (int i=0; i<10; i++){
	  cout<<"elevazione : "<<setprecision (1)<<(float)i*0.5<<"  --  ";
	  for(int j=10; j<=100; j=j+10){
	   cout.width(10);
	   cout.precision(1);
	   cout<<fixed<<right<<p.elev_br_2_surfDistance(i*0.5,j*1000.);
	  }
	  cout<<endl;
	}

cout<<" test br_bh_2_elev"<<endl;

	for (int i=1; i<=10; i++){
	  cout<<"range : "<<setprecision (1)<<(float)i*10000.<<"  --  ";
	  for(int j=1; j<=10; j++){
	   cout.width(10);
	   cout.precision(2);
	   cout<<fixed<<right<<p.br_bh_2_elev(i*10000.,j*500.);
	  }
	  cout<<endl;
	}

cout<<" test ds_bh_2_elev"<<endl;

	for (int i=1; i<=10; i++){
	  cout<<"range : "<<setprecision (1)<<(float)i*10000.<<"  --  ";
	  for(int j=1; j<=10; j++){
	   cout.width(10);
	   cout.precision(2);
	   cout<<fixed<<right<<p.ds_bh_2_elev(i*10000.,j*500.);
	  }
	  cout<<endl;
	}

/*
    float elev_sd_2_beamHeight(float , float);
    float elev_br_2_beamHeight(float elev, float  beam_range);
    float elev_br_bh_2_surfDistance    (float elev, float beam_range, float beam_height);
    float elev_br_2_surfDistance    (float elev, float beam_range);
    float elev_sd_bh_2_beamRange(float elev, float surfDistance, float beam_height);
    float elev_sd_2_beamRange(float elev, float surfDistance);

    float br_bh_2_elev(float beamRange, float beamHeight);
    float ds_bh_2_elev(float surfDistance, float beamHeight);
*/


}
