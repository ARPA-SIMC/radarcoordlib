#include <iostream>
#include <iomanip>
#include <cmath>
#include <radarcoordlib/RadarGeoCoord_util.hpp>

using namespace std;

main () {
  float latp = 44.6547, lonp = 11.6236, hr=11., ath=25.; // SPC
  float latr = 44.7914, lonr = 10.4992;               // GAT
  float X,Y;
  float dist, az;

  RadarGeoCoord_util spc (latr,lonr,hr,ath);   // initialize radar site with SPC coordinates

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

  X = 14000.;
  Y = - 77000.;
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

}
