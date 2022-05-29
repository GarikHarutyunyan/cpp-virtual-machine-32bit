#include "Utils.h"

int Utils::binaryToInt(byte value) {
	int result = (int)(value.to_ulong());

	return result;
}

int Utils::binaryToInt(stream value) {
	int result = (int)(value.to_ulong());

	return result;
}

stream Utils::byteToStream(byte value) {
	stream result = Utils::binaryToInt(value);

	return result;
}

int Utils::decoder3bit(byte value)
{
	bool value1 = value[0];
	bool value2 = value[1];
	bool value3 = value[2];

	int result = 0;

	if (value1) {
		result += 1;
	}

	if (value2) {
		result += 2;
	}

	if (value3) {
		result += 4;
	}

	return result;
}

int Utils::decoder4bit(byte value)
{
	bool value4 = value[3];
	int result = Utils::decoder3bit(value);

	if (value4) {
		result += 8;
	}

	return result;
}

stream Utils::streamAdd(stream value1, stream value2) {
	stream result = value1.to_ullong() + value2.to_ullong();

	return result;
}

stream Utils::streamNot(stream value) {
	stream result = value.flip();

	return result;
}

stream Utils::streamSignedNegator(stream value) {
	stream value1 = Utils::streamNot(value);
	stream value2(1); // "00000001"
	stream result = Utils::streamAdd(value1, value2);

	return result;
}

stream Utils::streamSub(stream value1, stream value2) {
	stream result = Utils::streamAdd(value1, Utils::streamSignedNegator(value2));

	return result;
}

bool Utils::streamLessThan(stream value1, stream value2) {
	bool result = false;

	for (int i = value1.size()-1; i >= 0; i--) {
		if (value1[i] ^ value2[i]) {
			result = value2[i];
			break;
		}
	}

	return result;
}

bool Utils::streamMoreThan(stream value1, stream value2) {
	bool result = Utils::streamLessThan(value2, value1);

	return result;
}
