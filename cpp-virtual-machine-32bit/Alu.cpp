#include "Alu.h"
#include <iostream>

stream Alu::run(byte instruction, stream value1, stream value2) {
	int instructionCode = Utils::decoder3bit(instruction);
	stream result;

	switch (instructionCode) {
		case 0:
			result = Alu::streamAdd(value1, value2);
			break;
		case 1:
			result = Alu::streamSub(value1, value2);
			break;
		case 2:
			result = Alu::streamAnd(value1, value2);
			break;
		case 3:
			result = Alu::streamOr(value1, value2);
			break;
		case 4:
			result = Alu::streamNot(value1);
			break;
		case 5:
			result = Alu::streamXor(value1, value2);
			break;
	}
	return result;
}

stream Alu::streamAdd(stream value1, stream value2) {
	stream result = Utils::streamAdd(value1, value2);

	return result;
}

stream Alu::streamSub(stream value1, stream value2) {
	stream result = Utils::streamSub(value1, value2);

	return result;
}

stream Alu::streamAnd(stream value1, stream value2) {
	stream result = (value1 & value2);

	return result;
};

stream Alu::streamOr(stream value1, stream value2) {
	stream result = (value1 | value2);

	return result;
};

stream Alu::streamNot(stream value1) {
	stream result = ~value1;

	return result;
};

stream Alu::streamXor(stream value1, stream value2) {
	stream result = value1 ^ value2;

	return result;
};