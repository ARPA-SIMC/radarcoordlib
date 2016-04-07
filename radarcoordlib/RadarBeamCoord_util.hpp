/*!
 * \file
 * \brief Class to manage relationship between radar coordinates (Azimuth, elevation, range) and "pseudo-cilindric" coordinate on the a spherical Earth (azimuth, height, surface distance)
 */
#ifndef __RADAR_BEAM_COORD_UTIL__
#define __RADAR_BEAM_COORD_UTIL__

#include <math.h>

#define DEG2RAD(a) a*M_PI/180.     // degree to radiants
#define RAD2DEG(a) a*180.*M_1_PI   // radiants to degree
#define KeA(a)     4./3.* a        // WGS84 semimajor axis 

/*!
 * \brief Class to calculate elements related to radar coordinates.
 *
 * This class manage conversion between radar coordinates (Azimuth, elevation, range) and "pseudo-cilindric" coordinate on the a spherical Earth (azimuth, height, surface distance)
 *
 * This class compute calculation with radar coordinates\n
 * 
 */

class RadarBeamCoord_util {
  private:
   /*! EarthRadius */
   /*! Radius of Spherical earth (m) */
    float EarthRadius;
  public:
    /*!
     * \brief Constructor 
     * \param[in] ea - Earth radius (meter)
     */ 	
    RadarBeamCoord_util(float ea = 6378137.);
    ~RadarBeamCoord_util() {};

    /*!he
     * \brief Set private attribute EarthRadius used in some member functions
     * \param[in] ea - Earth radius (meter)
     */ 	
    void setEarthRadius (float ea) ;
    /*!
     * \brief Get the value tof private attribute EarthRadius.
     * \return ea - Earth radius used (meter)
     */ 	
    float getEarthRadius () ;

// funzioni che non considerano altezza radar

    /*!
     * \brief Calculate beam height (relative to radar height) as a funcion of elevation and surface distance
     * \param[in] elev         - Elevation of radar beam (Degree above horizon)
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \return Height of the center of the radar beam above the radar site level (m) 
     */ 	
    float elev_sd_2_beamHeight(float elev, float surfDistance);
    /*!
     * \brief Calculate beam height (relative to mean sea height) as a funcion of elevation and surface distance
     * \param[in] elev         - Elevation of radar beam (Degree above horizon)
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \param[in] alt_rad      - Height of the electromagnetic focus of the antenna above the msl
     * \return height of the center of the radar beam above the msl (m) 
     */ 	
    float elev_sd_2_beamHeight(float elev, float surfDistance, float alt_rad);


    /*!
     * \brief Calculate beam height (relative to radar height) as a funcion of elevation and ray-beam distance
     * \param[in] elev        - Elevation of radar beam (Degree above horizon)
     * \param[in] beamRange   - Slantwise distance alon the beam (m)
     * \return Height of the center of the radar beam above the radar site level (m) 
     */ 	
       float elev_br_2_beamHeight(float elev, float  beamRange);
    /*!
     * \brief Calculate beam height (relative to mean sea height) as a funcion of elevation and ray-beam distance
     * \param[in] elev        - Elevation of radar beam (Degree above horizon)
     * \param[in] beamRange   - Slantwise distance alon the beam (m)
     * \param[in] alt_rad     - Height of the electromagnetic focus of the antenna above the msl
     * \return height of the center of the radar beam above the msl (m) 
     */ 	
    float elev_br_2_beamHeight(float elev, float  beamRange, float alt_rad);


    /*!
     * \brief Calculate Surface Distance (on Earth surface) as a funcion of elevation, ray-beam distance and beam height (relative to radar height) 
     * \param[in] elev        - Elevation of radar beam (Degree above horizon)
     * \param[in] beamRange   - Slantwise distance alon the beam (m)
     * \param[in] beamHeight  - Height of the center of the radar beam above the radar site level (m)
     * \return Distance over the earth surface (m)
     */ 	
    float elev_br_bh_2_surfDistance    (float elev, float beamRange, float beamHeight);
    /*!
     * \brief Calculate Surface Distance (on Earth surface) as a funcion of elevation, ray-beam distance and beam height (relative to  mean sea height)
     * \param[in] elev        - Elevation of radar beam (Degree above horizon)
     * \param[in] beamRange   - Slantwise distance alon the beam (m)
     * \param[in] beamHeight  - Height above the msl of the center of the radar beam (m)
     * \param[in] alt_rad     - Height of the electromagnetic focus of the antenna above the msl
     * \return     -   Distance over the earth surface (m)
     */ 	
    float elev_br_bh_2_surfDistance    (float elev, float beamRange, float beamHeight, float alt_rad);


