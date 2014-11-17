#include <radarcoordlib/RadarSegment_util.hpp>

RadarSegment_util::RadarSegment_util() {
  clearSegment();
}

RadarSegment_util::RadarSegment_util(float latr,float lonr,float heightr, float aTH) : beginSegment(latr,lonr,heightr,aTH), endSegment(latr,lonr,heightr,aTH) {
  clearSegment();
}

void RadarSegment_util::setRadarCoord(float latr,float lonr,float heightr, float aTH){
  clearSegment();
  beginSegment.setRadarCoord(latr,lonr,heightr,aTH);
  endSegment.setRadarCoord(latr,lonr,heightr,aTH);
}

bool RadarSegment_util::setSegmentGeo(float lat_begin, float lon_begin, float lat_end, float lon_end){
     clearSegment();
     beginSegment.setPointGeoCoordsHeight(lat_begin, lon_begin,0.);
     endSegment.setPointGeoCoordsHeight(lat_end, lon_end,0.);
// check if coordinates calculation is correct for both extreems
     if (! endSegment.fillCoords() || ! beginSegment.fillCoords() ) {
	clearSegment();
	return false;
     }

     SetGeodesicLine();
     setSegmentVersus();
 // check if extreems are not coincident
     if (! isSegmentLengthValid()) {
	clearSegment();
	return false;
     }
     if (isRHI()){
	if (beginSegment.getSurfaceDistance() < 0.1) {
	    beginSegment.setPointGeodesicCoordinate(endSegment.getAzimuth(),0, false);
	    beginSegment.setPointGnomoCoords(0., 0., false);
        }	
	else {
           endSegment.setPointGeodesicCoordinate(beginSegment.getAzimuth(),0, false);
	   endSegment.setPointGnomoCoords(0., 0., false);
        }	
     }
     return true;
}

bool RadarSegment_util::setSegmentGnomo(float x_begin, float y_begin, float x_end, float y_end){
     clearSegment();
     beginSegment.setPointGnomoCoordsHeight(x_begin, y_begin,0.);
     endSegment.setPointGnomoCoordsHeight(x_end, y_end,0.);
// check if coordinates calculation is correct for both extreems
     if (! endSegment.fillCoords() || ! beginSegment.fillCoords() ) {
	clearSegment();
	return false;
     }

     SetGeodesicLine();
     setSegmentVersus();
 // check if extreems are not coincident
     if (! isSegmentLengthValid()) {
	clearSegment();
	return false;
     }
     if (isRHI()){
	if (beginSegment.getSurfaceDistance() < 0.1) {
	    beginSegment.setPointGeodesicCoordinate(endSegment.getAzimuth(),0, false);
	    beginSegment.setPointGnomoCoords(0., 0., false);
        }	
	else {
           endSegment.setPointGeodesicCoordinate(beginSegment.getAzimuth(),0, false);
	   endSegment.setPointGnomoCoords(0., 0., false);
        }	
     }
     return true;
}

bool RadarSegment_util::setSegmentGeodesic(float az_begin, float surfDist_begin, float az_end, float surfDist_end){
     clearSegment();
     beginSegment.setPointGeodesicCoordinateHeight(az_begin, surfDist_begin,0.);
     beginSegment.fillCoords();
     endSegment.setPointGeodesicCoordinateHeight(az_end, surfDist_end,0.);
     endSegment.fillCoords();
// check if coordinates calculation is correct for both extreems
     if (! endSegment.fillCoords() || ! beginSegment.fillCoords() ) {
	clearSegment();
	return false;
     }

     SetGeodesicLine();
     setSegmentVersus();
 // check if extreems are not coincident
     if (! isSegmentLengthValid()) {
	clearSegment();
	return false;
     }
     if (isRHI()){
	if (beginSegment.getSurfaceDistance() < 0.1 ) {
	    beginSegment.setPointGeodesicCoordinate(endSegment.getAzimuth(),0, false);
	    beginSegment.setPointGnomoCoords(0., 0., false);
        }	
	else {
           endSegment.setPointGeodesicCoordinate(beginSegment.getAzimuth(),0, false);
	   endSegment.setPointGnomoCoords(0., 0., false);
        }	
     }
     return true;
}

