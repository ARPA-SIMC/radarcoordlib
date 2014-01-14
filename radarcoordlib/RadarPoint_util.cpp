#include <radarcoordlib/RadarPoint_util.hpp>

/*
 RadarPoint_util::RadarPoint_util(float latr,float lonr,float heightr, float aTH): radar_site(latr,lonr,heightr, aTH) {
  setPoint2Missing(); 
}
RadarPoint_util::RadarPoint_util(float latr,float lonr,float heightr, float aTH, float azimuth, float elevation, float range): radar_site(latr,lonr,heightr, aTH) {

  setPoint2Missing(); 
}
*/

RadarPoint_util::RadarPoint_util() {
  RadarPoint_util(0.,0.,0.,0.); 
}

RadarPoint_util::RadarPoint_util(float latr,float lonr,float heightr, float aTH) {
  setRadarCoord(latr,lonr,heightr, aTH);
  setPoint2Missing(); 
}

RadarPoint_util::RadarPoint_util(float latr,float lonr,float heightr, float aTH, float azimuth, float elevation, float range) {
  setRadarCoord(latr,lonr,heightr, aTH);
  setPoint2Missing(); 
}

/*
 RadarPoint_util::RadarPoint_util (const RadarPoint_util &param){
  //this->setRadarCoord(param.getLatR(), param.getLonR(), param.getHeightR(), param.getAntennaTowerHeight ());
  std::cout<<param.getLatR()<<std::endl;//, param.getLonR(), param.getHeightR(), param.getAntennaTowerHeight ());
 
  setPointGnomoCoordsElev(param.getPointXCoord(), param.getPointYCoord(),param.getElevation(),false);
  setPointGeoCoordsHeight(param.getPointLat(), param.getPointLon(),param.getHeight(),false);
  setPointGeodesicCoordinateHeight(param.getAzimuth(), param.getSurfaceDistance(),param.getHeight(),false);
  setPointRadarCoordinateHeight(param.getAzimuth(), param.getHeight(), param.getBeamDistance(), false);
}
*/

void RadarPoint_util::setPoint2Missing(){
  float m;
  m= generic::getMissing();
  Xcoord_p        = m; 
  Ycoord_p        = m;
  Lat_p           = m;
  Lon_p           = m;
  Azimuth         = m;
  surfaceDistance = m; 
  Elevation       = m;
  Height          = m;
  BeamDistance    = m; 
}

float RadarPoint_util::setElevation(float value) {
  Elevation=value;
}

bool RadarPoint_util::isElevationSet() {
 	  if (generic::isMissing(getElevation())) return false;
          if ( ! generic::checkElevation ( getElevation()) ) return false;
	  return true;
        }

float RadarPoint_util::getElevation() {return Elevation;}
	
float RadarPoint_util::setHeight (float value) {Height = value; } //radarHeight2radarElev () ;}
bool RadarPoint_util::isHeightSet() {
 	  if (generic::isMissing(getHeight())) return false;
	  return true;
        }
float RadarPoint_util::getHeight() {return  Height;}

float RadarPoint_util::setBeamDistance(float value) {BeamDistance = value;}

bool RadarPoint_util::isBeamDistanceSet() {
  if (generic::isMissing(getBeamDistance())) return false;
  if ( ! generic::checkBeamDistance ( getBeamDistance()) ) return false;
  return true;
}

float RadarPoint_util::getBeamDistance () {return BeamDistance;}

bool RadarPoint_util::isRadarCoordsSet() {
	return isAzimuthSet() && isBeamDistanceSet() && (isElevationSet() || isHeightSet());
}

void RadarPoint_util::setPointGnomoCoordsHeight(float X, float Y, float H, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointGnomoCoords(X, Y, cleanOtherCoords);
  setElevation(generic::getMissing());
  setHeight(H);
}

void RadarPoint_util::setPointGnomoCoordsElev(float X, float Y, float Elev, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointGnomoCoords(X, Y, cleanOtherCoords);
  setElevation(Elev);
}

void RadarPoint_util::setPointGeoCoordsHeight(float lat, float lon, float H, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointGeoCoords(lat, lon, cleanOtherCoords);
  setHeight(H);
}

void RadarPoint_util::setPointGeoCoordsElev(float lat, float lon, float Elev, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointGeoCoords(lat,lon, cleanOtherCoords);
  setElevation(Elev);
}
void RadarPoint_util::setPointGeodesicCoordinateHeight (float Azimuth, float SurfaceDist, float H, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointGeodesicCoordinate(Azimuth,SurfaceDist, cleanOtherCoords);
  setHeight(H);
}

void RadarPoint_util::setPointGeodesicCoordinateElev (float Azimuth, float SurfaceDist, float Elev, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointGeodesicCoordinate(Azimuth,SurfaceDist, cleanOtherCoords);
  setElevation(Elev);
}
void RadarPoint_util::setPointRadarCoordinateElev (float Azimuth, float Elev, float BeamDist, bool cleanOtherCoords){
  if (cleanOtherCoords) setPoint2Missing();
  setAzimuth(Azimuth);
  setBeamDistance(BeamDist);
  setElevation(Elev);
}

