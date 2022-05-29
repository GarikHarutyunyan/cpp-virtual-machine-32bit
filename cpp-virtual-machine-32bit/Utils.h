#ifndef UTILS_H
#define UTILS_H

#include "common.h"

namespace Utils {
	int binaryToInt(byte);
	int binaryToInt(stream);
	stream stringToStream(std::string);
	stream byteToStream(byte);
	int decoder3bit(byte);
	int decoder4bit(byte);
	stream streamAdd(stream, stream);
	stream streamNot(stream);
	stream streamSignedNegator(stream);
	stream streamSub(stream, stream);
	bool streamLessThan(stream, stream);
	bool streamMoreThan(stream, stream);
};

#endif // UTILS_H