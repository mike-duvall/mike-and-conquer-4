#pragma once


#include <vector>


enum Format { NONE = 0x00, XORPrev = 0x20, XORLCW = 0x40, LCW = 0x80 };

class ImageHeader {

public:


	ImageHeader(std::vector<unsigned char> & data, int & dataOffset);
	unsigned int GetFileOffset();
	Format GetFormat();

	unsigned int GetRefOffset();
	Format GetRefFormat();
	std::vector<unsigned char> & GetData();
	void SetData(std::vector<unsigned char> & dataToSet);


private:

	Format format;
	uint32_t fileOffset;
	uint16_t refOffset;
	Format refFormat;

	std::vector<unsigned char> data;


};