void RadarPoint_util::setPointRadarCoordinateHeight (float Azimuth, float H, float BeamDist, bool cleanOtherCoords){
  if (cleanOtherCoords) setPoint2Missing();
  setAzimuth(Azimuth);
  setBeamDistance(BeamDist);
  setHeight(H);
}

bool RadarPoint_util::radarHeight2radarElev(){
  RadarBeamCoord_util Beam;
  float H;
  float E;
  float R;
  float alt_rad;
  bool out;
  E= generic::getMissing();
  out = false;  
  if(isHeightSet()){ 
  H=getHeight();
    alt_rad=getHeightR()+getAntennaTowerHeight();
    if (isBeamDistanceSet()) {
      R=getBeamDistance();
      E= (R > 0.) ? Beam.br_bh_2_elev(R,H,alt_rad): 90.;
      out = true;
    } else if (isSurfaceDistanceSet()){
      R=getSurfaceDistance();
       E= (R > 0.) ? Beam.ds_bh_2_elev(R,H,alt_rad): 90.;
      out = true;
   }
  } 
  setElevation(E);
  return out;
}

bool RadarPoint_util::radarElev2radarHeight(){
  RadarBeamCoord_util Beam;
  float H;
  float E;
  float R;
  float alt_rad;
  bool out;
  H= generic::getMissing();
  out = false;  
  if(isElevationSet()){ 
    E=getElevation();
    alt_rad=getHeightR()+getAntennaTowerHeight();
    if (isBeamDistanceSet()) {
      R=getBeamDistance();
      H=Beam.elev_br_2_beamHeight(E,R,alt_rad);
      out = true;
    } else if (isSurfaceDistanceSet()){
      R=getSurfaceDistance(); 
      H=Beam.elev_sd_2_beamHeight(E,R,alt_rad);
      out = true;
    }
  } 
  setHeight(H);
  return out;
}

bool RadarPoint_util::RadarCoords2GnomoCoords(){
// alias for RadarCoords2OtherCoords
 return RadarCoords2OthersCoords();
}

bool RadarPoint_util::RadarCoords2GeoCoords(){
// alias for RadarCoords2OtherCoords
 return RadarCoords2OthersCoords();
}

bool RadarPoint_util::syncRadarVerticalCoord(){
  if ( !(isBeamDistanceSet() || isSurfaceDistanceSet())) return false;
// check which vertical coordinate is set and calculate the other 
  if (isElevationSet()) {
    radarElev2radarHeight();
  } else {
    radarHeight2radarElev();
  }
  return true;
}

bool RadarPoint_util::RadarCoords2GeodeticCoords(){
  if ( !this->isRadarCoordsSet()) return false;
// check which vertical coordinate is set and calculate the other 
  if ( !this->syncRadarVerticalCoord()) return false;
  RadarBeamCoord_util Beam;
  float SurfDist;
// compute surface distance on the earth based on radar coords
  SurfDist=Beam.elev_br_2_surfDistance(getElevation(),getBeamDistance());
// set surface distance
  setSurfaceDistance(SurfDist);
  return true;
}

bool RadarPoint_util::RadarCoords2OthersCoords(){
// compute geodetic coordinate
  if ( !this->RadarCoords2GeodeticCoords()) return false;
// compute Geographic and Geognomic coords
  if (!invertGeodesicCalculation()) return false;
  return true;
}

bool RadarPoint_util::GeodeticCoords2RadarCoords(){
  if ( !this->isGeodesicCoordsSet()) return false;
  if (! syncRadarVerticalCoord()) return false;
  RadarBeamCoord_util Beam;
  float E;
  float sd;
  float br;
  E=getElevation();
  sd=getSurfaceDistance(); 
  br=Beam.elev_sd_2_beamRange(E,sd);
  setBeamDistance(br);
  return true;
}

bool RadarPoint_util::GnomoCoords2RadarCoords(){
  if ( !this->isPointGnomoCoordsSet()) return false;
  if (calculateGeodesicParam()) return GeodeticCoords2RadarCoords();
  return false;
}

bool RadarPoint_util:: GeoCoords2RadarCoords(){
  if ( !this->isPointGeoCoordsSet()) return false;
  if (calculateGeodesicParam()) return GeodeticCoords2RadarCoords();
  return false;
}

bool RadarPoint_util::fillCoords () {
  if (isRadarCoordsSet()) return RadarCoords2OthersCoords();
  if (! RadarGeoCoord_util::fillCoords()) return false;
  return GeodeticCoords2RadarCoords();
}
RadarPoint_util& RadarPoint_util::operator= (RadarPoint_util param){
  this->setRadarCoord(param.getLatR(), param.getLonR(), 
        param.getHeightR(), param.getAntennaTowerHeight ());
  this->setPointGnomoCoordsElev(param.getPointXCoord(), 
	param.getPointYCoord(),param.getElevation(),false);
  this->setPointGeoCoordsHeight(param.getPointLat(), 
	param.getPointLon(),param.getHeight(),false);
  this->setPointGeodesicCoordinateHeight(param.getAzimuth(), 
	param.getSurfaceDistance(),param.getHeight(),false);
  this->setPointRadarCoordinateHeight(param.getAzimuth(), 
	param.getHeight(), param.getBeamDistance(), false);
  return (*this);
}

