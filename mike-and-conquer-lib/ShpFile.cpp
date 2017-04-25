#include "ShpFile.h"

#include <vector>
#include <fstream>
#include <iostream>

#include "ImageHeader.h"
#include "LittleEndianNumberStream.h"
#include "LCWCompression.h"

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
	std::ifstream * shpFileStream = new std::ifstream(filename, std::ios::binary | std::ios::ate);
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

	Decompress(imageHeaders[0]);
	Decompress(imageHeaders[1]);
	Decompress(imageHeaders[2]);

	int x = 3;
	//shpBytes = ReadRestOfStream(*shpFileStream, shpBytesFileOffset);

}


void ShpFile::Decompress(ImageHeader * h) {
	//// No extra work is required for empty frames
	//if (h.Size.Width == 0 || h.Size.Height == 0)
	//	return;

	//if (recurseDepth > imageCount)
	//	throw new InvalidDataException("Format20/40 headers contain infinite loop");

	switch (h->GetFormat()) {
		//case Format.XORPrev:
		//case Format.XORLCW:
		//{
		//	if (h.RefImage.Data == null)
		//	{
		//		++recurseDepth;
		//		Decompress(h.RefImage);
		//		--recurseDepth;
		//	}

		//	h.Data = CopyImageData(h.RefImage.Data);
		//	XORDeltaCompression.DecodeInto(shpBytes, h.Data, (int)(h.FileOffset - shpBytesFileOffset));
		//	break;
		//}

		case LCW: {
			//var imageBytes = new byte[Size.Width * Size.Height];
			//LCWCompression.DecodeInto(shpBytes, imageBytes, (int)(h.FileOffset - shpBytesFileOffset));
			//h.Data = imageBytes;

			int count = this->Width() * this->Height();
			//uint8_t * imageByes = new uint8_t[count];
			//LCWCompression.DecodeInto(shpBytes, imageBytes, (int)(h.FileOffset - shpBytesFileOffset));

			
			std::vector<unsigned char> imageBytes(count);
			int offset = (int)(h->GetFileOffset() - shpBytesFileOffset);
			LCWCompression::DecodeInto(shpBytes, imageBytes, offset, false);
			h->SetData(imageBytes);

			break;
		}
	}

	//default:
	//	throw new InvalidDataException();
	//}
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