#ifndef ALU_H
#define ALU_H

#include "common.h"
#include "Utils.h"

class Alu {
public:
	stream run(byte, stream, stream);

private:
	stream streamAdd(stream, stream);
	stream streamSub(stream, stream);
	stream streamAnd(stream, stream);
	stream streamOr(stream, stream);
	stream streamNot(stream);
	stream streamXor(stream, stream);
};
#endif // ALU_H