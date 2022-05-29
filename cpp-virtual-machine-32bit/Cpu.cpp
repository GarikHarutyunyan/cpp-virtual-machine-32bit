#include "Cpu.h"
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

stream Cpu::run(stream inputValue, bool debugMode) {
	this->reg[0] = inputValue;
	stream value1, value2;

	std::string fileName = "Program.bin";
	std::ifstream configFile(fileName, std::ios::binary);
	std::vector<byte> program(std::istreambuf_iterator<char>(configFile), {});

	while (Utils::binaryToInt(this->counter) + 3 < program.size()) {
		int i = Utils::binaryToInt(this->counter);

		// counter += 4
		this->counter = Utils::streamAdd(this->counter, 4);

		byte OPCODE(program[i]); // Get first 8 bits from 32
		byte ARGUMENT_1(program[i+1]);
		byte ARGUMENT_2(program[i+2]);
		byte RESULT_ADDRESS(program[i+3]);

		bool onConditionalMode = OPCODE[5];// **1***** 

		if (OPCODE[7]) { // 1*******
			value1 = Utils::byteToStream(ARGUMENT_1);
		}
		else {
			int registerIndex = Utils::decoder4bit(ARGUMENT_1);
			value1 = this->reg[registerIndex];
		}

		if (OPCODE[6]) { // *1******
			value2 = Utils::byteToStream(ARGUMENT_2);;
		}
		else {
			int registerIndex = Utils::decoder4bit(ARGUMENT_2);
			value2 = this->reg[registerIndex];
		}


		if (onConditionalMode) {
			if (this->cond.run(OPCODE, value1, value2)) {
				stream counterNewValue = Utils::byteToStream(RESULT_ADDRESS);
				this->counter = counterNewValue;
			}
		}
		else {
			int registerIndex = Utils::decoder4bit(RESULT_ADDRESS);
			this->reg[registerIndex] = this->alu.run(OPCODE, value1, value2);
		}

		if (debugMode)
		{
			Cpu::printRegisters();
		}
	}

	return this->reg[1];
}

void Cpu::printRegisters() {
	std::cout << "Input " << ": " << this->reg[0] << std::endl;
	for (int i = 2; i < REGISTERS_COUNT; i++) {
		std::cout << "Register "<< i << ": " << this->reg[i] << std::endl;
	}
	std::cout << "Output " << ": " << this->reg[1] << std::endl;
	std::cout << "Counter " << ": " << this->counter << std::endl;
	std::cout << std::endl;
}