void RadarSegment_util::clearSegment(){
	clearSegmentPoints();
	beginSegment.setPoint2Missing();
	endSegment.setPoint2Missing();
        segmentVersus = NOT_DEF_ROT_VERSUS;
	setSegmentLength(generic::getMissing());
}

void RadarSegment_util::clearSegmentPoints(){
	SegmentPoint.clear();
	setSegmentNumPoint(0);
	setSegmentLineStep(generic::getMissing());
	setSegmentAzimuthStep(generic::getMissing());
	stepType=NOT_DEF_STEP_TYPE;
}

void RadarSegment_util::setSegmentStep(SegmentFillingMethod type, float value){
        clearSegmentPoints();
	setSegmentType(type);	
	switch (type){
	  case NUM_POINT         : setSegmentNumPoint((int)value);
	                     break;
	  case LINE_STEP         : setSegmentLineStep(value);
	                     break;
	  case AZIMUTH_STEP      : setSegmentAzimuthStep(value);
	                     break;
	  case NOT_DEF_STEP_TYPE : clearSegmentPoints();
			     break;
        }
}

void RadarSegment_util::CalculateSegment(){
	switch (getSegmentType()){
	  case NUM_POINT         : CalculateSegmentNumPoint();
	                     break;
	  case LINE_STEP         : CalculateSegmentLineStep();
	                     break;
	  case AZIMUTH_STEP      : CalculateSegmentAzimuthStep();
	                     break;
	  case NOT_DEF_STEP_TYPE : ;  // SegmentPoint.clear();
			     break;
        }
}
vector <RadarPoint_util> RadarSegment_util::getSegment(){
	vector <RadarPoint_util> temp = SegmentPoint;
	return temp;
}

RadarPoint_util RadarSegment_util::getSegmentPoint(int index){
	RadarPoint_util temp;
	if ( SegmentPoint.size() > index) temp = SegmentPoint[index];
	return temp;
}

void RadarSegment_util::addSegmentPoint(RadarPoint_util point){
	SegmentPoint.push_back(point);
}

bool RadarSegment_util::addSegmentPoint(int index, RadarPoint_util point){
	if ( SegmentPoint.size() <= index) return false;
	vector <RadarPoint_util>::iterator it;
	it=SegmentPoint.begin() +index; 
	SegmentPoint.insert(it,point);
	return true;
}

void RadarSegment_util::setSegmentNumPoint(int value){
	numPoint=value;
}
void RadarSegment_util::setSegmentLineStep(float value){
	segmentStep=value;
}
void RadarSegment_util::setSegmentAzimuthStep(float value){
	AzimuthStep=fabs(value);
}
int RadarSegment_util::getSegmentNumPoint(){
	return numPoint;
}
float RadarSegment_util::getSegmentLineStep(){
	return segmentStep;
}
float RadarSegment_util::getSegmentAzimuthStep(){
	return AzimuthStep; 
}
void RadarSegment_util::CalculateSegmentNumPoint(){
   float lengthStep;
   int numpoint;
   float latr,lonr,heightr, altTower;

   latr=beginSegment.getLatR();
   lonr=beginSegment.getLonR();
   heightr=beginSegment.getHeightR();
   altTower=beginSegment.getAntennaTowerHeight();
// calculate step along the segment
   lengthStep=getSegmentLength()/(getSegmentNumPoint()-1);
   numpoint=getSegmentNumPoint();
//cleaning procedure
   clearSegmentPoints();
   setSegmentType(NUM_POINT);
   setSegmentNumPoint(numpoint);
   setSegmentLineStep(lengthStep);

//starting of segment definition procedure
//add first point
   addSegmentPoint(beginSegment);
   for (int i=1 ; i <numpoint-1; i++){
// add segment points between first and latter
     RadarPoint_util tmpPoint(latr,lonr,heightr,altTower);
     GeographicLib::Math::real distance, latp,lonp;
     distance= (GeographicLib::Math::real)(i*lengthStep);
     SegmentLine.Position(distance, latp, lonp);
     tmpPoint.setPointGeoCoordsHeight(latp,lonp,0.);
     tmpPoint.fillCoords();
/*   
       std::cout<<  "Latitude      : "<<tmpPoint.getPointLat()<<" N";
        std::cout<<  "Longitude     : "<<tmpPoint.getPointLon()<<" E";
        std::cout<<  "X             : "<<tmpPoint.getPointXCoord();
        std::cout<<  "Y             : "<<tmpPoint.getPointYCoord();
        std::cout<<  "Distanza      : "<<tmpPoint.getSurfaceDistance();
        std::cout<<  "Azimuth       : "<<tmpPoint.getAzimuth()<<std::endl;
*/
    addSegmentPoint(tmpPoint);
   }
//add latter point
   addSegmentPoint(endSegment);
// ending of segment definition procedure
}

