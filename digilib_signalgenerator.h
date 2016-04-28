#pragma once

#include "digilib_binary.h"
using digiLib::BinaryInteger;
#include "digilib_logiccircuit.h"
using digiLib::InputSignals;

#define DIGILIB_INTARRAYLEN(x) (sizeof(x)/sizeof(int))

namespace digiLib
{
	class SignalGenerator
	{
	public:
		SignalGenerator(void);
		static InputSignals generateAllCombinations(short int nInp, short int rep = 0);
		static InputSignals generateCombination(short int nInp, int* combs, int combs_n, short int rep = 0);
		~SignalGenerator(void);
	};
}