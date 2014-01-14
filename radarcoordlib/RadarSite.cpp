#include <radarcoordlib/RadarSite.hpp>

RadarSite::RadarSite(float latr,float lonr,float heightr, float aTH) {
  setLatR(latr);
  setLonR(lonr);
  setHeightR(heightr);
  setAntennaTowerHeight(aTH);
}


void RadarSite::setRadarCoord(float latr,float lonr,float heightr, float aTH) {
  setLatR(latr);
  setLonR(lonr);
  setHeightR(heightr);
  setAntennaTowerHeight(aTH);
}

void RadarSite::setLatR( float value) {
  if ( ! generic::checkLatitude( value) ) 
    throw RadarCoordBadDataException("Radar Latitude passed ouside limits");
  lat_r=value;
}
void RadarSite::setLonR( float value) {
  if ( ! generic::checkLongitude( value) ) 
    throw RadarCoordBadDataException("Radar Longitude passed ouside limits");
  lon_r=value;
}
void RadarSite::setHeightR( float value) {height_r=value;}
void RadarSite::setAntennaTowerHeight( float value) { 
  if ( value < 0. || value > 100.) 
    throw RadarCoordBadDataException("Radar antenna tower height ouside limits");
  antennaTowerHeight=value;
}
float RadarSite::getLatR() {return lat_r;}
float RadarSite::getLonR() {return lon_r;}
float RadarSite::getHeightR() {return height_r;}
float RadarSite::getAntennaTowerHeight() { return antennaTowerHeight;}

