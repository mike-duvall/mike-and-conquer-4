#pragma once


#include <string>
#include <vector>

class ShpFile {

public:
	ShpFile(std::string & filename);
	int Width();
	int Height();
	long Size();
	int NumberOfImages();
	std::vector<unsigned char> & SpriteFrame1();

private:
	std::vector<unsigned char> charVector;
	std::vector<unsigned char> spriteFrame1Vector;
	int numberOfImages;
	int width;
	int height;

	int ReadNumberOfImages();
	int ReadWidth();
	int ReadHeight();

};