/*!
 * \file
 * \brief Class to manage relationship between radar site and a segment (defined by two points and a versus) 
 */
#ifndef __RADAR_SEGMENT_UTIL__
#define __RADAR_SEGMENT_UTIL__

#include <limits>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include <GeographicLib/Math.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <radarcoordlib/radar_coord_exceptions.hpp>
#include <radarcoordlib/generic.hpp>
#include <radarcoordlib/RadarBeamCoord_util.hpp>
#include <radarcoordlib/RadarGeoCoord_util.hpp>
#include <radarcoordlib/RadarPoint_util.hpp>
   
#define SEGMENT_LENGTH_MINIMUM 1.

/*!
 * \brief Definition of filling types\n 
 */
/*!
 * Possible values \n
 * NOT_DEF_STEP_TYPE    not defined filling method\n
 * NUM_POINT            Number of segment point based method\n
 * LINE_STEP            Fixed segment interval distance based method\n
 * AZIMUTH_STEP         Fixed Azimuthal distance based method
 */
enum SegmentFillingMethod {NOT_DEF_STEP_TYPE,NUM_POINT, LINE_STEP, AZIMUTH_STEP};

/*!
 * \brief Versus of rotation 
 */
/*!
 * Possible values \n
 * CW ClockWise (equal 1)\n
 * CCW CounterClockWise (equal -1)\n
 */
enum RotationVersus{CW=1, NOT_DEF_ROT_VERSUS = 0, CCW=-1};

/*!
 * \brief Class to calculate radar point coordinates along a defined segment relative to radar site
 *
 * This class compute (back and for) Earth coordinate calculations and radar coordinate of points alongs segment  \n
 * relative to a defined radar site.
 */
/*!
 * The point coordinate could be passed as one of the following options:\n
 * - Geographic (Latitude, Longitude,height)\n
 * - Aeqd projection centred on the radar site (Xcoord, Ycoord, height) in meter\n
 * - Geodetic coordinate (Azimuth, distance over Earth surface, height) (Degree, meter)\n
 * - Radar (Azimuth, Elevation, slatwise distance along the range) (Degree, degree, meter)
 */ 
/*! 
 * This class implement segment defined as a couple of obj defined by RadarPoint_util
 * \sa RadarPoint_util::
 */ 
class RadarSegment_util{
private: 
/*!
 * First point of the of segment
 */
	RadarPoint_util beginSegment;
/*!
 * Last point of the of segment
 */
	RadarPoint_util endSegment;
/*!
 * Lenght of the segment
 */
	float segmentLength;

/*!
 * Geodesic Line between Segment extremes (from beginSegment to endSegment)
 */
	 GeographicLib::GeodesicLine SegmentLine;
         
/*!
 * Number of points along the segment
 */
	int numPoint;
/*!
 * Size of interval between adiacent points along the segment
 */
/*! 
 * Note that if the points along the segment are defined at regular azimth distance this quantity is not regular
 */
	float segmentStep;
/*!
 * Azimuth distance between adiacent points along the segment
 */
/*! 
 * Note that if the points along the segment are defined at regular interval distance this quantity is not regular
 */
	float AzimuthStep;
/*!
 * Definition of how segment points are defined
 */ 
	SegmentFillingMethod stepType;
/*!
 * Vettore contente i punti del segmento. Ogni punto è definito come oggetto di tipo RadarPoint_util
 */
	vector <RadarPoint_util> SegmentPoint;

/*!
 * Segment versus (CW-CCW)
 */
	RotationVersus segmentVersus;
	
public:
	/*! 
         *\brief Constructor
	 */
	/*!
	 * Inizialize radar site coordinates at \n
	 * Lat                 : 0. N - 
	 * Lon                 : 0. E - 
	 * Height              : 0. m - 
	 * Antennatower height : 0. m \n 
	 * First and last points of the segment are set to missing value
	 */ 
	RadarSegment_util(); 
	/*!
         *\brief Constructor with radar coordinates passed
	 * First and last points of the segment are set to missing value
	 *\param[in] latr    - Radar site Latitude
	 *\param[in] lonr    - Radar site Longitude
	 *\param[in] heightr - Height above the msl of radar site (antenna tower not included)
	 *\param[in] aTH     - Height of the electric antenna focus related above the surface
	 */
	RadarSegment_util(float latr,float lonr,float heightr, float aTH);

