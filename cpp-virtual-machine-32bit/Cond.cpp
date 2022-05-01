#include "Cond.h"

bool Cond::run(byte instruction, stream value1, stream value2) {
	int instructionCode = Utils::decoder3bit(instruction);
	
	bool result = false;
	switch (instructionCode) {
		case 0: 
			result = value1 == value2;
			break;
		case 1:
			result = !(value1 == value2);
			break;
		case 2:
			result = Utils::streamLessThan(value1, value2);
			break;
		case 3:
			result = Utils::streamLessThan(value1, value2) | value1 == value2;
			break;
		case 4:
			result = Utils::streamMoreThan(value1, value2);
			break;
		case 5:
			result = Utils::streamMoreThan(value1, value2) | value1 == value2;
			break;
	}
	return result;
}