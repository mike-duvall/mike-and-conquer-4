#include "ShpFile.h"

#include <vector>
#include <fstream>



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


int ReadTwoBytesAsInt(int byteOffset1, int byteOffset2, std::vector<unsigned char> bytes) {
	char byte0 = bytes[byteOffset1];
	char byte1 = bytes[byteOffset2];
	return (byte1 * 256) + byte0;
}


int ShpFile::ReadNumberOfImages() {
	return ReadTwoBytesAsInt(0, 1, charVector);
}

int ShpFile::ReadWidth() {
	return ReadTwoBytesAsInt(6, 7, charVector);
}


int ShpFile::ReadHeight() {
	return ReadTwoBytesAsInt(8, 9, charVector);
}



ShpFile::ShpFile(std::string & filename) {
	charVector = ReadAllBytes(filename.c_str());
	numberOfImages = ReadNumberOfImages();
	width = ReadWidth();
	height = ReadHeight();
}


int ShpFile::Width() {
	return width;
}

int ShpFile::Height() {
	return height;
}

long ShpFile::Size() {
	return charVector.size();
}


int ShpFile::NumberOfImages() {
	return numberOfImages;
}


std::vector<unsigned char> & ShpFile::SpriteFrame1() {
	return spriteFrame1Vector;
}	