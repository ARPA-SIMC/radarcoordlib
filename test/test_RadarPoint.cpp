#include <iostream>
#include <iomanip>
#include <cmath>
#include <radarcoordlib/RadarPoint_util.hpp>

using namespace std;

int main () {
  float latp = 44.6547, lonp = 11.6236, hr=11., ath=25.; // SPC
  float latr = 44.7914, lonr = 10.4992;               // GAT
  float X,Y;
  float dist, az;
  float H,E;

  RadarPoint_util spc (latr,lonr,hr,ath);   // initialize radar site with SPC coordinates

  cout<<"=========================================="<<endl;
  cout<<"Printout radar site coordinate"<<endl;
  cout<<"Latitude      : "<<spc.getLatR()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getLonR()<<" E"<<endl;
  cout<<"Height        : "<<spc.getHeightR()<<" m"<<endl;
  cout<<"Antenna Tower : "<<spc.getAntennaTowerHeight()<<" m"<<endl;
  cout<<"=========================================="<<endl;

  spc.setPointGeoCoords(latp,lonp);
  cout<<"=========================================="<<endl;
  cout<<"Printout point coordinate"<<endl;
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;
  cout<<"(X,Y) sono definite ? "<<spc.isPointAeqdCoordsSet()<<endl; 
/*
  cout<<" X missing ? "<<spc.isMissing(spc.getPointXCoord())<<endl;
  cout<<" X defined ? "<<spc.isPointXCoordSet()<<endl;
  cout<<" Y missing ? "<<spc.isMissing(spc.getPointYCoord())<<endl;
  cout<<" Y defined ? "<<spc.isPointYCoordSet()<<endl;
  cout<<" True : "<<true<<endl;
 */
  cout<<"Calcolo le coordinate (Aeqd SPC)"<<endl;
  spc.GeoCoords2AeqdCoords();
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;
  cout<<"(X,Y) sono definite ?t "<<spc.isPointAeqdCoordsSet()<<endl; 
  cout<<"Calcolo distanza e azimuth punto rispetto sito radar"<<endl;
  spc.calculateGeodesicParam();
  cout<<"Distanza  : "<<spc.getSurfaceDistance()<<" m"<<endl;
  cout<<"Azimuth   : "<<spc.getAzimuth()<<" N"<<endl;
  cout<<"=================================================="<<endl;
  cout<<" ora setto X, Y  e ricalcolo tutto "<<endl;
  X=spc.getPointXCoord();
  Y=spc.getPointYCoord();

//  X = 14000.;
//  Y = - 77000.;
  spc.setPoint2Missing();
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;
  cout<<"inizializzo con punto (x,y)"<<endl;
  spc.setPointAeqdCoords(X,Y,false);  	// questa chiamata non calcola automaticamente le coordinate Aeqd 
					// ma devo chiamare il metodo a mano (vedi sotto)
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;
  cout<<"Calcolo le coordinate geografiche"<<endl;
  spc.AeqdCoords2GeoCoords();
  cout<<"Latitude      : "<<spc.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<spc.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<spc.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<spc.getPointYCoord()<<" m"<<endl;
  cout<<"Calcolo distanza e azimuth punto rispetto sito radar"<<endl;
  spc.calculateGeodesicParam();
  cout<<"Distanza  : "<<spc.getSurfaceDistance()<<" m"<<endl;
  cout<<"Azimuth   : "<<spc.getAzimuth()<<" N"<<endl;
  cout<<"=================================================="<<endl;
  cout<<" ricalcolo partendo dalle coordinate della geodetica "<<endl;
  X=spc.getAzimuth();  
  Y=spc.getSurfaceDistance();
  spc.setPointGeodesicCoordinate(X,Y);
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
  for (dist=25000.; dist<= 125000.;dist=dist+25000.){
    cout<<"=================================================="<<dist<<endl;
    for (H=250; H<=15000.; H=H+500.){
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
  }
 RadarPoint_util radar = spc;
  cout<<"Latitude      : "<<radar.getPointLat()<<" N"<<endl;
  cout<<"Longitude     : "<<radar.getPointLon()<<" E"<<endl;
  cout<<"X             : "<<radar.getPointXCoord()<<" m"<<endl;
  cout<<"Y             : "<<radar.getPointYCoord()<<" m"<<endl;
  cout<<"Distanza  : "<<spc.getSurfaceDistance()<<" m"<<endl;
  cout<<"Azimuth   : "<<spc.getAzimuth()<<" N"<<endl;

}

