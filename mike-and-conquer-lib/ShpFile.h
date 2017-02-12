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

private:
	std::vector<char> charVector;
	int numberOfImages;
	int width;
	int height;

	int ReadNumberOfImages();
	int ReadWidth();
	int ReadHeight();

};