#ifndef DIGILIB_MOREGATES
#define DIGILIB_MOREGATES

#include "digilib_logicgate.h"
using digiLib::LogicGate;

namespace digiLib
{
	class XOR : public LogicGate
	{
	public:
		XOR() : LogicGate(2,1)
		{	}
	protected:
		void logic()
		{
			NodeStatus I1 = getInpNodeStatus(1);
			NodeStatus I2 = getInpNodeStatus(2);
			if(I1==I2)
				setOutNodeStatus(1, LOW);
			else
				setOutNodeStatus(1, HIGH);
		}
	};

	class XNOR : public LogicGate
	{
	public:
		XNOR() : LogicGate(2,1)
		{	}
	protected:
		void logic()
		{
			NodeStatus I1 = getInpNodeStatus(1);
			NodeStatus I2 = getInpNodeStatus(2);
			if(I1==I2)
				setOutNodeStatus(1, HIGH);
			else
				setOutNodeStatus(1, LOW);
		}
	};
}

#endif