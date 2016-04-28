#ifndef DIGILIB_LOGICCIRCUIT
#define DIGILIB_LOGICCIRCUIT

#include "digilib_node.h"
#include "digilib_logicgate.h"
#include "digilib_binary.h"
using digiLib::BinaryInteger;
using digiLib::Node;
using digiLib::LogicGate;
#include <vector>
#include <algorithm>
using std::all_of;
using std::vector;

#define INPUTDATA(x) BinaryInteger(x,false)

namespace digiLib
{
	class LogicCircuit
	{
	private:
		short int nInpNodes;
		short int nOutNodes;
		vector<Node*> inps;
		vector<Node*> inps_Original;
		vector<bool> inpsBits;
		vector<Node*> outs;
		vector<Node*> forFlush;
		vector<bool> singleSimOut;
		vector<vector<bool>> simOut;

		bool applyInputBits(BinaryInteger inpBitString);

	public:
		LogicCircuit();
		void addInputNode(LogicGate& LG, short int pos);
		void addOutputNode(LogicGate& LG, short int pos);
		short int totalInpNodes();
		short int totalOutNodes();
		void _debug_memorymap();
		void printOutput();
		bool getOutputFromNode(short int pos);
		void flushNodes();
		vector<vector<bool>> simulate(vector<BinaryInteger> pulses);
		void simulateOnce(BinaryInteger inpBitString);
	};

	void printSimulationOutput(vector<vector<bool>>& B);

	typedef vector<BinaryInteger> InputSignals;
	typedef vector<vector<bool>> SimulationOutput;
}

#endif