#include "Utils.h"

int Utils::binaryToInt(byte value) {
	int result = (int)(value.to_ulong());

	return result;
}

int Utils::binaryToInt(stream value) {
	int result = (int)(value.to_ulong());

	return result;
}

stream Utils::stringToStream(std::string value) {
	stream result(value);

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

std::pair<bool, bool> Utils::bitHalfAdder(bool value1, bool value2)
{
	bool carry = value1 & value2;
	bool sum = value1 ^ value2;

	return std::make_pair(carry, sum);
}


std::pair<bool, bool> Utils::bitFullAdder(bool value1, bool value2, bool value3)
{
	// Use Half adder on value1/value2, use half adder again for result's sum and value3
	std::pair<bool, bool> result1 = Utils::bitHalfAdder(value1, value2);
	bool carry1 = result1.first;
	bool sum1 = result1.second;

	std::pair<bool, bool> result2 = Utils::bitHalfAdder(sum1, value3);
	bool carry2 = result2.first;
	bool sum2 = result2.second;

	// take sum2 as sum and (carry1 or carry2) as carry;
	bool carry = carry1 | carry2;
	bool sum = sum2;
	return std::make_pair(carry, sum);
}

stream Utils::streamAdd(stream value1, stream value2) {
	stream result;
	bool carryBit = 0;
	std::pair<bool, bool> currentResult;

	for (int i = 0; i < value1.size(); i++) {
		currentResult = Utils::bitFullAdder(carryBit, value1[i], value2[i]);

		carryBit = currentResult.first;
		result[i] = currentResult.second;
	}

	return result;
}

stream Utils::streamNot(stream value) {
	stream result;
	for (int i = 0; i < value.size(); i++) {
		result[i] = ~value[i];
	}

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
