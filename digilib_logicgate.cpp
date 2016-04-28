#include "digilib_logicgate.h"

digiLib::LogicGate::LogicGate()
{
	nInpNodes = 0; nOutNodes = 0;
	tTable = nullptr;
}

digiLib::LogicGate::LogicGate(short int inode, short int onode)
{
	nInpNodes = 0; nOutNodes = 0;
	addInputNode(inode);
	addOutputNode(onode);
	tTable = nullptr;
}

void digiLib::LogicGate::addInputNode(short int nodeNumber)
{
	for(int n = 1; n<=nodeNumber; n++)
	{
		Node N;
		++nInpNodes;
		N.makeParent(this);
		inpNodes.push_back(N);
	}
}

void digiLib::LogicGate::addOutputNode(short int nodeNumber)
{
	for(int n = 1; n<=nodeNumber; n++)
	{
		Node N;
		++nOutNodes;
		N.makeParent(this);
		outNodes.push_back(N);
	}
}

short int digiLib::LogicGate::totalInpNodes()
{	return this->nInpNodes;		}

short int digiLib::LogicGate::totalOutNodes()
{	return this->nOutNodes;		}

digiLib::Node* digiLib::LogicGate::getInpNode(short int n)
{
	try
	{	return &this->inpNodes.at(n-1);
	}catch(out_of_range e)
	{	cout << e.what();
	return (new Node());	}
}

digiLib::Node* digiLib::LogicGate::getOutNode(short int n)
{	
	try
	{	return &this->outNodes.at(n-1);
	}catch(out_of_range e)
	{	cout << e.what();
	return (new Node());	}
}

void digiLib::LogicGate::_debug_memorymap()
{
	cout << "address : " << this << endl;
	cout << "--INPUT--" << endl;
	for(short int x=0;x<totalInpNodes();x++)
	{
		cout << "Node " << x+1 << ": " << &inpNodes[x] << " Status : " << 
			inpNodes[x].getBitStatus() << " parent : " << inpNodes[x].getParent() << endl;
		inpNodes[x]._debug();
	}
	cout << "--OUTPUT--" << endl;
	for(short int x=0;x<totalOutNodes();x++)
	{
		cout << "Node " << x+1 << ": " << &outNodes[x] << " Status : " << 
			outNodes[x].getBitStatus() << " parent : " << outNodes[x].getParent() << endl;
		outNodes[x]._debug();
	}
}

bool digiLib::LogicGate::invokeLogic()
{	
	if(tTable==nullptr)
		this->logic();
	else
		this->TTLogic();
	bool logicError = false;
	for(auto I : outNodes)
	{
		if(I.getBitStatus()==NodeStatus::FLOATING)
			logicError = true;
	}
	if(logicError)
		return false;
	else
		return true;
}


void digiLib::LogicGate::setTruthTable(TruthTable& T)
{
	tTable = &T;
}


void digiLib::LogicGate::TTLogic()
{
	if(tTable->totalInpNodes()!=this->totalInpNodes() || tTable->totalOutNodes()!=this->totalOutNodes())
		(cout << "Number of nodes mismatch" << endl, exit(0));
	else
	{
		string binStr;
		for(short int x=1; x<=this->totalInpNodes(); x++)
			binStr += ((getInpNodeStatus(x)==HIGH)?"1":"0");
		char* binaryStr = (char*)binStr.c_str();
		vector<bool> actualOp = tTable->getCorrespondingOutput(BinaryInteger(binaryStr,false));
		if(this->totalOutNodes()==actualOp.size())
		{
			for(short int x=1; x<=this->totalOutNodes(); x++)
				setOutNodeStatus(x, ((actualOp.at(x-1)==true)?HIGH:LOW));
		}
		else
			(cout << "Number of nodes mismatch" << endl, exit(0));
	}
}

bool digiLib::LogicGate::isAllInpAvailable()
{
	bool yesno = true;
	for(auto I : inpNodes)
	{
		if(I.getBitStatus()==FLOATING)
			yesno = false;
	}
	return yesno;
}

void digiLib::LogicGate::setInpNodeStatus(short int pos, digiLib::NodeStatus stat)
{
	if(stat==HIGH)
		this->inpNodes.at(pos-1).setBit();
	if(stat==LOW)
		this->inpNodes.at(pos-1).clearBit();
}

digiLib::NodeStatus digiLib::LogicGate::getOutNodeStatus(short int pos)
{
	return this->outNodes.at(pos-1).getBitStatus();
}

digiLib::NodeStatus digiLib::LogicGate::getInpNodeStatus(short int pos /* obviously IN_NODE */)
{	return this->inpNodes.at(pos-1).getBitStatus();		}

void digiLib::LogicGate::setOutNodeStatus(short int pos /* obviously IN_NODE */, digiLib::NodeStatus stat)
{	
	if(stat==HIGH)
		this->outNodes.at(pos-1).setBit();
	if(stat==LOW)
		this->outNodes.at(pos-1).clearBit();
}

bool digiLib::nodeConnect(LogicGate& fromLG, short int fromPos, NodeType fromType, 
						  LogicGate& toLG, short int toPos, NodeType toType)
{
	if(fromType!=toType)
	{
		if(fromType==OUT_NODE && toType==IN_NODE)
			fromLG.getOutNode(fromPos)->connectNode(toLG.getInpNode(toPos));
		if(fromType==IN_NODE && toType==OUT_NODE)
			fromLG.getInpNode(fromPos)->connectNode(toLG.getOutNode(toPos));
		return true;
	}
	else
	{
		cerr << "Invalid node connection type..." << endl;
		return false;
	}
}

void digiLib::nodeStatusChange(LogicGate& LG, short int pos, NodeType type, NodeStatus b)
{
	if(type==OUT_NODE)
	{
		if(b==HIGH)
			LG.getOutNode(pos)->setBit();
		else
			LG.getOutNode(pos)->clearBit();
	}
	else
	{
		if(b==HIGH)
			LG.getInpNode(pos)->setBit();
		else
			LG.getInpNode(pos)->clearBit();
	}
}

digiLib::Node* digiLib::_getNodePtr(LogicGate& LG, short int pos, NodeType type)
{
	if(type==IN_NODE)
		return LG.getInpNode(pos);
	else
		return LG.getOutNode(pos);
}