 	/*! 
         *\brief Set radar coordinates for the segment, clear any other informations 
	 * First and last points of the segment are set to missing value
	 *\param[in] latr    - Radar site Latitude
	 *\param[in] lonr    - Radar site Longitude
	 *\param[in] heightr - Height above the msl of radar site (antenna tower not included)
	 *\param[in] aTH     - Height of the electric antenna focus related above the surface
	 */
	void setRadarCoord(float latr,float lonr,float heightr, float aTH);

/*!
 * \brief Set segment extremes in geographic coordinate
 * \param[in] lat_begin   Latitude  of the first point of the segment (Degree N)
 * \param[in] lon_begin   Longitude of the first point of the segment (Degree E)
 * \param[in] lat_end     Latitude  of the last  point of the segment (Degree N)
 * \param[in] lon_end     Longitude of the last  point of the segment (Degree E)
 * \return  true if segment set
 */
/*!
 * NOTE - This method set the initial height of points to 0 meter (asl) and compute all coordinates
 * \sa RadarPoint_util::setPointGeoCoordsHeight
 * \sa RadarPoint_util::fillCoords
 */
	bool  setSegmentGeo(float lat_begin, float lon_begin, float lat_end, float lon_end) ;
/*!
 * \brief Set segment extremes in gnomonic coordinate
 * \param[in] x_begin   X of the first point of the segment (meter)
 * \param[in] y_begin   Y of the first point of the segment (meter)
 * \param[in] x_end     X of the last point of the segment (meter)
 * \param[in] y_end     Y of the last point of the segment (meter)
 * \return  true if segment set
 */
/*!
 * NOTE - This method set the initial height of points to 0 meter (asl) and compute all coordinates
 * \sa RadarPoint_util::setPointAeqdCoordsHeight
 * \sa RadarPoint_util::fillCoords
 */
	bool  setSegmentAeqd(float x_begin, float y_begin, float x_end, float y_end) ;
/*!
 * \brief Set segment extremes in geodesic coordinate relative to radar site
 * \param[in] az_begin         Azimuth X of the first point of the segment (Degree from N in clockwise direction)
 * \param[in] surfDist_begin   Surface Distance of the first point of the segment (meter)
 * \param[in] az_end           Azimuth of the last point of the segment (Degree from N in clockwise direction)
 * \param[in] surfDist_end     Surface Distance of the last point of the segment (meter)
 * \return  true if segment set
 */
/*!
 * NOTE - This method set the initial height of points to 0 meter (asl) and compute all coordinates
 * \sa RadarPoint_util::setPointGeodesicCoordinateHeight
 * \sa RadarPoint_util::fillCoords
 */
	bool  setSegmentGeodesic(float az_begin, float surfDist_begin, float az_end, float surfDist_end) ;
/*!
 * Clear segment Object, remove extremes, points and any other information
 */
	void clearSegment();
/*!
 * Clear segment Points and segment filling method information\n
 * Note that this method maintain the information related to segment extremes.
 */
	void clearSegmentPoints();
/*!
 * \brief Return the segment direction - Azimuth
 * \return segmentAzimuth
 */
	float getSegmentAzimuth();
/*!
 * \brief Return the segment lenght
 * \return segmentLength
 */
	float getSegmentLength();
/*!
 * \brief Define segment subdivision 
 * \param[in] type	define subdivison type\n
 *                         NPOINT      - Number of point\n
 *                         LINESTEP    - Interval distance along the segment\n
 *                         AZIMUTHSTEP - Azimuthal distance between two point along the segment\n
 * \param[in] value	Value to be set
 */
	void setSegmentStep(SegmentFillingMethod type, float value);
/*!
 * \brief Calculate segment point 
 */
	void CalculateSegment();

/*! 
 * \brief Get segment
 * \return segment Vector of RadarPoint_util objects for the segment
 */

	vector<RadarPoint_util> getSegment();
/*! 
 * \brief Get segment point
 * \param[in] index   index of the vector element.
 * \return segment point. RadarPoint_util object
 */

