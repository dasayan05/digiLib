# digiLib
A Digital Electronics Library for C++

'digiLib' is a tiny library written in C++ for modelling & simulating small scale digital electronics circuit. This library is written by A.Das for hobby purpose. With 'digiLib', digital logic circuits can be made efficiently with plenty of extra features like Truthtable generation etc. The library is actually made to model 'Combinational' logic circuits only. But with some tricks (explained later), one can model sequential circuits also. The library also provides pre-built classes for sequential circuits too for ease of use. Apart from that, the library provides fully abstracted classes for easier control. The beauty of the library is that the classes are extremely easy to use and generalized upto a great extent.

System specification:

The library is written in MSVC 2012 and works only with MSVC compilers. In future, I hope this library will be available for all other platforms and compilers with more features.

'digiLib' - An Overview:
-----------------------

'digiLib' library is distributed over several source files. There are total 4 Classes for users, namely :

1. BinaryInteger - A Class that represents a binary integer.
2. LogicGate - The main component of the library and a representative Class of not only a Logic gate but also any logic unit/block.
3. LogicCircuit - The wrapper for an entire logic circuit. It is primarily required for simulation only.
4. TruthTable - A Class that represents a Truth table (More on this class later).

NOTE: There are several more classes but they are for internal uses only.

'digiLib' - A Description:
-------------------------

1. 'BinaryInteger' Class:
-------------------------

[This simply represents a binary integer number. One can construct a binary integer from a Decimal number or a binary string (Char*).]

1.a. BinaryInteger(char* num, bool truncZeroOn = true) -> The constructor for BinaryInteger from a binary string. 'truncZeroOn' specifies wheather to truncate leading zeros or not.

1.b. BinaryInteger(Decimal num, bool truncZeroOn = true) -> The constructor for BinaryInteger from a Decimal(int) number. 'truncZeroOn' specifies wheather to truncate leading zeros or not.

2. void removeLeadingZeros() -> Remove leading zeros in the BinrayInteger manually.

3. void makeLength(short int len) -> Makes the length of the string as 'len' by padding zeros.

4. void operator () (short int pos, unsigned short int bit) -> Set specific bit 'pos' as 'bit'.

5. bool operator == (BinaryInteger) -> Checkes wheather two 'BinaryInteger's represents the same number or not.

6. void invertBit(short int pos) -> Inverts a specific bit.

7. void onesComplement() -> Computes 1's complement.

8. void showBinaryInfo() -> Shows the infos of the BinaryInteger object(For debugging purpose only).

9. short int length() -> Length of binary string.

10. bool operator () (short int pos) const -> get the 'pos'-th bit.

11. bool getMSB() -> A special form of operator() to access the MSB.

12. bool getLSB() -> A special form of operator() to access the LSB.

13. operator Decimal() -> Casting to Decimal, i.e. to int.

2. 'LogicGate' Class:
---------------------

[This abstract class represents a logic unit/block. The simplest usage of this class is being a Logic Gate]

1.a. LogicGate() -> void constructor.

1.b. LogicGate(short int inode, short int onode) -> Constructs an logic unit/block with 'inode' numbers of input nodes and 'onode' numbers of output nodes.

2. short int totalInpNodes() -> Total number of Input nodes.

3. short int totalOutNodes() -> Total number of Input nodes.

4. bool invokeLogic() -> A main function for invoking the logic of the logic unit/block using logic() function (See the tutorial) , i.e. activating the LogicGate for generating output.

5. void TTLogic() -> A main function for invoking the logic of the logic unit/block using a TruthTable object.

6. void setTruthTable(TruthTable&) -> Set a truth table as the logic of the LogicGate.

7. bool isAllInpAvailable() -> Returns true when all inputs of the LogicGate are given.

3. 'LogicCircuit' Class:
------------------------

[LogicCircuit is an abstract view of a circuit. Simply, users need to wrap the entire circuit with a LogicCircuit for simulation purpose only. See the tutorials for details.]

1. LogicCircuit() -> Makes an abstract empty Logic circuit.

2. void addInputNode(LogicGate& LG, short int pos) -> Defines and input node of the Logic circuit.

3. void addOutputNode(LogicGate& LG, short int pos) -> Defines and output node of the Logic circuit.

4. short int totalInpNodes() -> Total number of input nodes.

5. short int totalOutNodes() -> Total number of output nodes.

6. void printOutput() -> Prints the simulation output in console.

7. bool getOutputFromNode(short int pos) -> Collect the output from a specific node after simulation.

8. vector<vector<bool>> simulate(vector<BinaryInteger> pulses) -> Simulate the circuit with pulses.size() iterations. In each iteration, the inputs to all the input nodes will be one bit from the corresponding BinaryInteger with MSB being the input bit for 1st input node and LSB being the input bit for last input node.
(See tutorial for detailed description).

4. 'TruthTable' Class:
----------------------

[Represents a Truth table.]

1. TruthTable(vector<BinaryInteger> ,vector<vector<bool>>) -> Make a truth table from the inputs to a circuit and the simulation outputs.

2. vector<bool> getCorrespondingOutput(BinaryInteger) -> Get corresponding output of all the output nodes for a given input combination.

3. short int totalInpNodes() -> Total number of Input nodes.

4. short int totalOutNodes() -> Total number of Output nodes.

5. void showTable() -> Shows the truth table in console.

5. Other functions:
-------------------

1. bool nodeConnect(LogicGate& fromLG, short int fromPos, NodeType fromType, LogicGate& toLG, short int toPos, NodeType toType) -> Connects node of one LogicGate to a node of another LogicGate.

2. void nodeStatusChange(LogicGate& LG, short int pos, NodeType type, NodeStatus b) -> Change a node status (HIGH or LOW).

3. NodeStatus getInpNodeStatus(short int pos) -> Get the status of 'pos'th input node of the LogicGate. This is a protected function and can only be called from a derived class of LogicGate.

4. void setOutNodeStatus(short int pos, NodeStatus stat) -> Set the status of 'pos'th output node to 'stat'.

6. Enums, macros & typedefs:
----------------------------

1. 'NodeStatus' enum -> It simply contains HIGH(1), LOW(0) & FLOATING(-1) which are nothing but voltage representations in any node.

2. 'NodeType' enum -> It simply contains IN_NODE or OUT_NODE, IN_NODE being an input-type node & OUT_NODE being a output-type node.

3. 'Decimal' typedef -> It mean 'int'. [typedef int Decimal]

4. 'INPUTDATA(x)' macro -> It is a BinaryInteger object with truncZeroOn=false. [#define INPUTDATA(x) BinaryInteger(x,false)]

5. 'InputSignals' typedef -> It is a vector of BinaryInteger which is needed for a simulation input.

6. 'SimulationOutput' typedef -> It is a vector of vector<bool> which is needed for a simulation output.

7. 'INV_NODESTATUS(x)' macro -> Inverts a 'NodeStatus' value.

########## Tutorial ############
http://technicodes.weebly.com/digilib.html
