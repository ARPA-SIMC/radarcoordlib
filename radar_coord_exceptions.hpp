/*! \file
 *  \brief Radar coord exceptions
 */
#ifndef __RADAR_COORD_EXCEPTIONS__
#define __RADAR_COORD_EXCEPTIONS__

#include <stdexcept>

/*!
 * \brief
 * Radar coord generic error
 * 
 * Every exception thrown by radar_coord library is a specialization of this exception
 */
class RadarCoordException : public std::logic_error
{
public:
	/*! 
	 * \brief Initialize the exception
	 * \param msg	the exception msg
	 */
	RadarCoordException(const std::string& msg)
	:std::logic_error(msg)
	{
	}
	virtual ~RadarCoordException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * RadarCoord unsupported feature error
 * 
 * Raised every time a feature is used with unsupported options.
 */
class RadarCoordUnsupportedException : public RadarCoordException
{
public:
	/*! 
	 * \brief Initialize the exception
	 * \param msg				the exception msg 
	 */
	RadarCoordUnsupportedException(const std::string& msg)
	:RadarCoordException("Unsupported operation error: " + msg)
	{
	}
	virtual ~RadarCoordUnsupportedException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * RadarCoord format error
 * 
 * Generic exception for situations where data is not compliant to specifications
 */
class RadarCoordFormatException : public RadarCoordException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	RadarCoordFormatException(const std::string& msg)
	:RadarCoordException(msg)
	{
	}
	virtual ~RadarCoordFormatException() throw()
	{
	}
};

/*===========================================================================*/
/*!
 * \brief
 * RadarCoord bad data value passed
 * 
 * Throw every time a value is not within specification
 */
class RadarCoordBadDataException : public RadarCoordFormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	RadarCoordBadDataException(const std::string& msg)
	:RadarCoordFormatException(msg)
	{
	}
	virtual ~RadarCoordBadDataException() throw()
	{
	}
};


/*!
 * \brief
 * RadarCoord unknown format error
 * 
 * Throw every time a HDF5 file has an unknown format
 * \n For example when "/Conventions" has an unexpected value
 */
class RadarCoordUnknownFormatException : public RadarCoordFormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	RadarCoordUnknownFormatException(const std::string& msg)
	:RadarCoordFormatException(msg)
	{
	}
	virtual ~RadarCoordUnknownFormatException() throw()
	{
	}
};

/*===========================================================================*/

/*===========================================================================*/

/*!
 * \brief
 * RadarCoord invalid attribute value error
 * 
 * Exception throwed when a attribute has an invalid value
 */
class RadarCoordInvalidAttributeValueException : public RadarCoordFormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of attribute with the invalid value
	 */
	RadarCoordInvalidAttributeValueException(const std::string& name)
	:RadarCoordFormatException("Attribute " + name + " has a invalid value")
	{
	}
	virtual ~RadarCoordInvalidAttributeValueException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * RadarCoord missing group error
 * 
 * Exception throwed when an Odim group (a dataset group, a data group etc.) is missing 
 */
class RadarCoordMissingGroupException : public RadarCoordFormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of the missing HDF5 group
	 */
	RadarCoordMissingGroupException(const std::string& name)
	:RadarCoordFormatException("HDF5 Group " + name + " not found")
	{
	}
	virtual ~RadarCoordMissingGroupException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * RadarCoord missing group error
 * 
 * Exception throwed when an dataset is missing 
 */
class RadarCoordMissingDatasetException : public RadarCoordFormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of the missing HDF5 dataset
	 */
	RadarCoordMissingDatasetException(const std::string& name)
	:RadarCoordFormatException("HDF5 dataset " + name + " not found")
	{
	}
	virtual ~RadarCoordMissingDatasetException() throw()
	{
	}
};

/*===========================================================================*/


/*===========================================================================*/


#endif
