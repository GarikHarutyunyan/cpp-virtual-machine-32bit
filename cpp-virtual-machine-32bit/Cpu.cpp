#include "Cpu.h"
#include <istream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

stream Cpu::run(stream inputValue, bool debugMode) {
	this->reg[0] = inputValue;
	stream value1, value2;

	std::ifstream configFile;
	std::string fileName = "Program.txt";
	std::string currentCommandString;
	configFile.open(fileName);
	int sizeOfStream = inputValue.size() + 2; // stream length(32) + length of "/n"(2) = 10

	while (getline(configFile, currentCommandString)) {
		// counter++
		this->counter = Utils::streamAdd(this->counter, 1);

		stream currentCommand = Utils::stringToStream(currentCommandString);
		byte OPCODE(currentCommandString.substr(0,8)); // Get first 8 bits from 32
		byte ARGUMENT_1(currentCommandString.substr(8, 8));
		byte ARGUMENT_2(currentCommandString.substr(16, 8));
		byte RESULT_ADDRESS(currentCommandString.substr(24, 8));

		bool onConditionalMode = OPCODE[5];// **1***** 

		if (OPCODE[7]) { // 1*******
			value1 = Utils::byteToStream(ARGUMENT_1);
		}
		else {
			int registerIndex = Utils::decoder4bit(ARGUMENT_1);
			if (registerIndex != 1) {
				// reg[1] is used as output so its value can't be used
				value1 = this->reg[registerIndex];
			}
		}

		if (OPCODE[6]) { // *1******
			value2 = Utils::byteToStream(ARGUMENT_2);;
		}
		else {
			int registerIndex = Utils::decoder4bit(ARGUMENT_2);
			if (registerIndex != 1) {
				// reg[1] is used as output so its value can't be used
				value2 = this->reg[registerIndex];
			}
		}


		if (onConditionalMode) {
			if (this->cond.run(OPCODE, value1, value2)) {
				stream counterNewValue = Utils::streamSub(Utils::byteToStream(RESULT_ADDRESS), 1);
				this->counter = counterNewValue;
			}
		}
		else {
			int registerIndex = Utils::decoder4bit(RESULT_ADDRESS);
			if (registerIndex != 0) {
				// reg[0] is used as input so its value can't be changed
				this->reg[registerIndex] = this->alu.run(OPCODE, value1, value2);
			}
		}

		if (debugMode)
		{
			Cpu::printRegisters();
		}

		// Set index for configFile reading
		int counterIntValue = Utils::binaryToInt(this->counter);
		configFile.seekg((counterIntValue + 1) * sizeOfStream);
	}

	return this->reg[1];
}

void Cpu::printRegisters() {
	std::cout << "Input " << ": " << this->reg[0] << std::endl;
	for (int i = 2; i < REGISTERS_COUNT; i++) {
		std::cout << "Register "<< i << ": " << this->reg[i] << std::endl;
	}
	std::cout << "Output " << ": " << this->reg[0] << std::endl;
	std::cout << std::endl;
}