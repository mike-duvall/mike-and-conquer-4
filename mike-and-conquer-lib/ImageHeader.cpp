#include "ImageHeader.h"


#include <fstream>
#include "LittleEndianNumberStream.h"



ImageHeader::ImageHeader(std::vector<unsigned char> & data, int & dataOffset) {
	
	//var data = stream.ReadUInt32();
	//FileOffset = data & 0xffffff;
	//Format = (Format)(data >> 24);
	//RefOffset = stream.ReadUInt16();
	//RefFormat = (Format)stream.ReadUInt16();

	//int data = ReadTwoBytesAsInt

	uint32_t readData = ReadUInt32(data,dataOffset);
	fileOffset = readData & 0xffffff;
	format = (Format)(readData >> 24);


	refOffset = ReadUInt16(data, dataOffset);
	refFormat = (Format)ReadUInt16(data, dataOffset);


}


void ImageHeader::SetData(std::vector<unsigned char> & dataToSet) {
	this->data = dataToSet;
}

unsigned int ImageHeader::GetFileOffset() {
	return fileOffset;
}


Format ImageHeader::GetFormat() {
	return format;
}


unsigned int ImageHeader::GetRefOffset() {
	return refOffset;
}


Format ImageHeader::GetRefFormat() {
	return refFormat;
}


std::vector<unsigned char> & ImageHeader::GetData() {
	return data;
}