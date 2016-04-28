#include "digilib_node.h"

digiLib::Node::Node()
{
	connections.clear();
	bit = NodeStatus::FLOATING;
	parent = nullptr;
	//nodeName = 0;
}

void digiLib::Node::makeParent(LogicGate* parent)
{	this->parent = parent;	}

digiLib::LogicGate* digiLib::Node::getParent()
{	return parent;		}

void digiLib::Node::connectNode(Node* C)
{
	if(!any_of(connections.begin(), connections.end(), [C](Node* n) {return n==C;}))
		connections.push_back(C);

	if(!any_of(C->connections.begin(), C->connections.end(), [this](Node* n) {return n==this;}))
		C->connectNode(this);
}

void digiLib::Node::setBit()
{	
	this->bit = HIGH;
	for(auto I : connections)
	{
		if(I->getBitStatus()!=HIGH)
			I->setBit();
	}
}

void digiLib::Node::clearBit()
{	
	this->bit = LOW;
	for(auto I : connections)
	{
		if(I->getBitStatus()!=LOW)
			I->clearBit();
	}
}

void digiLib::Node::flushBit()
{	
	this->bit = FLOATING;
	for(auto I : connections)
	{
		if(I->getBitStatus()!=FLOATING)
			I->flushBit();
	}
}

digiLib::NodeStatus digiLib::Node::getBitStatus()
{	return this->bit;		}

void digiLib::Node::_debug()
{
	for(auto I : this->connections)
		cout << I << ",";
	cout << endl;
}

vector<digiLib::Node*> digiLib::_getNodeConnectionPtr(Node& n)
{
	return n.connections;
}