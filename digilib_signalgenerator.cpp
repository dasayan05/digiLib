#include "digilib_signalgenerator.h"

namespace SIG
{
	InputSignals theSig;
}

digiLib::SignalGenerator::SignalGenerator(void)
{}

InputSignals digiLib::SignalGenerator::generateAllCombinations(short int nInp, short int rep)
{
	int T = (int)pow<short int,short int>(2,nInp);
	for(int r = 1; r<=rep+1; r++)
	{
		for(int t = 0; t<T; t++)
		{
			BinaryInteger B(t, true);
			B.makeLength(nInp);
			SIG::theSig.push_back(B);
		}
	}
	return SIG::theSig;
}

InputSignals digiLib::SignalGenerator::generateCombination(short int nInp, int* combs, int combs_n, short int rep)
{
	for(int r = 1; r<=rep+1; r++)
	{
		for(int X = 0; X<combs_n; X++)
		{
			BinaryInteger B(combs[X], true);
			B.makeLength(nInp);
			SIG::theSig.push_back(B);
		}
	}
	return SIG::theSig;
}


digiLib::SignalGenerator::~SignalGenerator(void)
{
}
