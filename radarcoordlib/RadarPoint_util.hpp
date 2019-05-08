/*!
 * \file
 * \brief Class to manage relationship between radar site and a single point 
 */
#ifndef __RADAR_POINT_UTIL__
#define __RADAR_POINT_UTIL__

#include <limits>
#include <iostream>
using namespace std;


#include <radarcoordlib/radar_coord_exceptions.hpp>
#include <radarcoordlib/generic.hpp>
#include <radarcoordlib/RadarBeamCoord_util.hpp>
#include <radarcoordlib/RadarGeoCoord_util.hpp>
/*!
 * \brief Class to calculate radar point coordinates related to radar place and coordinates
 *
 * This class compute (back and for) Earth coordinate calculations and radar coordinate of a single point \n
 * related to a radar position.
 */
/*!
 * The point coordinate could be passed as one of the following options:\n
 * - Geographic (Latitude, Longitude,height)\n
 * - Aeqd projection centred on the radar site (Xcoord, Ycoord, height) in meter\n
 * - Geodetic coordinate (Azimuth, distance over Earth surface, height) (Degree, meter)\n
 * - Radar (Azimuth, Elevation, slatwise distance along the range) (Degree, degree, meter)
 */ 
/*!
 * This class compute conversion between coordinate system
 */
class RadarPoint_util : public RadarGeoCoord_util{
//private:
protected:
/*!
 *Slantwise distance of the radar point along the radar beam (meter)
 */
	float BeamDistance;
/*!
 * Elevation of the radar beam (Degree)
 */
	float Elevation;

/*! Height (meter above msl) of the center of the radar beam at the radar point */
	float Height;


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
	 * Point coordinates are set to missing value
	 */ 
	RadarPoint_util(); 
	/*!
         *\brief Constructor with radar coordinates passed
	 * Point coordinates are set to missing value
	 *\param[in] latr    - Radar site Latitude
	 *\param[in] lonr    - Radar site Longitude
	 *\param[in] heightr - Height above the msl of radar site (antenna tower not included)
	 *\param[in] aTH     - Height of the electric antenna focus related above the surface
	 */
	RadarPoint_util(float latr,float lonr,float heightr, float aTH);

	/*!
         *\brief Constructor with radar coordinates pnd point coordinate passed
	 * Point coordinates are set to missing value
	 *\param[in] latr      - Radar site Latitude (Degree N)
	 *\param[in] lonr      - Radar site Longitude (Degree E)
	 *\param[in] heightr   - Height above the msl of radar site (antenna tower not included) (meter)
	 *\param[in] aTH       - Height of the electric antenna focus related above the surface (meter)
	 *\param[in] azimuth   - Azimuth of the radar beam (Degree)
	 *\param[in] elevation - Elevation of the radar beam above the horizon (Degree)
         *\param[in] range     - Slantwise distance along teh radar beam (meter)
	 */ 
	RadarPoint_util(float latr,float lonr,float heightr, float aTH, float azimuth, float elevation, float range);
/*!
 * \brief copy constructor
 */
// RadarPoint_util (const RadarPoint_util &param);

/*!
 * \brief Check if Elevation is valid
 * \return true if coordinate is set
 */
	bool isElevationSet() ;

/*!
 * \brief Get beam Elevation used
 * \return Elevation (degree above horizon)
 */
	float getElevation();

/*!
 * \brief Check if height is valid
 */
	bool isHeightSet(); 

/*!
 *  \brief Get beam height (above msl)
 * \return Height (meter)
 */
	float getHeight ();

/*!
 * \brief Check if slantwise distance along the ray is valid (equal or greater than 0.)
 */
	bool isBeamDistanceSet(); 

/*!
 *  \brief Get slantwise distance along the ray
 * \return BeamDistance (meter)
 */
	float getBeamDistance ();

/*!
 * \brief Check if radar coordinates are set
 * \return true if Azimuth,BeamDistane and one of Elevation or Height are set
 */
	bool isRadarCoordsSet();

/*!
 * \brief Set Point coordinates to missing
 */
	void setPoint2Missing();

/*!
 * \brief Set Aeqd coordinates (Aeqd projection centred on radar site)
 * \param[in] X  - x coordinate (meter)
 * \param[in] Y  - y coordinate (meter)
 * \param[in] H  - height above msl (meter)
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Elevation coordinate will be unset. 
 */
	void setPointAeqdCoordsHeight(float X, float Y, float H, bool cleanOtherCoords = true);
/*!
 * \brief Set Aeqd coordinates (Aeqd projection centred on radar site)
 * \param[in] X     - x coordinate (meter)
 * \param[in] Y     - y coordinate (meter)
 * \param[in] Elev  - Elevation above horizon (Degree)
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Height coordinate will be unset. 
 */
	void setPointAeqdCoordsElev(float X, float Y, float Elev, bool cleanOtherCoords = true);

/*!
 * \brief Set point geographic coordinates
 * \param[in] lat  - latitude (degree N)
 * \param[in] lon  - longitude (degree E)
 * \param[in] H  - height above msl (meter)
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Elevation coordinate will be unset. 
 */
	void setPointGeoCoordsHeight(float lat, float lon, float H, bool cleanOtherCoords = true);

/*!
 * \brief Set point geographic coordinates
 * \param[in] lat               Latitude (degree N)
 * \param[in] lon               Longitude (degree E)
 * \param[in] Elev              Elevation above horizon (Degree)
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Height coordinate will be unset. 
 */
	void setPointGeoCoordsElev(float lat, float lon, float Elev, bool cleanOtherCoords = true);

/*!
 * \brief  Set Geodesic coordinate (Azimuth, Surface distance)
 * \param[in] Azimuth           Direction from radar site (Degree N)
 * \param[in] H                 Height above msl (meter)
 * \param[in] SurfaceDist       Distance over the Earth surface between radar site and Earth point
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Elevation coordinate will be unset. 
 */
	void setPointGeodesicCoordinateHeight (float Azimuth, float SurfaceDist, float H, bool cleanOtherCoords = true);

/*!
 * \brief  Set Geodesic coordinate (Azimuth, Surface distance)
 * \param[in] Azimuth           Direction from radar site (Degree N)
 * \param[in] Elev              Elevation above horizon (Degree)
 * \param[in] SurfaceDist       Distance over the Earth surface between radar site and Earth point
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Height coordinate will be unset. 
 */
 
