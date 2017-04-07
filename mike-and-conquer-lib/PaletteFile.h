#pragma once


#include <string>
#include <vector>

class PaletteEntry;

class PaletteFile {

public:
	PaletteFile(std::string & filename);
	std::vector<PaletteEntry *> & GetPaletteEntries();


private:
	std::vector<PaletteEntry *> paletteEntryList;
	std::vector<unsigned char> allData;
	int allDataOffset;


};