void RadarSegment_util::CalculateSegmentLineStep(){
   float lengthStep;
   int lengthSegment, distance;
   float latr,lonr,heightr, altTower;

   latr=beginSegment.getLatR();
   lonr=beginSegment.getLonR();
   heightr=beginSegment.getHeightR();
   altTower=beginSegment.getAntennaTowerHeight();

   lengthSegment=getSegmentLength();
   lengthStep=getSegmentLineStep();
//cleaning procedure
   clearSegmentPoints();
   setSegmentType(LINE_STEP);
   setSegmentLineStep(lengthStep);
//starting of segment definition procedure
//add first point
   addSegmentPoint(beginSegment);
// add intermediate segment points after the first
   for (distance=lengthStep ; distance <lengthSegment ; distance=distance + lengthStep ){
     RadarPoint_util tmpPoint(latr,lonr,heightr,altTower);
     GeographicLib::Math::real latp,lonp;
     SegmentLine.Position((GeographicLib::Math::real)distance, latp, lonp);
     tmpPoint.setPointGeoCoordsHeight(latp,lonp,0.);
     tmpPoint.fillCoords();
     addSegmentPoint(tmpPoint);
   }
// check if segmentLength is a multiple of segmentStep. If is add endSegment to Segment.
   if (distance == lengthSegment) addSegmentPoint(endSegment);
   setSegmentNumPoint(SegmentPoint.size());
// ending of segment definition procedure
}


void RadarSegment_util::CalculateSegmentAzimuthStep(){
   GeographicLib::Math::real latr,lonr,latp,lonp, latfirst, lonfirst, lat_point, lon_point;
   GeographicLib::Math::real az_i, az_e,distance,increment,temp,loop_dist;
   GeographicLib::Math::real az_tmp;
   GeographicLib::Math::real az_old;
   float tmp_azimuth;
   float heightr, altTower;
   heightr=beginSegment.getHeightR();
   altTower=beginSegment.getAntennaTowerHeight();

   float lengthSegment, azimuthStep;
   lengthSegment=getSegmentLength();
   azimuthStep=getSegmentAzimuthStep();
//cleaning procedure
   clearSegmentPoints();
   setSegmentType(AZIMUTH_STEP);
   setSegmentAzimuthStep(azimuthStep);

// get fixed value foir radar and segment starting point
   latr=(GeographicLib::Math::real)beginSegment.getLatR();
   lonr=(GeographicLib::Math::real)beginSegment.getLonR();
   latfirst=(GeographicLib::Math::real)beginSegment.getPointLat();
   lonfirst=(GeographicLib::Math::real)beginSegment.getPointLon();
   
   const GeographicLib::Geodesic g1= GeographicLib::Geodesic::WGS84();
   GeographicLib::GeodesicLine TmpLine;
// compute the azimuthal angle for the segment beginSegment-radarSite. 
// This will be used as first value in the following operation
   temp=g1.Inverse(latfirst,lonfirst,latr,lonr,distance,az_tmp,az_e);

//starting of segment definition procedure
//add first point
   addSegmentPoint(beginSegment);
   int numpoint =1;
// add intermediate segment points after the first
   do {
// define a temporary  geodesicLine originating at radar with an azimuth which increase of azimuthstep at each iteration 
     tmp_azimuth=fmod(beginSegment.getAzimuth()+getSegmentVersus()*azimuthStep*numpoint+360.,360);
     TmpLine = g1.Line(latr,lonr,(GeographicLib::Math::real)(tmp_azimuth));
   //inner loop for search point in the intersection of segment and tmp line 
     loop_dist=0.;
     increment=10000.;
     int count=1;
     while (increment >= 1){
// calculate point coordinate   
       TmpLine.Position(loop_dist+count*increment,latp,lonp);
// calculate azimuth respect the segment starting point 
       temp=g1.Inverse(latfirst,lonfirst,latp,lonp,distance,az_i,az_e);
//check if it have been cross the segment
       if((fmod(az_i+360.,360.) - (GeographicLib::Math::real)getSegmentAzimuth()) * 
                (fmod(az_tmp+360.,360.) - (GeographicLib::Math::real)getSegmentAzimuth())< 0.) {
// yes - restart iteration from the last valid point with lower increment
         loop_dist= loop_dist + increment * (count-1);
         increment=increment * 0.1;
         count=1;
       } else {
//no - continue the iteration
         count++;
         az_tmp=az_i;
         lat_point=latp;
         lon_point=lonp;
       }
     }
// point defined
// calculate final  point coords
     lat_point=(lat_point+latp)*0.5;
     lon_point=(lon_point+lonp)*0.5;
     
//define a new object
     RadarPoint_util tmpPoint((float)latr,(float)lonr,heightr,altTower);
     tmpPoint.setPointGeoCoordsHeight(lat_point,lon_point,0.);
     tmpPoint.fillCoords();
//add the point to the vector
     addSegmentPoint(tmpPoint);
     numpoint++;
// calculate distance along the segment respect the segment starting point 
     temp=g1.Inverse(latfirst,lonfirst,lat_point,lon_point,distance,az_i,az_e);
// test if the point is out of the segment
   } while ((distance-getSegmentLength())<100.);

// remove the last added segment point which is out of the segment.
   SegmentPoint.pop_back();
// ending of segment definition procedure
   setSegmentNumPoint(SegmentPoint.size());
}

