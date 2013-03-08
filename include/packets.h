#ifndef _PACKETS_H
#define _PACKETS_H

#define MAX_PACKETSHEAD_NUM 200

typedef struct tagPACKETSHEAD
{
	int use;
	char decode[32];
    char encode[32];
}PACKETSHEAD;

void my_packets();

#endif