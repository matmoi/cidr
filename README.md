Cidr library                         {#mainpage}
============

IPv4 addresses
IPv4 ip address can be represented as an integer made up of 4 bytes. Here is an example of IPv4 addresses represented in both "doted decimal" format and in 4-byte format:
- 0xFFFFFFFF = 255.255.255.255
- 0xFF00FF01 = 255.0.255.1
- 0x10203040 = 16.32.48.64
- 0x00000000 = 0.0.0.0
 
CIDR range
-------------

An IPv4 CIDR range identifies an IPv4 network (i.e. collection of IPv4 addresses). A CIDR range consists of an IPv4 address and a 
suffix indicating how many bits of the address make up the network mask. The suffix can be from 0 to 32 bits. A CIDR range is written as: [IPv4 Address]/[prefix bit count]. For example:
- 192.168.0.1/22
- 128.148.128.40/32
- 168.0.0.0/0
- 10.61.128.218/27
 
Keep in mind that only the prefix of the IPv4 Address is Significant. That's why CIDR Range Has Multiple Representations Because the address bits which are not part of the prefix aren't relevant. For example, these representations are equivalent:
- 255.255.255.255/24
- 255.255.255.0/24
- 255.255.255.100/24
(i.e. the addresses are identical for the first 24 bits, although the last 8 bits differ)
 
Comparing CIDR ranges
-------------

Lets say we have two CIDR ranges A and B. Now, lets say we have LA and LB as prefix lengths for A and B respectively. Finally, say N = MIN (LA, LB). To determine if A is a subset of B, we have to determine if:
1. The prefix length of A is greater than B
2. The first N bits of the IPv4 addresses are the same. Similarly, we can easily derive if A is equal to B or, A is superset of B or, A is disjoint of B.
For example:
- "23.45.67.89/16" is EQUAL to "23.45.255.255/16" (the prefix lengths match and the prefixes match)
- "1.2.3.4/24" is SUBSET of "1.2.3.4/16" (the prefix lengths are different but prefixes match) "172.84.26.128/16" is SUPERSET of
- "172.84.26.255/24" (the prefix lengths are different but prefixes match)
- "197.54.16.128/25" is DISJOINT of "197.54.16.127/25" (the prefixes are different)
 
C-library cidr if for working with CIDR ranges that has 2 functions:
- creates a CIDR range from it's string representation
- compares two CIDR ranges as specified above

See doc for details.