#ifndef DIGILIB_TRUTHTABLE
#define DIGILIB_TRUTHTABLE

#include "digilib_binary.h"
using digiLib::BinaryInteger;

namespace digiLib
{
	class TruthTable
	{
	private:
		vector<BinaryInteger> inps;
		vector<vector<bool>> outs;
	public:
		TruthTable(vector<BinaryInteger> ,vector<vector<bool>>);
		vector<bool> getCorrespondingOutput(BinaryInteger);
		short int totalInpNodes();
		short int totalOutNodes();
		void showTable();
		~TruthTable(void);
	};
}
#endif