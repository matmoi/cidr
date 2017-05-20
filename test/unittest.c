/**
* \file unittest.c
* \brief Unittest program for cidr library
* \author Matthieu Moinard
* \version 0.1
* \date May 21st 2017
*
*/

#include "cidr.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
* \brief Entry point to run unittest on cidr library. Trigger asserts in case of test failure.
* \return EXIT_SUCCESS
*/

int main(int argc, char *argv[])
{
    Cidr* addr_ptr = NULL;
    Cidr* addr2_ptr = NULL;
    Cidr  addr;

    // 1 // test cidr_ipv4_factory parsing function.
    // addr and addr_ptr should be strictly equal
    printf("[test 1.2] parsing '255.255.255.255/24'\n");
    assert(cidr_ipv4_factory(&addr_ptr,"255.255.255.255/24") == CIDR_OK);
    addr = (Cidr) { .ip = 0xffffffff, .mask = 0xffffff00 };
    assert(addr.ip == addr_ptr->ip && addr.mask == addr_ptr->mask);

    printf("[test 1.2] parsing '255.0.255.1/16'\n");
    assert(cidr_ipv4_factory(&addr_ptr, "255.0.255.1/16") == CIDR_OK);
    addr = (Cidr) { .ip = 0xff00ff01, .mask = 0xffff0000 };
    assert(addr.ip == addr_ptr->ip && addr.mask == addr_ptr->mask);

    printf("[test 1.3] parsing '16.32.48.64/8'\n");
    assert(cidr_ipv4_factory(&addr_ptr, "16.32.48.64/8") == CIDR_OK);
    addr = (Cidr) { .ip = 0x10203040, .mask = 0xff000000 };
    assert(addr.ip == addr_ptr->ip && addr.mask == addr_ptr->mask);

    printf("[test 1.4] parsing '0.0.0.0/0'\n");
    assert(cidr_ipv4_factory(&addr_ptr, "0.0.0.0/0") == CIDR_OK);
    addr = (Cidr) { .ip = 0x00000000, .mask = 0x00000000 };
    assert(addr.ip == addr_ptr->ip && addr.mask == addr_ptr->mask);

    printf("\n");

    // 2 // test cidr_compare function
    printf("[test 2.1] '23.45.67.89/16' compared to '23.45.255.255/16' (expect EQUAL)\n");
    assert(cidr_ipv4_factory(&addr_ptr, "23.45.67.89/16") == CIDR_OK);
    assert(cidr_ipv4_factory(&addr2_ptr, "23.45.255.255/16") == CIDR_OK);
    assert(cidr_compare(addr_ptr, addr2_ptr) == CIDR_EQUAL);

    printf("[test 2.2] '1.2.3.4/24' compared to '1.2.3.4/16' (expect SUBSET)\n");
    assert(cidr_ipv4_factory(&addr_ptr, "1.2.3.4/24") == CIDR_OK);
    assert(cidr_ipv4_factory(&addr2_ptr, "1.2.3.4/16") == CIDR_OK);
    assert(cidr_compare(addr_ptr, addr2_ptr) == CIDR_SUBSET);

    printf("[test 2.3] '172.84.26.128/16' compared to '172.84.26.255/24' (expect SUPERSET)\n");
    assert(cidr_ipv4_factory(&addr_ptr, "172.84.26.128/16") == CIDR_OK);
    assert(cidr_ipv4_factory(&addr2_ptr, "172.84.26.255/24") == CIDR_OK);
    assert(cidr_compare(addr_ptr, addr2_ptr) == CIDR_SUPERSET);

    printf("[test 2.4] '197.54.16.128/25' compared to '197.54.16.127/25' (expect DISJOINT)\n");
    assert(cidr_ipv4_factory(&addr_ptr, "197.54.16.128/25") == CIDR_OK);
    assert(cidr_ipv4_factory(&addr2_ptr, "197.54.16.127/25") == CIDR_OK);
    assert(cidr_compare(addr_ptr, addr2_ptr) == CIDR_DISJOINT);

    printf("\n");

    cidr_destructor(&addr_ptr);
    cidr_destructor(&addr2_ptr);

    return EXIT_SUCCESS;
}