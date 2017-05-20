/**
* \file cidr_app.c
* \brief Program to manipulate CIDR range addresses
* \author Matthieu Moinard
* \version 0.1
* \date May 21st 2017
*
*/

#include "cidr.h"
#include <stdlib.h>
#include <stdio.h>

/**
* \brief Print cmd line usage.
*/
void usage() {
    printf("cidr_app usage:\n");
    printf("cidr_app ADDR : indicate if ADDR is a valid cidr range of an ipv4 address (such as '192.168.1.1/8')\n");
    printf("cidr_app ADDR_1 ADDR_2 : indicate if ADDR_1 is equal to, subset/superset of or disjoint from ADDR_2\n");
}

/**
* \brief cidr_app cmd line program, entry function.
*
* \param argc Number of cmd line arguments, supports 2 (check CIDR range validity) or 3 (compare two CIDR ranges) arguments.
* \param argv Array of cmd line arguments.
* \return EXIT_SUCCESS if program runs successfully, EXIT_FAILURE otherwise.
* 
* cidr_app usage:
* cidr_app ADDR : indicate if ADDR is a valid cidr range of an ipv4 address (such as '192.168.1.1/8')
* cidr_app ADDR_1 ADDR_2 : indicate if ADDR_1 is equal to, subset/superset of or disjoint from ADDR_2
*/

int main(int argc, char *argv[])
{
    Cidr* addr1_ptr = NULL;
    Cidr* addr2_ptr = NULL;
    if (argc == 2)
    {
        if (cidr_ipv4_factory(&addr1_ptr, argv[1]) == CIDR_OK) {
            printf("'%s' is valid\n", argv[1]);
        }
        else
        {
            printf("'%s' is not valid\n", argv[1]);
            return EXIT_FAILURE;
        }
    }
    else if (argc == 3)
    {
        if (cidr_ipv4_factory(&addr1_ptr, argv[1]) != CIDR_OK) {
            printf("'%s' is not valid\n", argv[1]);
            return EXIT_FAILURE;
        }
        if (cidr_ipv4_factory(&addr2_ptr, argv[2]) != CIDR_OK) {
            printf("'%s' is not valid\n", argv[2]);
            return EXIT_FAILURE;
        }
        CIDR_CMP res = cidr_compare(addr1_ptr, addr2_ptr);
        switch (res) {
        case CIDR_EQUAL:
            printf("'%s' is EQUAL to '%s'\n", argv[1], argv[2]);
            break;
        case CIDR_SUBSET:
            printf("'%s' is a SUBSET of to '%s'\n", argv[1], argv[2]);
            break;
        case CIDR_SUPERSET:
            printf("'%s' is a SUPERSET of to '%s'\n", argv[1], argv[2]);
            break;
        case CIDR_DISJOINT:
            printf("'%s' is DISJOINT from '%s'\n", argv[1], argv[2]);
            break;
        default: // should never be here
            (void*)0;
        }
    }
    else {
        usage();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}