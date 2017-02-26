#pragma once


#include <vector>


enum Format { XORPrev = 0x20, XORLCW = 0x40, LCW = 0x80 };

class ImageHeader {

public:


	ImageHeader(std::ifstream & stream);
	unsigned int GetOffset();
	Format GetFormat();

private:

	Format format;


};
