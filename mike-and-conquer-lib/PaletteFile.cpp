#include "PaletteFile.h"

#include <fstream>
#include "LittleEndianNumberStream.h"
#include "PaletteEntry.h"

PaletteFile::PaletteFile(std::string & filename) {

	std::ifstream *  shpFileStream = new std::ifstream(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = shpFileStream->tellg();
	shpFileStream->seekg(0, std::ios::beg);

	allDataOffset = 0;
	allData = ReadAllBytes(filename.c_str());

	int numBytes = allData.size();

	while (allDataOffset < numBytes) {
		uint8_t red = ReadUInt8(allData, allDataOffset);
		uint8_t green = ReadUInt8(allData, allDataOffset);
		uint8_t blue = ReadUInt8(allData, allDataOffset);

		PaletteEntry * paletteEntry = new PaletteEntry(red, green, blue);

		paletteEntryList.push_back(paletteEntry);

	}

}

PaletteFile::~PaletteFile() {

	for (std::vector<PaletteEntry *>::iterator it = paletteEntryList.begin(); it != paletteEntryList.end(); ++it) {
		PaletteEntry * paletteEntry = *it;
		delete paletteEntry;
	}

	paletteEntryList.clear();

}


std::vector<PaletteEntry *> & PaletteFile::GetPaletteEntries() {
	return paletteEntryList;
}

