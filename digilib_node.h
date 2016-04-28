#ifndef DIGILIB_NODE
#define DIGILIB_NODE

#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::to_string;

#include <algorithm>
#include <stdlib.h>
using std::any_of;

#define MAX_NODENAME_LEN 10
#define INV_NODESTATUS(x) ((x==HIGH)?LOW:HIGH)

namespace digiLib
{
	enum NodeStatus { LOW, HIGH, FLOATING = -1};

	class LogicGate;

	class Node
	{
	private:
		vector<Node*> connections;
		NodeStatus bit;
		LogicGate* parent;
	public:
		Node();
		void makeParent(LogicGate* parent);
		LogicGate* getParent();
		void connectNode(Node* C);
		void setBit();
		void clearBit();
		void flushBit();
		NodeStatus getBitStatus();
		void _debug();

		friend vector<Node*> _getNodeConnectionPtr(Node& n);
	};
}

#endif