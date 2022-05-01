#ifndef CPU_H
#define CPU_H

#include "common.h"
#include "Utils.h"
#include <istream>
#include <fstream>
#include "Alu.h"
#include "Cond.h"

const int REGISTERS_COUNT = 15;

class Cpu {
public:
	stream run(stream, bool = false);

private:
	void printRegisters();
	stream reg[REGISTERS_COUNT], counter = 0; // Using reg[0] for input and reg[1] for output
	Alu alu;
	Cond cond;
};

#endif // CPU_H