    /*!
     * \brief Calculate Surface Distance (on Earth surface) as a funcion of elevation and ray-beam distance.
     * \param[in] elev         - Elevation of radar beam (Degree above horizon)
     * \param[in] beamRange    - Slantwise distance alon the beam (m)
     * \return Distance over the earth surface (m)
     */ 	
    float elev_br_2_surfDistance    (float elev, float beamRange);


    /*!
     * \brief Calculate the distance over the ray beam as a funcion of elevation, surface distance (over Earth surface) and beam height (relative to radar height) 
     * \param[in] elev         - Elevation of radar beam (Degree above horizon)
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \param[in] beamHeight   - Height of the center of the radar beam above the radar site level (m)
     * \return Slantwise distance alon the beam (m)
     */ 	
    float elev_sd_bh_2_beamRange(float elev, float surfDistance, float beamHeight);
    /*!
     * \brief Calculate the distance over the ray beam as a funcion of elevation, surface distance (over Earth surface) and beam height (relative to mean sea height) 
     * \param[in] elev         - Elevation of radar beam (Degree above horizon)
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \param[in] beamHeight   - Height above the msl of the center of the radar beam (m)
     * \param[in] alt_rad      - Height of the electromagnetic focus of the antenna above the msl
     * \return  - Slantwise distance alon the beam (m)
     */ 	
    float elev_sd_bh_2_beamRange(float elev, float surfDistance, float beamHeight, float alt_rad);


    /*!
     * \brief Calculate the distance over the ray beam as a funcion of elevation and surface distance (over Earth surface)
     * \param[in] elev         - Elevation of radar beam (Degree above horizon)
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \return Slantwise distance alon the beam (m)
     */ 	
    float elev_sd_2_beamRange(float elev, float surfDistance);


    /*!
     * \brief Calculate elevation angle as a function of the distance over the ray beam and beam height (relative to radar height) 
     * \param[in] beamRange   - Slantwise distance alon the beam (m)
     * \param[in] beamHeight  - Height of the center of the radar beam above the radar site level (m)
     * \return Elevation of center of the radar beam (Degree above horizon)
     */ 	
    float br_bh_2_elev(float beamRange, float beamHeight);
    /*!
     * \brief Calculate elevation angle as a function of the distance over the ray beam and beam height (relative to mean sea height) 
     * \param[in] beamRange   - Slantwise distance alon the beam (m)
     * \param[in] beamHeight  - Height above the msl of the center of the radar beam (m)
     * \param[in] alt_rad     - Height of the electromagnetic focus of the antenna above the msl
     * \return - Elevation of center of the radar beam (Degree above horizon)
     */ 	
    float br_bh_2_elev(float beamRange, float beamHeight, float alt_rad);


    /*!
     * \brief Calculate elevation angle as a function of the distance over Earth surface and beam height (relative to radar height) 
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \param[in] beamHeight   - Height of the center of the radar beam above the radar site level (m)
     * \return Elevation of center of the radar beam (Degree above horizon)
     */ 	
    float ds_bh_2_elev(float surfDistance, float beamHeight);
    /*!
     * \brief Calculate elevation angle as a function of the distance over Earth surface and beam height (relative to mean sea height) 
     * \param[in] surfDistance - Distance over the earth surface (m)
     * \param[in] beamHeight   - Height above the msl of the center of the radar beam (m)
     * \param[in] alt_rad      - Height of the electromagnetic focus of the antenna above the msl
     * \return - Elevation of center of the radar beam (Degree above horizon)
     */ 	
    float ds_bh_2_elev(float surfDistance, float beamHeight, float alt_rad);
	
// duplico tutte le funzioni - qui considero anche l'altezza del radar

    //float elev_br_2_surfDistance    (float elev, float beamRange, float alt_rad);
    //float elev_sd_2_beamRange(float elev, float surfDistance, float alt_rad);

};


#endif
