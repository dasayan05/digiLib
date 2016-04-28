#include "digilib_logiccircuit.h"

bool digiLib::LogicCircuit::applyInputBits(BinaryInteger inpBitString)
{
	if(inps_Original.size()==inpBitString.length())
	{
		for(int x=(int)inps.size()-1;x>=0;x--)
			inpsBits.push_back(inpBitString(x));
		return true;
	}
	else
	{
		cout << "Number of INPUTBITs doesn't match"
			" the number of input nodes of the LogicCircuit" << endl;
		return false;
	}
}

digiLib::LogicCircuit::LogicCircuit()
{	nInpNodes = 0; nOutNodes = 0;		}

short int digiLib::LogicCircuit::totalInpNodes()
{	return this->nInpNodes;	}

short int digiLib::LogicCircuit::totalOutNodes()
{	return this->nOutNodes;	}

void digiLib::LogicCircuit::addInputNode(LogicGate& LG, short int pos)
{	inps.push_back(_getNodePtr(LG, pos, IN_NODE)); ++nInpNodes;
/* i/ps should be connected with i/ps of LCs */	}

void digiLib::LogicCircuit::addOutputNode(LogicGate& LG, short int pos)
{	outs.push_back(_getNodePtr(LG, pos, OUT_NODE));	++nOutNodes;
/* i/ps should be connected with i/ps of LCs */	}

void digiLib::LogicCircuit::_debug_memorymap()
{
	cout << "Inp connections" << endl;
	for(auto I : inps)
		cout << I << ",";
	cout << endl << "Out connections" << endl;
	for(auto I : outs)
		cout << I << ",";
	cout << endl;
}

void digiLib::LogicCircuit::printOutput()
{
	short int C = 0, D = 0;

	for(auto I : simOut)
	{
		cout << "Simulation Iteration : " << ++C << endl;
		for(auto J : I)
		{
			cout << "Output node : " << ++D << " -> " << J << endl;
		}
		D = 0;
	}
}

bool digiLib::LogicCircuit::getOutputFromNode(short int pos)
{	return (outs.at(pos-1)->getBitStatus()==HIGH)?true:false;		}

void digiLib::LogicCircuit::flushNodes()
{
	for(auto I : forFlush)
		I->flushBit();
}

vector<vector<bool>> digiLib::LogicCircuit::simulate(vector<BinaryInteger> pulses)
{
	inps_Original = inps;
	for(auto I : pulses)
	{
		inps = inps_Original;
		simulateOnce(I);
		flushNodes();
		simOut.push_back(singleSimOut);
	}
	return simOut;
}

void digiLib::LogicCircuit::simulateOnce(BinaryInteger inpBitString)
{
	if(!applyInputBits(inpBitString))
	{
		cout << "Exitting..." << endl;
		exit(0);
	}
	vector<LogicGate*> nextLayerGates;
	vector<bool> gateInvokeDone;
	for(int x=0;x<(int)inps.size();x++)
	{
		// apply the potentials
		if(inpsBits[x]==true)
			inps[x]->setBit();
		else
			inps[x]->clearBit();
	}

	// while : the layer iteration
	// --------------------------------
	while(!inps.empty())
	{
		nextLayerGates.clear();
		for(auto I : inps)
		{
			// get the parents of those Nodes
			if(!any_of(nextLayerGates.begin(), nextLayerGates.end(),
				[I](LogicGate* t){return t==I->getParent();}))
				nextLayerGates.push_back(I->getParent());
		}

		int nNextLayerGates = nextLayerGates.size();
		gateInvokeDone.clear();
		for(int x=0;x<nNextLayerGates;x++)
			gateInvokeDone.push_back(false);
		//cout << endl << "Next layer gate : " << nextLayerGates[0] << endl;

		vector<Node*> nextNodePtrs;
		vector<bool> nextNodeStatus;

		while(true)
			// to make sure all gates in a layer simulated
		{
			for(int x=0; x<nNextLayerGates; x++)
				// iterate all the gates
			{
				if((nextLayerGates[x]->isAllInpAvailable()) && (gateInvokeDone[x]==false))
				{
					nextLayerGates[x]->invokeLogic();
					gateInvokeDone[x] = true;
					// one logic gate has been activated
					// now need to collect the output nodes of those
					// gates to proceed with next layer simulation

					for(short int i=1; i<=nextLayerGates[x]->totalOutNodes(); i++)
					{
						Node* anOPNode = _getNodePtr(*nextLayerGates[x], i, OUT_NODE);

						if(!any_of(forFlush.begin(), forFlush.end(),
							[anOPNode](Node* n){return n==anOPNode;}))
							forFlush.push_back(anOPNode);

						vector<Node*> tVec = _getNodeConnectionPtr(
							*anOPNode);
						for(auto I : tVec)
						{
							nextNodePtrs.push_back(I);
							nextNodeStatus.push_back((I->getBitStatus()==HIGH)?true:false);
						}
					}
				}
			}
			if(all_of(gateInvokeDone.begin(), gateInvokeDone.end(), [](bool b){return b==true;}))
				break;
		}

		inps = nextNodePtrs;
		inpsBits = nextNodeStatus;
	}
	// simulation done

	singleSimOut.clear();
	for(auto I : outs)
		singleSimOut.push_back((I->getBitStatus()==HIGH)?true:false);
}

void digiLib::printSimulationOutput(vector<vector<bool>>& B)
{
	short int C = 0, D = 0;
	for(auto I : B)
	{
		cout << "Simulation Iteration : " << ++C << endl;
		for(auto J : I)
		{
			cout << "Output node " << ++D << " -> " << J << endl;
		}
		D = 0;
	}
}