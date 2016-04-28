#ifndef DIGILIB_BINARY
#define DIGILIB_BINARY

#include <iostream>
using std::cout;	// For Debug
using std::endl;	// For Debug
using std::cerr;
#include <cmath>
using std::pow;

#include <exception>
using std::out_of_range;

#include <vector>
using std::vector;

#define MSB length()-1
#define LSB 0

typedef int Decimal;

namespace digiLib
{
	class BinaryInteger
	{
	private:
		vector<bool> data;
		/* The main binary data in
		the form of vector<bool> */
		short int len;
		void truncZeros();
		/* Truncs leading zeros */

		void bitAppend(unsigned short int bit);
		/* Internally appends each bit one by one */

	public:

		BinaryInteger(char* num, bool truncZeroOn = true);
		/* Init with binary string */

		BinaryInteger(Decimal num, bool truncZeroOn = true);
		/* Init with decimal number */
	private:
		void set(char* num, bool truncZeroOn = true);
		/*	LSB -> vector[0]	MSB -> vector[end]	*/

		void set(Decimal num, bool truncZeroOn = true);
		/*	LSB -> vector[0]	MSB -> vector[end]	*/

	public:
		// Pre-built BinaryInteger
		static BinaryInteger allZero(short int len);
		static BinaryInteger allOne(short int len);
		// Pre-built BinaryInteger

		void removeLeadingZeros();
		/* in case of any manual changes to the data (i.e. not using ctor or set function),
		this function needs to be invoked explicitly */

		void makeLength(short int l);
		// makes the length of the string as 'l' by padding zeroes

		void operator () (short int pos, unsigned short int bit);
		// set specific bit

		bool operator == (BinaryInteger);

		void invertBit(short int pos);
		/* inverts a specific bit */

		void onesComplement();

		void showBinaryInfo();

		short int length();
		/* length of binary string = length of this->data */

		bool operator () (short int pos) const;
		/* get the i-th bit with 0 being the LSB and 'length()-1' being the MSB.
		Also shows error message if index out of bound, i.e. pos>=length()*/

		bool getMSB();
		/* A special form of operator() to access the MSB */

		bool getLSB();
		/* A special form of operator() to access the LSB */

		operator Decimal();
		/* casting to int, i.e. to Decimal */
	};
}

#endif