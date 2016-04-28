#ifndef DIGILIB_SEQUENTIAL
#define DIGILIB_SEQUENTIAL

#include "digilib_logicgate.h"
using digiLib::LogicGate;

namespace digiLib
{
	class NORLatch : public LogicGate
	{
	private:
		NodeStatus memory;
	public:
		NORLatch() : 
			LogicGate(2,2)
		{	memory = LOW;	}
	protected:
		void logic()
		{
			NodeStatus I1 = getInpNodeStatus(1);
			NodeStatus I2 = getInpNodeStatus(2);
			if(I1==LOW && I2==HIGH)
			{
				setOutNodeStatus(1, HIGH);
				setOutNodeStatus(2, LOW);
				memory = HIGH;
			}
			else if(I1==HIGH && I2==LOW)
			{
				setOutNodeStatus(1, LOW);
				setOutNodeStatus(2, HIGH);
				memory = LOW;
			}
			else if(I1==LOW && I2==LOW)
			{
				setOutNodeStatus(1, memory);
				setOutNodeStatus(2, INV_NODESTATUS(memory));
			}
		}
	};

	class NANDLatch : public LogicGate
	{
	private:
		NodeStatus memory;
	public:
		NANDLatch() : 
			LogicGate(2,2)
		{	memory = LOW;	}
	protected:
		void logic()
		{
			NodeStatus I1 = getInpNodeStatus(1);
			NodeStatus I2 = getInpNodeStatus(2);
			if(I1==LOW && I2==HIGH)
			{
				setOutNodeStatus(1, LOW);
				setOutNodeStatus(2, HIGH);
				memory = HIGH;
			}
			else if(I1==HIGH && I2==LOW)
			{
				setOutNodeStatus(1, HIGH);
				setOutNodeStatus(2, LOW);
				memory = LOW;
			}
			else if(I1==HIGH && I2==HIGH)
			{
				setOutNodeStatus(1, memory);
				setOutNodeStatus(2, INV_NODESTATUS(memory));
			}
		}
	};
}

#endif