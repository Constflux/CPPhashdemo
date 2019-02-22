// Jamison LeBreton
// 7/7/2017
// Week 5 Assignment CS425
// Dr. Masuck

#include "Hash.h"

using namespace std;

int main()
{
	const int iSize = 101;			// size of hash table (prime number)
	int iHashTable[iSize];			// array representing hash table
	ClearTable(iHashTable, iSize);	// initialize table
	int iSumLProbe = 0, iSumQProbe = 0, iSumDouble = 0;	// variables to hold total number of collisions
	int iInsertions = 0, iValue = 0;	// number of insertions to make and the value of the hash
	hash<int> standardHash;				// standard hash function for ints
	time_t tSeed = time(NULL);			// time variable so random function reproduces same numbers for all 3 attempts

	cout << "Hash table size is the prime number " << iSize << ".\n";
	cout << "This program computes the number of collisions from linear probing, quadratic probing, \n";
	cout << "and double hashing collision resolution";
	do {
		cout << "\nHow many randomly generated insertions would you like to make? ";
		cin >> iInsertions;
	} while ((iInsertions <= 0) || (iInsertions > iSize));
	
	/* Start Linear Probe
	For each insertion generate standard hash from random number and size to the hash table size
	if that value has not yet been used then mark as used, else increment by one until empty space
	is found. */
	srand(tSeed);
	for (int i = 0; i < iInsertions; i++)
	{
		iValue = ((standardHash(rand())) % iSize);
		if (iHashTable[iValue] == 0) iHashTable[iValue] = 1;
		else 
		{
			for (int j = 1; j < iSize; j++)
			{
				iSumLProbe += 1;
				if (iValue + j >= iSize) iValue -= iSize;
				if (iHashTable[(iValue + j)] == 0) 
				{
					iHashTable[(iValue + j)] = 1;
					break;
				}
			}
		}
	}

	/* Start Quadratic Probe
	For each insertion generate standard hash from random number and size to the hash table size
	if that value has not yet been used then mark as used, else increment by offset until empty
	space is found.  Offset is (2^x) and so is mutliplied by 2 each iteration */
	srand(tSeed);
	ClearTable(iHashTable, iSize);
	long int iOffset = 1;
	for (int i = 0; i < iInsertions; i++)
	{
		iValue = ((standardHash(rand())) % iSize);
		if (iHashTable[iValue] == 0) iHashTable[iValue] = 1;
		else
		{
			for (int j = 0; j < iSize; j++)
			{
				iSumQProbe += 1;
				while (iValue + iOffset >= iSize) { iValue -= iSize; }
				if (iHashTable[(iValue + iOffset)] == 0)
				{
					iHashTable[(iValue + iOffset)] = 1;
					break;
				}
				iOffset *= 2;
			}
		}
	}

	/* Start Double Hashing Probe
	For each insertion generate standard hash from random number and size to the hash table size
	if that value has not yet been used then mark as used, else generate an offset by running a 
	second hash and multiplying that by the number of iterations attempted.  Add offset until an
	empty spot is found  */
	srand(tSeed);
	ClearTable(iHashTable, iSize);
	iOffset = 0;
	for (int i = 0; i < iInsertions; i++)
	{
		iValue = ((standardHash(rand())) % iSize);
		if (iHashTable[iValue] == 0) iHashTable[iValue] = 1;
		else
		{
			for (int j = 1; j < iSize; j++)
			{
				iSumDouble += 1;
				iOffset = j * SecondHash(iValue);
				while (iValue + iOffset >= iSize) { iValue -= iSize; }
				if (iHashTable[(iValue + iOffset)] == 0)
				{
					iHashTable[(iValue + iOffset)] = 1;
					break;
				}
			}
		}
	}

	cout << "\nCollisions from linear probe resolution were:    " << iSumLProbe;
	cout << "\nCollisions from quadratic probe resolution were: " << iSumQProbe;
	cout << "\nCollisions from double hashing resolution were:  " << iSumDouble << "\n\n";

	cout << "Press any key to exit";
	system("pause");
	return 0;
}

// Function to clear array representing hash table
void ClearTable(int table[], int size)
{
	for (int i = 0; i < size; i++)
	{
		table[i] = 0;
	}
}

// Second hash function for double hashing collision resolution
int SecondHash(int x)
{
	return (23 - (x % 23));
}