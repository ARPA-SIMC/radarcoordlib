/*!
 * \file
 * \brief Class to manage relationship between radar site and a single point over the Earth
 */
#ifndef __RADAR_GEO_COORD__
#define __RADAR_GEO_COORD__

#include <limits>
#include <iostream>
using namespace std;

/* Utilizzo le funzioni messe a disposizione dalla GegraphicLib per muovermi sul geoide */
#include <GeographicLib/Math.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/GeodesicLine.hpp>
#include <GeographicLib/Gnomonic.hpp>

#include <radarcoordlib/radar_coord_exceptions.hpp>
#include <radarcoordlib/generic.hpp>
#include <radarcoordlib/RadarSite.hpp>
#include <radarcoordlib/RadarBeamCoord_util.hpp>

using namespace GeographicLib;
/*!
 * \brief Class to calculate point coordinates related to radar place and coordinates
 *
 * This class compute (back and for)  Earth coordinate calculations of a single point \n
 * related to radar position.
 */
/*!
 * The point coordinate could be passed as one of the following options:\n
 * - Geographic (Latitude, Longitude)\n
 * - Gnomonic projection centred on the radar site (Xcoord, Ycoord) in meter\n
 * - Geodetic coordinate (Azimuth, distance over Earth surface) (Degree, meter)
 */ 
class RadarGeoCoord_util{
 protected: 

//private :

        /*! Radar_site */
	/*! Radar site coordinate */
	RadarSite radar_site;

	/*! Xcoord_p */
	/*! Gnomonic X coordinate value for the point evaluated */
	float  Xcoord_p;
	/*! Ycoord_p */
	/*! Gnomonic Y coordinate value for the point evaluated */
	float  Ycoord_p;
	/*! Lat_p */
	/*! Latitude coordinate for the point evaluated */
	/*! \sa generic::checkLatitude*/
	float  Lat_p;
	/*! Lon_p */
	/*! Longitude coordinate for the point evaluated */
	/*! \sa generic::checkLongitude*/
	float  Lon_p;
	/*! surfaceDistance */
	/*! Distance between radar and point on the geodetic line */
	float surfaceDistance;
	/*! Azimuth */
	/*! Azimuth form north of the geodetic line at the radar site*/
	float Azimuth;

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

	RadarGeoCoord_util(); 
	/*!
         *\brief Constructor with radar coordinates passed
	 * Point coordinates are set to missing value
	 *\param latr    - Radar site Latitude
	 *\param lonr    - Radar site Longitude
	 *\param heightr - Height above the msl of radar site (antenna tower not included)
	 *\param aTH     - Height of the electric antenna focus related above the surface
	 */
	RadarGeoCoord_util(float latr,float lonr,float heightr, float aTH);

	/*! 
	 *\brief get radar latitude value 
	 * \return Radar site Latitude
	 */
	float getLatR();

	/*! 
	 *\brief get radar longitude value 
	 *\return  Radar site Longitude
	 */
	float getLonR();

	/*! 
	 *\brief get radar height above msl value 
	 *\return Height above the msl of radar site (antenna tower not included)
	 */
	float getHeightR();

	/*! 
	 *\brief get beam electromagnetic focus height above surface value 
	 *\return Height of the electric antenna focus related above the surface
	 */
	float getAntennaTowerHeight();

	/*!
	 *\brief Set radar coordinates
	 *\param[in] latr            Radar site Latitude
	 *\param[in] lonr            Radar site Longitude
	 *\param[in] heightr         Height above the msl of radar site (antenna tower not included)
	 *\param[in] aTH             Height of the electric antenna focus related above the surface
	 *\param[in] cleanPointCoord if true all point coordinate are cleaned
	 */
	void setRadarCoord(float latr,float lonr,float heightr, float aTH, bool cleanPointCoord = true); 

	/*!
	 * \brief Set Point coordinates to missing
	 */
	virtual void setPoint2Missing();

	/*!
	 * \brief Set Gnomonic coordinates (Gnomonic projection centred on radar site)
	 * \param[in] X  - x coordinate (meter)
	 * \param[in] Y  - y coordinate (meter)
	 * \param[in] cleanOtherCoords  If true Geodesic and Geographic coordinate will be unset. 
	 */
	void setPointGnomoCoords(float X, float Y, bool cleanOtherCoords = true) ;

	/*!
	 * \brief Check if point X coordinate is valid
	 * \return true if coordinate is set
	 */
	bool isPointXCoordSet(); 

	/*!
	 * \brief Check if point Y coordinate is valid
	 * \return true if coordinate is set
	 */
	bool isPointYCoordSet(); 

	/*!
	 * \brief Check if point Gnomonic coordinates are valid
	 * \return true if both coordinates are set
	 */
	bool isPointGnomoCoordsSet();

	/*!
	 * \brief Get point X coordinate (Gnomonic projection centred on radar site)
	 * \return x coordinate (meter)
	 */
	float getPointXCoord(); 

	/*!
	 * \brief Get point y coordinate (Gnomonic projection centred on radar site)
	 * \return y coordinate (meter)
	 */
	float getPointYCoord(); 

	/*!
	 * \brief Compute geographic coordinates from Gnomonic coordinates
	 * \return true if geographich coordinates are calculated
	 */
	bool GnomoCoords2GeoCoords () ;
	
	/*!
	 * \brief Set point geographic coordinates
	 * \param[in] lat  - latitude (degree N)
	 * \param[in] lon  - longitude (degree E)
	 * \param[in] cleanOtherCoords  If true Geodesic and Gnomonic coordinate will be unset. 
	 */
	void setPointGeoCoords(float lat, float lon, bool cleanOtherCoords = true) ;

