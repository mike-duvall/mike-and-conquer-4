#include "ImageHeader.h"


#include <fstream>
#include "LittleEndianNumberStream.h"



ImageHeader::ImageHeader(std::ifstream & stream) {
	
	//var data = stream.ReadUInt32();
	//FileOffset = data & 0xffffff;
	//Format = (Format)(data >> 24);
	//RefOffset = stream.ReadUInt16();
	//RefFormat = (Format)stream.ReadUInt16();

	//int data = ReadTwoBytesAsInt

	uint32_t data = ReadUInt32(stream);
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