#include <radarcoordlib/RadarGeoCoord_util.hpp>
RadarGeoCoord_util::RadarGeoCoord_util(){
  setPoint2Missing();
}

RadarGeoCoord_util::RadarGeoCoord_util(float latr,float lonr,float heightr,float aTH): radar_site(latr,lonr,heightr, aTH) {
  setPoint2Missing(); 
}

void RadarGeoCoord_util::setPoint2Missing(){
  float m;
  m= generic::getMissing();
  Xcoord_p  = m; 
  Ycoord_p  = m;
  Lat_p     = m;
  Lon_p     = m;
  Azimuth   = m;
  surfaceDistance = m; 
}
	void RadarGeoCoord_util::setLatR( float value) { radar_site.setLatR(value);}
	void RadarGeoCoord_util::setLonR( float value) { radar_site.setLonR(value);}
	void RadarGeoCoord_util::setHeightR( float value) {radar_site.setHeightR(value);}
	void RadarGeoCoord_util::setAntennaTowerHeight( float value) {radar_site.setAntennaTowerHeight(value);}
	float RadarGeoCoord_util::getLatR() {return radar_site.getLatR();}
	float RadarGeoCoord_util::getLonR() {return radar_site.getLonR();}
	float RadarGeoCoord_util::getHeightR() {return radar_site.getHeightR();}
	float RadarGeoCoord_util::getAntennaTowerHeight() {return radar_site.getAntennaTowerHeight();}

void RadarGeoCoord_util::setRadarCoord(float latr,float lonr,float heightr, float aTH, bool cleanPointCoord) { 
  radar_site.setRadarCoord(latr,lonr,heightr, aTH);
  if (cleanPointCoord) setPoint2Missing();
}
	
void RadarGeoCoord_util::setPointGnomoCoords(float X, float Y, bool cleanOtherCoords ) {
  if (cleanOtherCoords) setPoint2Missing();

  setPointXCoord(X);
  setPointYCoord(Y);
//  if (setGeo) GnomoCoords2GeoCoords();
}

bool RadarGeoCoord_util::GnomoCoords2GeoCoords () {
// if coordinates are unset return false
  if ( !this->isPointGnomoCoordsSet()) return false;
  typedef GeographicLib::Math::real real;
  real   LatRad,LonRad, LatPoint, LonPoint, XPoint,YPoint, AZ_gno,rk;
  real a = Constants::WGS84_a<real> ();
  real f = Constants::WGS84_f<real>();
  const Geodesic  geod(a,f);
  const Gnomonic  Gn(geod);

  LatRad = getLatR();
  LonRad = getLonR();
  XPoint = (real)getPointXCoord();
  YPoint = (real)getPointYCoord();
  Gn.Reverse(LatRad,LonRad,XPoint,YPoint,LatPoint,LonPoint,AZ_gno, rk);
  setPointLat((float)LatPoint);
  setPointLon((float)LonPoint);

  return true;
}

// Devo decidere se metto qui un test sui valori possibili e se mettere questi membri come private
void RadarGeoCoord_util::setPointLat(float value) {
  if ( ! generic::checkLatitude( value) ) throw RadarCoordBadDataException("Latitude passed ouside limits");
  Lat_p = value; 
}
void RadarGeoCoord_util::setPointLon(float value) {
  if ( ! generic::checkLongitude( value) ) throw RadarCoordBadDataException("Longitude passed ouside limits");
  Lon_p = value; 
}

void RadarGeoCoord_util::setPointGeoCoords(float lat, float lon, bool cleanOtherCoords) {
  if (cleanOtherCoords) setPoint2Missing();
  setPointLat(lat);
  setPointLon(lon);
//  if (setGnomo) GeoCoords2GnomoCoords();
}

bool RadarGeoCoord_util::isPointLongitudeSet() {
  if (generic::isMissing(getPointLon())) return false;
  if ( ! generic::checkLongitude( getPointLon()) ) return false;
  return true;
}

bool RadarGeoCoord_util::isPointLatitudeSet() {
  if (generic::isMissing(getPointLat())) return false;
  if ( ! generic::checkLatitude( getPointLat()) ) return false;
  return true;
}

bool RadarGeoCoord_util::GeoCoords2GnomoCoords () {
// if coordinates are unset return false
  if ( !this->isPointGeoCoordsSet()) return false;
  typedef GeographicLib::Math::real real;
  real   LatRad,LonRad, LatPoint, LonPoint, XPoint,YPoint, AZ_gno,rk;
  real a = Constants::WGS84_a<real> ();
  real f = Constants::WGS84_f<real>();
  const Geodesic  geod(a,f);
  const Gnomonic  Gn(geod);

  LatRad = getLatR();
  LonRad = getLonR();
  LatPoint = (real)getPointLat();
  LonPoint = (real)getPointLon();
  Gn.Forward(LatRad,LonRad, LatPoint,LonPoint,XPoint,YPoint,AZ_gno, rk);
  setPointXCoord((float)XPoint);
  setPointYCoord((float)YPoint);

 return true;
}

