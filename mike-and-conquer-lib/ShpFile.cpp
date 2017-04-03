#include "ShpFile.h"

#include <vector>
#include <fstream>
#include <iostream>

#include "ImageHeader.h"


#include "LittleEndianNumberStream.h"

static std::vector<unsigned char> ReadAllBytes(char const* filename) {
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	std::vector<unsigned char> unsignedResult;
	for (std::vector<char>::iterator it = result.begin(); it != result.end(); ++it) {
		unsignedResult.push_back(*it);
	}

	return unsignedResult;
}



ShpFile::ShpFile(std::string & filename) {
	shpFileStream = new std::ifstream(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = shpFileStream->tellg();
	shpFileStream->seekg(0, std::ios::beg);

	allDataOffset = 0;
	allData = ReadAllBytes(filename.c_str());
	

	// write contents of file to text file
	//std::ofstream out("d:/mc-e1.shp.txt");
	//for (std::vector<unsigned char>::iterator it = charVector.begin(); it != charVector.end(); ++it) {
	//	unsigned int charAsInt = *it;
	//	out << charAsInt << std::endl;
	//}

	//out.close();
	
	numberOfImages = ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);  // 2, 3
	ReadUInt16(allData, allDataOffset);  // 4, 5

	width = ReadUInt16(allData, allDataOffset);  // 6, 7
	height = ReadUInt16(allData, allDataOffset);  // 8, 9

	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);

	for (int i = 0; i < numberOfImages; i++) {
		ImageHeader * imageHeader = new ImageHeader(allData, allDataOffset);
		imageHeaders.push_back(imageHeader);
	}

	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);
	ReadUInt16(allData, allDataOffset);

	shpBytesFileOffset = imageHeaders[0]->GetFileOffset();

	int size = allData.size();
	int countRemaining = size - allDataOffset;
		
	for (int i = 0; i < countRemaining; i++) {
		//printf("i=%d", i);
		shpBytes.push_back(allData[allDataOffset++]);
	}

	int x = 3;
	//shpBytes = ReadRestOfStream(*shpFileStream, shpBytesFileOffset);

}


int ShpFile::GetShpBytesFileOffset() {
	return shpBytesFileOffset;
}


std::vector<unsigned char> & ShpFile::GetShpBytes() {
	return shpBytes;
}

int ShpFile::Width() {
	return width;
}

int ShpFile::Height() {
	return height;
}

long ShpFile::Size() {
	return allData.size();
}


int ShpFile::NumberOfImages() {
	return numberOfImages;
}


std::vector<unsigned char> & ShpFile::SpriteFrame1() {
	return spriteFrame1Vector;
}	



std::vector<ImageHeader *> & ShpFile::ImageHeaders() {
	return this->imageHeaders;
}