	/*!
	 * \brief Check if point longitude is valid and set.
	 * \return true if longitude valide and set.
	 */
	bool isPointLongitudeSet();

	/*!
	 * \brief Check if point latitude is valid and set.
	 * \return true if latitude valide and set.
	 */
	bool isPointLatitudeSet() ;

	/*!
	 * \brief Check if point Geographic coordinates are valid
	 */
	bool isPointGeoCoordsSet(); 
	
	/*!
	   \brief Get point latitude
	 * \return latitude (degree N)
	 */
	float getPointLat(); 

	/*!
	 * \brief Get point longitude
	 * \return longitude (degree E)
	 */
	float getPointLon(); 

	/*!
	 * \brief Compute Gnomonic coordinates fro Geographic coordinates
	 * \return true if gnomonic coordinates are calculated
	 */
	bool GeoCoords2GnomoCoords () ;
	
	/*!
	 * \brief Calculate Earth distance and Azimuth from radar site to the point set.
	 */
	/*! 
 	* One of Gnomonic or Geographic coords should be set
 	* Detail description\n
 	* Geodesic parameters are calculate based on 
 	* GeographicLib available at http://sourceforge.net/projects/geographiclib/
 	*\return True if calculation of Geodetic parameters converge\n
 	*        False if calcualtion is not possible
 	*/ 
	bool calculateGeodesicParam() ;
	
	/*!
	 * \brief Calculate geographic and gnomonic coordinates from Earth distance and Azimuth.
	 */
	/*! 
	 * Detail description\n
	 * Invert Geodesic calculation are based on 
	 * GeographicLib available at http://sourceforge.net/projects/geographiclib/
	 *\return True if calculation of iGeographic coordinate is done\n
	 *        False if calcualtion is not possible
	 */ 
	bool invertGeodesicCalculation() ;

	/*!
	 * \brief  Set Geodesic coordinate (Azimuth, Surface distance)
	 * \param[in] Azimuth           direction from radar site (Degree N)
	 * \param[in] SurfaceDist       distance over the Earth surface between radar site and Earth point
	 * \param[in] cleanOtherCoords  If true Gnomonic and Geographic coordinate will be unset. 
	 */
	void setPointGeodesicCoordinate (float Azimuth, float SurfaceDist, bool cleanOtherCoords = true);

	 /*!
	 * \brief Check if geodetic Azimuth is set.
	 * \return true if geodetic azimuth is set.
	 */
	bool isAzimuthSet() ; 

	/*!
	 * \brief Check if 
	 * \return true if geodetice distance is set.
	 */
	bool isSurfaceDistanceSet() ;

	/*!
	 * \brief Check if point Geodetic coordinates are set
	 * \return true if set
	 */
	bool isGeodesicCoordsSet(); 
	
	/*!
	 * \brief Get distance on the Earth surface
	 * \return Distance over Earth surface (meter)
	 */
 	float getSurfaceDistance() ;
	
	/*!
	 * \brief Get Azimuth of geodetic between radar site and point
	 * \return Azimuth (degree from North clockwise)
	 */
	float getAzimuth() ;
	
	/*!
	 * \brief Compute point coordinates for all Gnomonic,Geographic and Geodesic systems
	 * \return True if calculation of coordinate is done\n
	 *        False if calcualtion is not possible
	 */
	virtual bool fillCoords () ;

protected:
	/*! 
	 *\brief set radar latitude value 
	 *\param[in] value    - Radar site Latitude
	 * \throw RadarCoordBadDataException  - if value passed if outsite [-90, +90] 
	 */
	void setLatR( float value) ;

	/*! 
	 *\brief set radar longitude value 
	 *\param[in] value    - Radar site Longitude
	 * \throw RadarCoordBadDataException  - if value passed if outsite [-180, +180] 
	 */
	void setLonR( float value);

	/*! 
	 *\brief set radar height above msl value 
	 *\param[in] value - Height above the msl of radar site (antenna tower not included)
	 */
	void setHeightR( float value);

	/*! 
	 *\brief set beam electromagnetic focus height above surface value 
	 *\param value     - Height of the electric antenna focus related above the surface
	 * \throw RadarCoordBadDataException  - if value passed if outsite [0, +100] 
	 */
	void setAntennaTowerHeight( float value);

	/*!
	 * \brief Set point X coordinate (Gnomonic projection centred on radar site)
	 * \param[in] value  - x coordinate (meter)
	 */
	void setPointXCoord(float value); 

	/*!
	 * \brief Set point y coordinate (Gnomonic projection centred on radar site)
	 * \param[in] value  - y coordinate (meter)
	 */
	void setPointYCoord(float value); 

	/*!
	   \brief Set point latitude
	 * \param[in] value  - latitude (degree N)
	 * \throw RadarCoordBadDataException if value passed if outsite [-90, +90] 
	 */
	void setPointLat(float value);

	/*!
	 * \brief Set point longitude
	 * \param[in] value  - longitude (degree E)
	 * \throw RadarCoordBadDataException if value passed if outsite [-180, +180] 
	 */
	void setPointLon(float value);

	/*!
	 * \brief Set distance on the Earth surface
	 * \param[in] value distance over Earth surface (meter)
	 */
	 void setSurfaceDistance(float value);
	
	/*!
	 * \brief Set Azimuth of geodetic between radar site and point
	 * \param[in] value Azimuth (degree from North clockwise)
	 */
	 void setAzimuth(float value); 
};

#endif

