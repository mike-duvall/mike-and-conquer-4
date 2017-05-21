#pragma once

#include <stdint.h>
#include <vector>

class XORDeltaCompression {

public:

	static int DecodeInto(std::vector<uint8_t> & src, std::vector<uint8_t> & dest, int srcOffset = 0);


};