// Devo decidere se metto qui un test sui valori possibili 
//	bool isElevationSet() {};

bool RadarGeoCoord_util::calculateGeodesicParam() {
  if (!this->isPointGeoCoordsSet()){	
    if (!this->isPointGnomoCoordsSet()) return false;
    this->GnomoCoords2GeoCoords (); 
  }
  typedef GeographicLib::Math::real real;
  const GeographicLib::Geodesic  g1= GeographicLib::Geodesic::WGS84();
  real   LatRad,LonRad, LatPoint, LonPoint, XPoint,Ypoint, Az1,Az2,S12,dummy;

  LatRad = getLatR();
  LonRad = getLonR();
  LatPoint = (real)getPointLat();
  LonPoint = (real)getPointLon();
  dummy = g1.Inverse(LatRad, LonRad,LatPoint,LonPoint, S12,Az1,Az2);
  if (Math::isnan(Az1)) return false;
  setSurfaceDistance ((float) S12);
  setAzimuth((float)Az1);
  return true;
}

bool RadarGeoCoord_util::invertGeodesicCalculation() {
  if (!this->isGeodesicCoordsSet()){
   return false;
  }

  typedef GeographicLib::Math::real real;
  const GeographicLib::Geodesic   g1= GeographicLib::Geodesic::WGS84();
  real   LatRad,LonRad, LatPoint, LonPoint, XPoint,Ypoint, Az1,S12,dummy;
  LatRad = getLatR();
  LonRad = getLonR();
  S12= getSurfaceDistance ();
  Az1=getAzimuth();
  const GeographicLib::GeodesicLine GL(g1, LatRad, LonRad, Az1);
  GL.Position(S12,LatPoint,LonPoint);
  setPointLat(LatPoint);
  setPointLon(LonPoint);
  GeoCoords2GnomoCoords();
  return true;
}

bool RadarGeoCoord_util::isPointXCoordSet() { return !generic::isMissing(Xcoord_p); }
bool RadarGeoCoord_util::isPointYCoordSet() { return !generic::isMissing(Ycoord_p); }
bool RadarGeoCoord_util::isPointGnomoCoordsSet() { return isPointXCoordSet() && isPointYCoordSet(); }
float RadarGeoCoord_util::getPointXCoord() {return Xcoord_p;}
float RadarGeoCoord_util::getPointYCoord() { return Ycoord_p;}
bool RadarGeoCoord_util::isPointGeoCoordsSet() { return isPointLongitudeSet() && isPointLatitudeSet(); }
float RadarGeoCoord_util::getPointLat() {return Lat_p;}
float RadarGeoCoord_util::getPointLon() {return Lon_p;}
void RadarGeoCoord_util::setPointGeodesicCoordinate (float Azimuth, float SurfaceDist, bool cleanOtherCoords) {
  if (cleanOtherCoords) setPoint2Missing();
  setAzimuth(Azimuth);
  setSurfaceDistance(SurfaceDist);
}
bool RadarGeoCoord_util::isAzimuthSet() { return !generic::isMissing(Azimuth); }
bool RadarGeoCoord_util::isSurfaceDistanceSet() { return !generic::isMissing(surfaceDistance); }
bool RadarGeoCoord_util::isGeodesicCoordsSet() { return isAzimuthSet() && isSurfaceDistanceSet(); }
float RadarGeoCoord_util::getSurfaceDistance() {return surfaceDistance;}
float RadarGeoCoord_util::getAzimuth() {return fmod(Azimuth+360.,360.);}
void RadarGeoCoord_util::setPointXCoord(float value) {Xcoord_p=value;}
void RadarGeoCoord_util::setPointYCoord(float value) {Ycoord_p=value;}
void RadarGeoCoord_util::setSurfaceDistance(float value) {surfaceDistance = value;}
void RadarGeoCoord_util::setAzimuth(float value) {Azimuth = value;}

bool RadarGeoCoord_util::fillCoords () {
  if (calculateGeodesicParam()) {
    if (!this->isPointGnomoCoordsSet()) GeoCoords2GnomoCoords();
  } else if (this->invertGeodesicCalculation()){
    if (!this->isPointGnomoCoordsSet()) GeoCoords2GnomoCoords();
  }
  else return false;
  return true;  
}


