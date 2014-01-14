/*!
 * \file
 * \brief Namespace for generic utility used
 */
#ifndef __namespace_generic__
#define __namespace_generic__

#include <limits>
//#include <iostream>
using namespace std;

//#include <radar_coord_exceptions.hpp>

/*!
 * \brief Generic utility namespace
 */

namespace generic{
/*!
 * \brief Return the missing value used for private attribute 
 * (NaN if available or the maximum float supported)
 */
	float getMissing();

/*!
 * \brief Check if the float value passed is set to missing value
 * \return true is value is equal to missing
 */
	bool isMissing(float value);

/*!
 * \brief Check if longitude is a valid value.
 * \param[in] value - Longitude value to be controlled (degree E [-180., +180.])
 * \return true if longitude valide.
 */
	bool checkLongitude(float value);
 
/*!
 * \brief Check if latitude is a valid value.
 * \param[in] value - Latitude value to be controlled (degree N [-90., +90.])
 * \return true if latitude valide.
 */
	bool checkLatitude(float value);

/*!
 * \brief Check if Elevation is a valid value.
 * \param[in] value - Elevation value to be controlled (degree above horizon [-5., +90.])
 * \return true if Elevation valide.
 */
	bool checkElevation(float value);
/*!
 * \brief Check if BeamDistance is a valid value.
 * \param[in] value - BeamDistance value to be controlled (greater-equal 0.)
 * \return true if BeamDistance is valide.
 */
	bool checkBeamDistance (float value);
};
#endif
