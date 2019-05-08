#include <iostream>
#include <iomanip>
#include <cmath>
#include <radarcoordlib/RadarPoint_util.hpp>

using namespace std;

int main () {
  float latp = 44.6547, lonp = 11.6236, hr=11., ath=25.; // SPC
  float latr = 44.7914, lonr = 10.4992;               // GAT
  float AzP = 180, SurfDistP = 10;      // Point close to the radar site (@ SurfDistP meter)
  float X,Y;
  float dist, az;
  float H,E;

  RadarPoint_util spc (latp,lonp,hr,ath);   // initialize radar site with SPC coordinates

  cout<<"=========================================="<<endl;
  cout<<"Printout radar site coordinate"<<endl;
  cout<<"Latitude      : "<<spc.getLatR()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getLonR()<<" E"<<endl;
  cout<<"Height        : "<<spc.getHeightR()<<" m"<<endl;
  cout<<"Antenna Tower : "<<spc.getAntennaTowerHeight()<<" m"<<endl;
  cout<<"=========================================="<<endl;

  spc.setPointGeodesicCoordinate(AzP,SurfDistP);
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;
  cout<<"Distanza  : "<<spc.getSurfaceDistance()<<" m"<<endl;
  cout<<"Azimuth   : "<<spc.getAzimuth()<<" N"<<endl;
  spc.invertGeodesicCalculation();
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;


  az= spc.getAzimuth();
  dist=spc.getSurfaceDistance();
    cout<<"=================================================="<<dist<<endl;
    for (H=1; H<=1000.; H++){
      spc.setPointRadarCoordinateHeight(az,H,dist);
/*
      spc.setHeight(H);
      spc.setElevation(generic::getMissing());
 */
      spc.fillCoords();
      cout<<setfill(' ')<<setw(15)<<setprecision(3)<<fixed<<spc.getSurfaceDistance();
      cout<<setfill(' ')<<setw(15)<<setprecision(3)<<fixed<<spc.getBeamDistance();
      cout<<setfill(' ')<<setw(15)<<setprecision(3)<<fixed<<spc.getHeight();
      cout<<setfill(' ')<<setw(15)<<setprecision(3)<<fixed<<spc.getElevation();
      cout<<setfill(' ')<<setw(15)<<setprecision(3)<<fixed<<spc.getPointXCoord();
      cout<<setfill(' ')<<setw(15)<<setprecision(3)<<fixed<<spc.getPointYCoord()<<endl;
    }
  
 RadarPoint_util radar = spc;
  cout<<"Latitude      : "<<radar.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<radar.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<radar.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<radar.getPointYCoord()<<" m"<<endl;
  cout<<"Distanza  : "<<spc.getSurfaceDistance()<<" m"<<endl;
  cout<<"Azimuth   : "<<spc.getAzimuth()<<" N"<<endl;

}

