/**
* \file cidr.h
* \brief cidr library header file
* \author Matthieu Moinard
* \version 0.1
* \date May 21st 2017
*
* \mainpage C-library to manipulate ipv4 addresses and CIDR ranges
*/

#include <stdint.h>

/** 8-bytes hexadecimal representation of an ipv4 address. For instance, 255.255.255.0 is represented as 0xffffff00. */
typedef uint32_t address_t;
/** Bitmask for most relevant bits of an ipv4 address regarding its CIDR range.*/
typedef address_t mask_t;
    
/**
* returned value for Cidr creation and destruction.
*/
typedef enum CIDR_RETVAL
{
    CIDR_OK = 0,        /**< Operation ends successfully. */
    CIDR_INVALID_FORMAT /**< Error during address parsing. */
} CIDR_RETVAL;

/**
* Returned value for cidr range comparison. { CIDR_DISJOINT, CIDR_EQUAL, CIDR_SUBSET, CIDR_SUPERSET}
*/
typedef enum CIDR_CMP
{
    CIDR_DISJOINT = 0, /**< Addresses are disjoint (CIDR prefixes are different) */
    CIDR_EQUAL,        /**< Addresses are equal (CIDR prefixes of same size are equal) */
    CIDR_SUBSET,       /**< First address is a subset of the second */
    CIDR_SUPERSET      /**< First address is a superset of the second */
} CIDR_CMP;

/**
* C struct to manipulate ipv4 addresses and its CIDR range.
*/
typedef struct Cidr
{
    /** 8-bytes hex representation of an ipv4 address */
    address_t ip;
    /** bitmask to determine CIDR range */
    mask_t mask;
} Cidr;

/**
* Instantiate a Cidr struct based on its ipv4 numerical dot-decimal representation, such as "255.255.255.255/8".
* \param cidr double pointer to the struct to instantiate.
* \param address dot-decimal ipv4 representation
* \return CIDR_OK if instantiation is ok, CIDR_INVALID_FORMAT otherwise
*/
CIDR_RETVAL cidr_ipv4_factory(Cidr** cidr, const char* address);

/**
* Free memory of a Cidr struct.
* \param cidr double pointer to the struct to destroy.
* \return CIDR_OK if destruction is ok, CIDR_INVALID_FORMAT otherwise
*/
CIDR_RETVAL cidr_destructor(Cidr** cidr);

/**
* Compare two Cidr structs.
* \param cidr First ipv4 address with its CIDR range
* \param cidr_ref Second ipv4 address used as the reference
* \return CIDR_EQUAL if both addresses have strictly same CIDR range, CIDR_SUBSET if cidr is a subset of cidr_ref, CIDR_SUPERSET id cidr is a superset of cidr_ref, CIDR_DISJOINT otherwise.
*/
CIDR_CMP cidr_compare(const Cidr* cidr, const Cidr* cidr_ref);