	void setPointGeodesicCoordinateElev (float Azimuth, float SurfaceDist, float Elev, bool cleanOtherCoords = true); 

/*!
 * \brief  Set Point radar coordinate (Azimuth, Elevation, Beam distance)
 * \param[in] Azimuth           Direction from radar site (Degree N)
 * \param[in] Elev              Elevation above horizon (Degree)
 * \param[in] BeamDist          Slantwise distance along the ray (m) 
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Height coordinate will be unset. 
 */
	void setPointRadarCoordinateElev (float Azimuth, float Elev, float BeamDist, bool cleanOtherCoords = true); 

/*!
 * \brief  Set Point radar coordinate (Azimuth, H, Beam distance)
 * \param[in] Azimuth           Direction from radar site (Degree N)
 * \param[in] H                 Height above msl (meter)
 * \param[in] BeamDist          Slantwise distance along the ray (m)
 * \param[in] cleanOtherCoords  If true Geodesic and Geographic and Elevation coordinate will be unset. 
 */
	void setPointRadarCoordinateHeight (float Azimuth, float H, float BeamDist, bool cleanOtherCoords = true); 

/*!
 * \brief Compute Height of the center of the radar beam based on elevation and range
 * \return True is Calculation is done
 */ 
	bool radarElev2radarHeight();
/*!
 * \brief Compute Elevation based on Height of the center of the radar beam and range
 * \return True is Calculation is done
 */ 
	bool radarHeight2radarElev();
/*!
 * \brief Check if it is possible syncronize the two vertical coords. Calculate the unset coords if possible.
 * \return True is Calculation is done
 */ 
	bool syncRadarVerticalCoord();

/*!
 * \brief Compute Aeqd coordinate (X,Y) from radar coordinate
 * \return True is Calculation of Aeqd coordinate is done
 */ 
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool RadarCoords2AeqdCoords();

/*!
 * \brief Compute Geographic coordinate (Lat,Lon) from radar coordinate
 * \return True is Calculation of Geographic coordinate is done
 */ 
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool RadarCoords2GeoCoords();

/*!
 * \brief Compute Geodetic coordinate (Azimuth, surfaceDistance) from radar coordinate
 * \return True is Calculation of Geodetic coordinate is done
 */ 
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool RadarCoords2GeodeticCoords();

/*!
 * \brief Compute Aeqd, Geographic and Geodetic coordinates from radar coordinate
 * \return True is Calculation of Geodetic, Geographic and Aeqd coordinate is done
 */ 
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool RadarCoords2OthersCoords();

/*!
 * \brief Compute radar coordinate from Aeqd coordinate (X,Y) 
 * \return True is Calculation of Radar coordinate is done
 */
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool AeqdCoords2RadarCoords();

/*!
 * \brief Compute radar coordinate from Geographic coordinate (Lat,Lon)
 * \return True is Calculation of Radar coordinate is done
 */ 
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool GeoCoords2RadarCoords();

/*!
 * \brief Compute radar coordinate from Geodetic coordinate (Azimuth, surfaceDistance)
 * \return True is Calculation of Radar coordinate is done
 */ 
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool GeodeticCoords2RadarCoords();
	
/*!
 * \brief  Compute point coordinates for all Radar, Aeqd,Geographic and Geodesic systems and syncronize vertical coords
 * \return True if calculation of coordinate is done\n
 *         False if calcualtion is not possible
 */
/*!
 * NOTE:  One of Elevation/Height should be set, the other will be computed
 */
	bool fillCoords () ;

/*!
 * \brief copy operator
 */
 RadarPoint_util& operator = (RadarPoint_util param);

protected:

/*!
 * \brief Set height (above msl) of the center of the beam 
 * \param[in]  value (meter)
 */
	void setHeight (float value); 

/*!
 * \brief Set slantwise distance along the ray 
 * \param[in]  value (meter)
 */
	void setBeamDistance (float value); 

/*!
 * \brief Set beam elevation
 * \param[in]  value (degree above horizon)
 */
	void setElevation(float value);
};

#endif