void RadarSegment_util::SetGeodesicLine(){
	const GeographicLib::Geodesic g1= GeographicLib::Geodesic::WGS84();
	GeographicLib::Math::real az_i, az_e,distance,temp;
	GeographicLib::Math::real lat1,lat2,lon1,lon2;
	lat1=(GeographicLib::Math::real) beginSegment.getPointLat();
	lon1=(GeographicLib::Math::real) beginSegment.getPointLon();
	lat2=(GeographicLib::Math::real) endSegment.getPointLat();
	lon2=(GeographicLib::Math::real) endSegment.getPointLon();
	temp=g1.Inverse(lat1,lon1,lat2,lon2,distance,az_i,az_e);
	setSegmentLength((float)distance);
//	setSegmentAzimuth((float)az_i);
	SegmentLine = g1.Line(lat1,lon1,az_i);
}

void RadarSegment_util::setSegmentLength(float value){
	segmentLength = value;
}
float RadarSegment_util::getSegmentAzimuth(){
	return	fmod(SegmentLine.Azimuth()+360.,360.);
}
float RadarSegment_util::getSegmentLength(){
	return	segmentLength;
}

RotationVersus RadarSegment_util::getSegmentVersus(){
  return segmentVersus;

}
bool RadarSegment_util::setSegmentVersus(){
// check if segment is along a singol ray or along opposite rays
   if ((beginSegment.getAzimuth() == endSegment.getAzimuth())||
       (fmod(beginSegment.getAzimuth()+180.,180.) == endSegment.getAzimuth())) return false;

   GeographicLib::Math::real latr,lonr,latp,lonp;
   GeographicLib::Math::real az_i, az_e,distance,temp;
   const GeographicLib::Geodesic g1= GeographicLib::Geodesic::WGS84();

   latr=beginSegment.getLatR();
   lonr=beginSegment.getLonR();
// set search distance lesser than segmenthLenghth
   distance = (GeographicLib::Math::real) (getSegmentLength()/3.);
// calculate geographic coordinate for a point at set distance along the segment from the beginning of the segment 
   SegmentLine.Position(distance, latp, lonp);
// calculate azimuth of this point from the radar site
   temp=g1.Inverse(latr,lonr,latp,lonp,distance,az_i,az_e);
//verify if it is CW or CCW
   segmentVersus = CCW;
   if ((float)az_i > beginSegment.getAzimuth() || fabs((float)az_i - beginSegment.getAzimuth()) < 200. ) segmentVersus = CW;
   return true;
}
void RadarSegment_util::setSegmentType(SegmentFillingMethod type){
  stepType=type;
}
SegmentFillingMethod RadarSegment_util::getSegmentType(){
  return stepType;
}   

