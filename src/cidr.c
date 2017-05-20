/**
* \file cidr.c
* \brief cidr library
* \author Matthieu Moinard
* \version 0.1
* \date May 21st 2017
*
*/

#include "cidr.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

CIDR_RETVAL cidr_ipv4_factory(Cidr** cidr,const char* address)
{
    assert(address != NULL);    // address should'nt be null NULL

    const char* p_char = address;
    address_t ip = 0x0;        //hex representation of an ipv4 address
    uint32_t cidr_range = 0x0; //cidr range of an ipv4 address (C in '0.0.0.0/C')
    mask_t mask = 0x0;         //bitmask from cidr range
    uint32_t dec;              // ipv4 decimal corresponding to dot-decimal notation (one of the X in 'X.X.X.X/0')
    uint32_t dec_length;       // length of a ipv4 decimal representation (shouldn't exceed 3 digits)
    int32_t  dec_counter;      // ipv4 decimal counter in range [0,4[

    // Extract ip
    for (dec_counter = 3; dec_counter >= 0; dec_counter--)
    {
        if (*p_char == '\0') return CIDR_INVALID_FORMAT;    // rest of address shouldn't be empty at this stage
        if (! isdigit(*p_char)) return CIDR_INVALID_FORMAT; // next decimal number should have at least one digit

        for (dec_length = 1; isdigit(p_char[dec_length++]););

        if (!(dec_counter > 0 && p_char[dec_length - 1] == '.') &&
            !(dec_counter == 0 && p_char[dec_length - 1] == '/')) // ip decimals must be separated by '.', and last must end by '/'
            return CIDR_INVALID_FORMAT;

        errno = 0;
        dec = (uint32_t) strtoul(p_char, NULL, 10);
        if(errno != 0) return CIDR_INVALID_FORMAT; // check number overflow/underflow
        if(dec > 0xff) return CIDR_INVALID_FORMAT; // decimal shouldn't exceed 255 in ipv4 representation

        ip |= (dec << (dec_counter << 3));

        p_char += dec_length;
    }

    // Extract CIDR range
    if (*p_char == '\0') return CIDR_INVALID_FORMAT;    // rest of address shouldn't be empty
    if (! isdigit(*p_char)) return CIDR_INVALID_FORMAT; // cidr should contain at least one digit

    for (dec_length = 1; isdigit(p_char[dec_length]); dec_length++);

    if(p_char[dec_length] != '\0') return CIDR_INVALID_FORMAT; // reach the end of ipv4 representation
    errno = 0;

    cidr_range = (mask_t) strtoul(p_char, NULL, 10);

    if (errno != 0) return CIDR_INVALID_FORMAT;      // check number overflow/underflow
    if (cidr_range > 32) return CIDR_INVALID_FORMAT; // cidr range can't exceed 32

    mask = (mask_t) ((uint64_t) ~0 << (32 - cidr_range));

    // Create CIDR
    cidr_destructor(cidr);
    *cidr = (Cidr*) malloc(sizeof(Cidr));
    (*cidr)->ip = ip;
    (*cidr)->mask = mask;

    return CIDR_OK;
}

CIDR_RETVAL cidr_destructor(Cidr** cidr)
{
    if (*cidr != NULL)
    {
        free(*cidr);
        *cidr = NULL;
    }
    return CIDR_OK;
}

CIDR_CMP cidr_compare(const Cidr* cidr, const Cidr* cidr_ref)
{
    assert(cidr != NULL);
    assert(cidr_ref != NULL);

    CIDR_CMP ret = CIDR_DISJOINT;
    
    if (cidr->mask == cidr_ref->mask)
    {
        if ((cidr->ip & cidr->mask) == (cidr_ref->ip & cidr->mask))
        {
            ret = CIDR_EQUAL;
        }
    }
    else if (cidr->mask > cidr_ref->mask)
    {
        if ((cidr->ip & cidr_ref->mask) == (cidr_ref->ip & cidr_ref->mask))
        {
            ret = CIDR_SUBSET;
        }
    }
    else // cidr->mask < cidr_ref->mask
    {
        if ((cidr->ip & cidr->mask) == (cidr_ref->ip & cidr->mask))
        {
            ret = CIDR_SUPERSET;
        }
    }
    return ret;
}