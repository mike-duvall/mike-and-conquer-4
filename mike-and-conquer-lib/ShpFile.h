#pragma once


#include <string>
#include <vector>

class ImageHeader;

class ShpFile {

public:
	ShpFile(std::string & filename);
	int Width();
	int Height();
	long Size();
	int NumberOfImages();
	std::vector<unsigned char> & SpriteFrame1();
	std::vector<ImageHeader *> & ImageHeaders();

private:
	std::ifstream * shpFileStream;
	std::vector<unsigned char> allData;
	int allDataOffset;
	std::vector<unsigned char> spriteFrame1Vector;
	std::vector<ImageHeader *> imageHeaders;
	int numberOfImages;
	int width;
	int height;

};