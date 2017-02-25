

#include "ImageHeader.h"





ImageHeader::ImageHeader(std::vector<unsigned char> & data) {
	
	//var data = stream.ReadUInt32();
	//FileOffset = data & 0xffffff;
	//Format = (Format)(data >> 24);
	//RefOffset = stream.ReadUInt16();
	//RefFormat = (Format)stream.ReadUInt16();

	//int data = ReadTwoBytesAsInt


}


unsigned int ImageHeader::Offset() {
	return 0;
}


Format ImageHeader::Format() {
	return XORPrev;
}