	RadarPoint_util getSegmentPoint(int index);
/*!
 * \brief Add a segment point at the end of the vector
 * \param[in] point    Point object to be added
 */
	void addSegmentPoint(RadarPoint_util point);
/*!
 * \brief Add a segment point in the position passed
 * \param[in] index position of point to be added in the vector
 * \param[in] point    Point object to be added
 * \return true is index lesser than vector size
 */ 
	bool addSegmentPoint(int index,RadarPoint_util point);
/*!
 * \brief Set segment filling method
 * \param[in] type	define subdivison type\n
 *                         NPOINT      - Number of point\n
 *                         LINESTEP    - Interval distance along the segment\n
 *                         AZIMUTHSTEP - Azimuthal distance between two point along the segment\n
 */
	void setSegmentType(SegmentFillingMethod type);
/*!
 * \brief Get the segment filling method utilized
 * \return method user (SegmentFillingMethod)
 */
	SegmentFillingMethod getSegmentType();
/*!
 * \brief Return the number of segment points 
 * \return numPoint Number of segment points
 */
	int getSegmentNumPoint();
/*!
 * \brief Return segment interval  
 * \return segmentStep	Interval distance along the segment
 */
	float getSegmentLineStep();
/*!
 * \brief Return segment Azimuth step
 * \return AzimuthStep	Azimuthal distance between two point along the segment
 */
	float getSegmentAzimuthStep();
/*!
 * \brief return the segment versus
 * return segmentVersus attribute 
 */
	RotationVersus getSegmentVersus();

/*!
 * \brief Set segment Elevation 
 * \param[in] elev Elevation value (Degree)
 */
/*!
 * This operation is executed for each point defined in the segment, not on beginSegment and endSegment attributes\n
 * Vertical coords are syncronized according to the elevation value passed\n
 * Radar coordinates are computed accordingly to the elevation value set.\n
 */
	void setSegmentElevation(float elev);
/*!
 * \brief Set segment Height 
 * \param[in] height Height above the sea level (meter)
 */
/*!
 * This operation is executed for each point defined in the segment, not on beginSegment and endSegment attributes\n
 * Vertical coords are syncronized according to the height value passed\n
 * Radar coordinates are computed accordingly to the height value set.\n
 */
	void setSegmentHeight(float height);

/*!
 * \brief Check if segment is an RHI
 * \return true if segment is an RHI
 */
/*!
 * NOTE:\n
 * An RHI is defined if the starting point or the ending point of the segment\n
 * is at a distance from the radat site less than 1 meter
 */
	bool isRHI();
/*!
 *\brief check if SegmentLength is valid 
 *\return true if Segment Length is greater than 1 meter.
*/
	bool  isSegmentLengthValid();

/*!
 * \brief Segment information on a output stream
 * \param[in] out -  an output stream - optional
 */
  void printSegmentInfo(std::ostream& out = std::cout);

/*!
 * \brief Calculate distance along the segment from segment starting point
 * \param[in] i - index of segment point
 * \return distance (m)
 */
  float distanceAlongSegment(int i);

private:
/*!
 * \brief Calculate and set segment versus
 * return true if calculation is possible (starting and ending points defined)
 */
	bool setSegmentVersus();

/*!
 * \brief Define Segment lenght
 * \param[in] value - Lenght of the segment (meter)
 */
	void setSegmentLength(float value);
/*!
 * \brief Define segment numpoint 
 * \param[in] value	Number of segment points
 */
	void setSegmentNumPoint(int value);
/*!
 * \brief Define segment Line step 
 * \param[in] value	Interval distance along the segment (meter)
 */
	void setSegmentLineStep(float value);
/*!
 * \brief Define segment Azimuth step
 * \param[in] value	Azimuthal distance between two point along the segment (degree)
 */
	void setSegmentAzimuthStep(float value);

/*!
 * \brief Calculate segment point for NumPoint method
 */
	void CalculateSegmentNumPoint();
/*!
 * \brief Calculate segment point for LineStep method
 */
	void CalculateSegmentLineStep();
/*!
 * \brief Calculate segment point for AzimuthStep method
 */
	void CalculateSegmentAzimuthStep();
/*!
 * \brief set of GeodesicLine
 */
	void SetGeodesicLine();
};

#endif
