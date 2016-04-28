#include "digilib_binary.h"

void digiLib::BinaryInteger::truncZeros()
{
	while((!data.at(len-1)) && (len!=1))
	{
		this->data.pop_back();
		--len;
	}
}

void digiLib::BinaryInteger::bitAppend(unsigned short int bit)
{
	this->data.push_back(bit?true:false);
	++this->len;
}

void digiLib::BinaryInteger::makeLength(short int l)
{
	if(l>this->len)
	{
		short int extraBits = l-len;
		for(short int i=1; i<=extraBits; i++)
			(this->data.push_back(false), ++len);
	}
}

digiLib::BinaryInteger::BinaryInteger(char* num, bool truncZeroOn)
{
	len = 0;
	this->set(num, truncZeroOn); // autometic trunc of leading zeros
}

digiLib::BinaryInteger::BinaryInteger(Decimal num, bool truncZeroOn)
{
	len = 0;
	this->set(num, truncZeroOn); // autometic trunc of leading zeros
}

void digiLib::BinaryInteger::set(char* num, bool truncZeroOn)
{
	data.clear();
	len = 0;
	short int length = strlen(num);
	for(short int i=length-1; i>=0; i--)
		this->bitAppend((num[i]==48)?0:1);

	if(truncZeroOn)
		truncZeros();
}	/*	LSB -> vector[0]	MSB -> vector[end]	*/

void digiLib::BinaryInteger::set(Decimal num, bool truncZeroOn)
{
	data.clear();
	len = 0;
	unsigned int r;
	if(num == 0)
		(data.push_back(false), ++len);
	while(num!=0)
	{
		r = num%2;num = num/2;
		this->bitAppend(r);
	}
	

	if(truncZeroOn)
		truncZeros();
}

digiLib::BinaryInteger digiLib::BinaryInteger::allZero(short int len)
{
	char* binStr = new char[len+1];
	int x;
	for(x=0; x<len; x++)
		binStr[x] = '0';
	binStr[x] = '\0';
	return BinaryInteger(binStr, false);
}

digiLib::BinaryInteger digiLib::BinaryInteger::allOne(short int len)
{
	char* binStr = new char[len+1];
	int x;
	for(x=0; x<len; x++)
		binStr[x] = '1';
	binStr[x] = '\0';
	return BinaryInteger(binStr);
}

void digiLib::BinaryInteger::removeLeadingZeros()
{	truncZeros();	}

void digiLib::BinaryInteger::operator () (short int pos, unsigned short int bit)
{	this->data.at(pos) = bit?true:false;	}
// set specific bit

void digiLib::BinaryInteger::invertBit(short int pos)
{	this->operator()(pos, !this->operator()(pos));	}
/* inverts a specific bit */

void digiLib::BinaryInteger::onesComplement()
{
	for(short int p=0; p<len; p++)
		invertBit(p);
}

void digiLib::BinaryInteger::showBinaryInfo()
{
	cout << "Binary Representation : ";
	for(short int pos = this->len-1; pos>=0; pos--)
		cout << this->operator()(pos);
	cout << endl << "Decimal Representation : " << (int)(*this) << endl;
	cout << "Length() = " << length() << ",MSB = " << getMSB() << ",LSB = " << getLSB() << endl; 
	/* The bits are shown from MSB to LSB (left to right)
	for proper visual representation */
}

short int digiLib::BinaryInteger::length()
{	return this->len;	}

bool digiLib::BinaryInteger::operator () (short int pos) const
{
	try
	{	return this->data.at(pos);
	} catch(out_of_range e)
	{	cerr << e.what();
	return false;
	}
}

bool digiLib::BinaryInteger::operator == (digiLib::BinaryInteger B)
{
	if(this->length()!=B.length())
		return false;
	else
	{
		short int C = 0;
		for(short int x=0; x<this->length(); x++)
		{
			if(this->operator()(x)!=B(x))
				++C;
		}
		if(C>0)
			return false;
		else
			return true;
	}
}

bool digiLib::BinaryInteger::getMSB()
{	return this->operator() (MSB);		}

bool digiLib::BinaryInteger::getLSB()
{	return this->operator() (LSB);		}

digiLib::BinaryInteger::operator Decimal()
{
	Decimal dec = 0;
	for(short int x = this->len-1; x>=0 ; x--)
		dec += (int)this->operator()(x) * pow<int,int>(2,x);
	return dec;
}