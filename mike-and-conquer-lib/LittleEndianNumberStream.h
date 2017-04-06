#pragma once

#include <stdint.h>
#include <fstream>

class LittleEndianNumberStream {

};


uint8_t  ReadUInt8(std::vector<unsigned char> & data, int & dataOffset);
uint16_t ReadUInt16(std::vector<unsigned char> & data, int & dataOffset);
uint32_t ReadUInt32(std::vector<unsigned char> & data, int & dataOffset);
std::vector<unsigned char> ReadAllBytes(char const* filename);