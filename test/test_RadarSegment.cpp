
#include <iostream>
#include <iomanip>
#include <cmath>
#include <radarcoordlib/RadarSegment_util.hpp>

using namespace std;

main () {
  float latr = 44.6547, lonr = 11.6236, hr=11., ath=25.; // SPC
//  float latr = 44.7914, lonr = 10.4992;               // GAT
//  float lat_start=44.870307 ;
//  float lon_start=11.097046 ;
  float lat_start=44.6547;
  float lon_start=11.6236;
  float lat_end=44.578547 ;
  float lon_end=11.027253 ;

  SegmentFillingMethod method;
  float step;
/*
 GAT START 44.870307 11.097046 79.281589 48082.965497 
 SPC START 44.870307 11.097046 -59.927193 48082.965498 
 GAT STOP 44.578547 11.027253 119.281575 48082.965495 
 SPC STOP 44.578547 11.027253 -99.927180 48082.965496 
*/

  RadarSegment_util asse (latr,lonr,hr,ath);   // initialize radar site with SPC coordinates

// set segment extreems 
  asse.setSegmentGeo(lat_start, lon_start, lat_end, lon_end);
  asse.setSegmentGeodesic(0., 100000., 90., 10000.);

  asse.printSegmentInfo();
  method = NUM_POINT;
  step =10;
 
  asse.setSegmentStep(method,step);
  RadarPoint_util Point;
  asse.CalculateSegment();
 
  asse.printSegmentInfo();
  for (int i=0; i <asse.getSegmentNumPoint(); i++){
	Point=asse.getSegmentPoint(i);
/*
	cout<<"Punto : "<<i<<" Coordinate ";
        cout<<  "Latitude      : "<<Point.getPointLat()<<" N";
        cout<<  "Longitude     : "<<Point.getPointLon()<<" E";
        cout<<  "X             : "<<Point.getPointXCoord();
        cout<<  "Y             : "<<Point.getPointYCoord();
        cout<<  "Distanza      : "<<Point.getSurfaceDistance();
        cout<<  "Azimuth       : "<<Point.getAzimuth()<<endl;
*/
      cout<<fixed;
      cout<<setprecision(6)<<Point.getPointLon()<<","<<Point.getPointLat()<<",0 ";
  }
cout<<endl;
  for (int myelev=0; myelev<11; myelev++){
    cout<<"=========================================="<<endl;
    asse.setSegmentElevation(myelev*5.);
    for (int i=0; i <asse.getSegmentNumPoint(); i++){
	Point=asse.getSegmentPoint(i);
	cout<<"Punto : "<<i<<" Coordinate ";
        cout<<"Distanza      : "<<Point.getSurfaceDistance();
        cout<<"      Azimuth       : "<<Point.getAzimuth();
	cout<<"      range     : "<<Point.getBeamDistance();
	cout<<"      height    : "<<Point.getHeight()<<endl;
    }
  }

// prendo il segmento intero con tutti i suoi punti
  vector <RadarPoint_util> segmento;
  segmento=asse.getSegment();
  cout<<"segmento ha : "<<segmento.size()<<" punti"<<endl;

//-------------------------------------------------------------------------------
// Ridefinisco il segmento come punti a distamnza regolare pari a 1000. metri
  cout<<"=========================================="<<endl;
  method = LINE_STEP;
  step =asse.getSegmentLength()/4.;
  asse.setSegmentStep(method,step);
// calcolo i spuntoi del segmento
  asse.CalculateSegment();
  asse.printSegmentInfo();
  cout<<"Number of point defined : " <<asse.getSegmentNumPoint()<<endl;
  for (int i=0; i <asse.getSegmentNumPoint(); i++){
	Point=asse.getSegmentPoint(i);
      cout<<fixed;
      cout<<setprecision(6)<<Point.getPointLon()<<","<<Point.getPointLat()<<",0 ";
  }
  cout<<endl;

  cout<<"=========================================="<<endl;

//-------------------------------------------------------------------------------
// Ridefinisco il segmento come punti a azimuth regolare pari a 1 grado
  cout<<"=========================================="<<endl;
  method = AZIMUTH_STEP;
  step =1.;
  asse.setSegmentStep(method,step);
// calcolo i spuntoi del segmento
  asse.CalculateSegment();
  asse.printSegmentInfo();
  cout<<"Number of point defined : " <<asse.getSegmentNumPoint()<<endl;
  for (int i=0; i <asse.getSegmentNumPoint(); i++){
	Point=asse.getSegmentPoint(i);
      cout<<fixed;
      cout<<setprecision(6)<<Point.getPointLon()<<","<<Point.getPointLat()<<",0 ";
  }
  cout<<endl;

  for (int myelev=0; myelev<11; myelev++){
    cout<<"=========================================="<<endl;
    asse.setSegmentElevation(myelev*5.);
    for (int i=0; i <asse.getSegmentNumPoint(); i++){
	Point=asse.getSegmentPoint(i);
	cout<<"Punto : "<<i<<" Coordinate ";
        cout<<"Distanza      : "<<Point.getSurfaceDistance();
        cout<<"      Azimuth       : "<<Point.getAzimuth();
	cout<<"      range     : "<<Point.getBeamDistance();
	cout<<"      height    : "<<Point.getHeight()<<endl;
    }
  }
}

