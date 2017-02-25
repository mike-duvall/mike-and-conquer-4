#pragma once


#include <vector>


enum Format { XORPrev = 0x20, XORLCW = 0x40, LCW = 0x80 };

class ImageHeader {

public:


	ImageHeader(std::vector<unsigned char> & data);
	unsigned int Offset();
	Format Format();
};
