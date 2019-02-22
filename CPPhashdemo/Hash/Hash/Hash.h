#ifndef HASH_H
#define HASH_H

#include<iostream>		// for input/output
#include<functional>	// for std hash
#include<cstdlib>		// for rand
#include<ctime>			// for time to seed rand

void ClearTable(int table[], int size);
int SecondHash(int x);

#endif