void RadarSegment_util::setSegmentElevation(float elev){
  for (int i=0; i< SegmentPoint.size(); i++){
     SegmentPoint[i].setPointGeoCoordsElev(SegmentPoint[i].getPointLat(),SegmentPoint[i].getPointLon(),elev,true);
     SegmentPoint[i].fillCoords();
  }
}

void RadarSegment_util::setSegmentHeight(float height){
  for (int i=0; i< SegmentPoint.size(); i++){
     SegmentPoint[i].setPointGeoCoordsHeight(SegmentPoint[i].getPointLat(),SegmentPoint[i].getPointLon(),height,true);
     SegmentPoint[i].fillCoords();
  }
}

bool RadarSegment_util::isRHI(){
  if (beginSegment.getSurfaceDistance() < 1. ||
        endSegment.getSurfaceDistance() < 1.  ) return true;
  return false;
}

bool  RadarSegment_util::isSegmentLengthValid(){
  if (getSegmentLength() > SEGMENT_LENGTH_MINIMUM) return true;
  return false;
}

void RadarSegment_util::printSegmentInfo(std::ostream& out ){
  out<<"=========================================="<<std::endl;
  out<<"Printout Segment information "<<std::endl;
  out<<"Segment segmentation method : "<<getSegmentType()<<std::endl;
  out<<"Number of point defined : " <<getSegmentNumPoint()<<std::endl;
  out<<"Azimuth step : "<<getSegmentAzimuthStep()<<std::endl;
  out<<"Linear step : "<<getSegmentLineStep()<<std::endl;
  out<<"Segment length : "<<getSegmentLength()<<std::endl;
  out<<"Segment Direction : "<<getSegmentAzimuth()<<std::endl;
  if(isRHI()) {
     out<<" YES" <<std::endl;
  } else out<<" NO"<<std::endl;
  out<<"Starting point "<<std::endl;
  out<<"Geodesic   Coordinate (Azimuth, SurfDist)  :"<<beginSegment.getAzimuth()<<" , "<<beginSegment.getSurfaceDistance()<<std::endl;
  out<<"Geographic Coordinate (Lat, Lon)           :"<<beginSegment.getPointLat()<<" , "<<beginSegment.getPointLon()<<std::endl;
  out<<"Geognomic  Coordinate (X,Y)                :"<<beginSegment.getPointXCoord()<<" , "<<beginSegment.getPointYCoord()<<std::endl;
  out<<"Range     : "<<beginSegment.getBeamDistance();
  out<<"Height    : "<<beginSegment.getHeight()<<std::endl;
  out<<"Ending point "<<std::endl;
  out<<"Geodesic   Coordinate (Azimuth, SurfDist)  :"<<endSegment.getAzimuth()<<" , "<<endSegment.getSurfaceDistance()<<std::endl;
  out<<"Geographic Coordinate (Lat, Lon)           :"<<endSegment.getPointLat()<<" , "<<endSegment.getPointLon()<<std::endl;
  out<<"Geognomic  Coordinate (X,Y)                :"<<endSegment.getPointXCoord()<<" , "<<endSegment.getPointYCoord()<<std::endl;
  out<<"Range     : "<<endSegment.getBeamDistance();
  out<<"Height    : "<<endSegment.getHeight()<<std::endl;
  out<<"=========================================="<<std::endl;
} 

float RadarSegment_util::distanceAlongSegment(int i){
  if( i < getSegmentNumPoint()){
	const GeographicLib::Geodesic g1= GeographicLib::Geodesic::WGS84();
	GeographicLib::Math::real az_i, az_e,distance,temp;
	GeographicLib::Math::real lat1,lat2,lon1,lon2;
	lat1=(GeographicLib::Math::real) beginSegment.getPointLat();
	lon1=(GeographicLib::Math::real) beginSegment.getPointLon();
	lat2=(GeographicLib::Math::real) SegmentPoint[i].getPointLat();
	lon2=(GeographicLib::Math::real) SegmentPoint[i].getPointLon();
	temp=g1.Inverse(lat1,lon1,lat2,lon2,distance,az_i,az_e);
        return (float) distance;
  } else return -1.;
}
