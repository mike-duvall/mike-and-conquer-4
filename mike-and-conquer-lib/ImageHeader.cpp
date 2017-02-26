

#include "ImageHeader.h"


#include <fstream>


uint32_t ReadUInt32(std::ifstream * stream) {
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;

	*stream >> byte0;
	*stream >> byte1;
	*stream >> byte2;
	*stream >> byte3;

	uint32_t sum = 0;
	sum = byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24);

	return sum;
}


ImageHeader::ImageHeader(std::ifstream & stream) {
	
	//var data = stream.ReadUInt32();
	//FileOffset = data & 0xffffff;
	//Format = (Format)(data >> 24);
	//RefOffset = stream.ReadUInt16();
	//RefFormat = (Format)stream.ReadUInt16();

	//int data = ReadTwoBytesAsInt

	uint32_t data = ReadUInt32(&stream);
	fileOffset = data & 0xffffff;
	format = (Format)(data >> 24);
	int x = 3;

}


unsigned int ImageHeader::GetOffset() {
	return fileOffset;
}


Format ImageHeader::GetFormat() {
	return format;
}