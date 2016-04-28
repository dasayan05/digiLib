#ifndef DIGILIB_BASICGATES
#define DIGILIB_BASICGATES

#include "digilib_logicgate.h"
using digiLib::LogicGate;

namespace digiLib
{
	template <short int i=2>
	class AND : public LogicGate
	{
	public:
		AND() : 
			LogicGate(i,1)
		{	}

	protected:
		void logic()
		{	// need to use input bits and generate output bit here
			NodeStatus N = NodeStatus::HIGH;
			for(int t=1; t<=i; t++)
			{
				if(getInpNodeStatus(t)==LOW)
				{
					N = NodeStatus::LOW;
					break;
				}
			}
			setOutNodeStatus(1, N);
		}
	};

	template <short int i=2>
	class OR : public LogicGate
	{
	public:
		OR() : 
			LogicGate(i,1)
		{	}

	protected:
		void logic()
		{
			// logic function
			NodeStatus N = NodeStatus::LOW;
			for(int t=1; t<=i; t++)
			{
				if(getInpNodeStatus(t)==HIGH)
				{
					N = NodeStatus::HIGH;
					break;
				}
			}
			setOutNodeStatus(1, N);
		}
	};

	class NOT : public LogicGate
	{
	public:
		NOT() : 
			LogicGate(1,1)
		{	}

	protected:
		void logic()
		{
			// main logic function
			NodeStatus I = getInpNodeStatus(1);
			if(I==HIGH)
				setOutNodeStatus(1, LOW);
			if(I==LOW)
				setOutNodeStatus(1, HIGH);
		}
	};

	template <short int i, short int o>
	class EmptyGate : public LogicGate
	{
	public:
		EmptyGate() : 
			LogicGate(i ,o)
		{}
	protected:
		void logic()
		{}
	};

	typedef AND<2> AND2;
	typedef AND<3> AND3;
	typedef OR<2> OR2;
	typedef OR<3> OR3;
}



#endif