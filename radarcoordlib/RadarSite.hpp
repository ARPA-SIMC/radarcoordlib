/*!
 * \file
 * \brief Class to store radar site coordinates
 */
#ifndef __RADAR_SITE__
#define __RADAR_SITE__

#include <limits>
#include <iostream>
using namespace std;

#include <radarcoordlib/radar_coord_exceptions.hpp>
#include <radarcoordlib/generic.hpp>

/*!
 * \brief Class to store radar site coordinate
 */
class RadarSite{
  private :
	/*! lat_r */
 	/*! Latitude of the radar place */
	/*! \sa checkLatitude*/
	float lat_r;
	/*! lon_r */
	/*! Longitude of radar place */
	/*! \sa checkLongitude*/
	float lon_r;
	/*! height_r */
	/*! Height above the msl of radar position (antenna tower not included)*/
	float height_r;
	/*! antennaTowerHeight */
	/*! Height of the electric antenna focus related above the surface*/
	float antennaTowerHeight;

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
	 */ 
	RadarSite() {
	  setRadarCoord(0.,0.,0.,0.);
	}
	/*!
         *\brief Constructor with radar coordinates passed
	 *\param latr    - Radar site Latitude
	 *\param lonr    - Radar site Longitude
	 *\param heightr - Height above the msl of radar site (antenna tower not included)
	 *\param aTH     - Height of the electric antenna focus related above the surface
	 */
	RadarSite(float latr,float lonr,float heightr, float aTH) ;

/*! 
 *\brief set radar latitude value 
 *\param value    - Radar site Latitude
 * \throw RadarCoordBadDataException  - if value passed if outsite [-90, +90] 
 */
	void setLatR( float value);
/*! 
 *\brief set radar longitude value 
 *\param value    - Radar site Longitude
 * \throw RadarCoordBadDataException  - if value passed if outsite [-180, +180] 
 */
	void setLonR( float value);
/*! 
 *\brief set radar height above msl value 
	 *\param value - Height above the msl of radar site (antenna tower not included)
 */
	void setHeightR( float value);
/*! 
 *\brief set beam electromagnetic focus height above surface value 
	 *\param value     - Height of the electric antenna focus related above the surface
 * \throw RadarCoordBadDataException  - if value passed if outsite [0, +100] 
 */
	void setAntennaTowerHeight( float value);

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
	 *\param[in] latr    - Radar site Latitude
	 *\param[in] lonr    - Radar site Longitude
	 *\param[in] heightr - Height above the msl of radar site (antenna tower not included)
	 *\param[in] aTH     - Height of the electric antenna focus related above the surface
	 */
	void setRadarCoord(float latr,float lonr,float heightr, float aTH) ;

private:
};

#endif

