#include "digilib_truthtable.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios_base;


digiLib::TruthTable::TruthTable(vector<BinaryInteger> in,vector<vector<bool>> out)
{
	if(in.size()==out.size())
	{
		this->inps = in;
		this->outs = out;
	}
}

void digiLib::TruthTable::showTable()
{
	short int C = 0;
	for(auto I : inps)
	{
		for(short int pos = I.length()-1; pos>=0; pos--)
			cout << I(pos) << " ";
		cout << "-> ";
		for(auto I : outs.at(C))
		{
			cout << I << " ";
		}
		++C;
		cout << endl;
	}
}

short int digiLib::TruthTable::totalInpNodes()
{	return inps.at(0).length();	}

short int digiLib::TruthTable::totalOutNodes()
{	return outs.at(0).size();	}


vector<bool> digiLib::TruthTable::getCorrespondingOutput(BinaryInteger B)
{
	for(unsigned int x=0; x<inps.size(); x++)
	{
		if(inps.at(x)==B)
			return outs.at(x);
	}
	(cout << "Doesn;t match any of the input combinations in the Truthtable" << endl, exit(0));
}

digiLib::TruthTable::~TruthTable(void)
{
}
