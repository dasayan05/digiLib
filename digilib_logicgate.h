#ifndef DIGILIB_LOGICGATE
#define DIGILIB_LOGICGATE

#include <vector>
#include <exception>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::out_of_range;


#include "digilib_node.h"
#include "digilib_truthtable.h"

namespace digiLib
{
	enum NodeType { IN_NODE, OUT_NODE};
	
	class LogicGate
	{
	private:
		short int nInpNodes;
		short int nOutNodes;
		vector<Node> inpNodes;
		vector<Node> outNodes;
		TruthTable* tTable;
	public:
		LogicGate();
		LogicGate(short int inode, short int onode);

	private:
		void addInputNode(short int nodeNumber = 1);

		void addOutputNode(short int nodeNumber = 1);
	public:
		short int totalInpNodes();
		short int totalOutNodes();

	private:
		Node* getInpNode(short int n);
		Node* getOutNode(short int n);
	public:
		
		friend bool nodeConnect(LogicGate& fromLG, short int fromPos, NodeType fromType, 
			LogicGate& toLG, short int toPos, NodeType toType);
		friend void nodeStatusChange(LogicGate& LG, short int pos, NodeType type, NodeStatus b);
		friend Node* _getNodePtr(LogicGate& LG, short int pos, NodeType type);
		

		void _debug_memorymap();
		bool invokeLogic();
		void TTLogic();
		void setTruthTable(TruthTable&);
		bool isAllInpAvailable();

		/* DEBUG */

		void setInpNodeStatus(short int pos, NodeStatus stat);

		NodeStatus getOutNodeStatus(short int pos);

		/* DEBUG */

	protected:
		virtual void logic() = NULL;
		/* need to overwrite logic() function for specific gate logic */

		NodeStatus getInpNodeStatus(short int pos /* obviously IN_NODE */);

		void setOutNodeStatus(short int pos /* obviously IN_NODE */, NodeStatus stat);
	};
}

#endif