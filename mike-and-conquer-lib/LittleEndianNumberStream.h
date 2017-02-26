#pragma once

#include <stdint.h>
#include <fstream>

class LittleEndianNumberStream {

};


uint16_t ReadUInt16(std::ifstream & stream);
uint32_t ReadUInt32(std::ifstream & stream);