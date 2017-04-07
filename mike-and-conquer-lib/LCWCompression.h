#pragma once

#include <stdint.h>
#include <vector>

class LCWCompression {

public:

	
//	static int DecodeInto(uint8_t * src, uint8_t * dest, int srcOffset = 0, bool reverse = false);
	static int DecodeInto(std::vector<uint8_t> & src, std::vector<uint8_t> & dest, int srcOffset = 0, bool reverse = false);

	//static void ReplicatePrevious(byte[] dest, int destIndex, int srcIndex, int count)
	static void ReplicatePrevious(std::vector<uint8_t> &  dest, int destIndex, int srcIndex, int count);

};
