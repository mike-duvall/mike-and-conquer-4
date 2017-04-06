#include "PaletteFile.h"

#include <fstream>
#include "LittleEndianNumberStream.h"

PaletteFile::PaletteFile(std::string & filename) {

	std::ifstream *  shpFileStream = new std::ifstream(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = shpFileStream->tellg();
	shpFileStream->seekg(0, std::ios::beg);

	allDataOffset = 0;
	allData = ReadAllBytes(filename.c_str());


}



std::vector<PaletteEntry *> & PaletteFile::GetPaletteEntries() {
	return paletteEntryList;
}

