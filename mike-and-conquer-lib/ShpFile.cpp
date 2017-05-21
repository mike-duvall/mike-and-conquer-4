#include "ShpFile.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <map>

#include "ImageHeader.h"
#include "LittleEndianNumberStream.h"
#include "LCWCompression.h"
#include "XORDeltaCompression.h"




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

	std::map<unsigned int, ImageHeader *> offsetToImageHeaderMap;
	for (std::vector<ImageHeader *>::iterator it = imageHeaders.begin(); it != imageHeaders.end(); ++it) {
		ImageHeader * imageHeader = *it;
		offsetToImageHeaderMap[imageHeader->GetFileOffset()] = *it;
	}

	ImageHeader * previousImageHeader = NULL;
	for (std::vector<ImageHeader *>::iterator it = imageHeaders.begin(); it != imageHeaders.end(); ++it) {

		ImageHeader * imageHeader = *it;

		if (imageHeader->GetFormat() == XORPrev) {
			//h.RefImage = headers[i - 1];
			imageHeader->SetRefImageHeader(previousImageHeader);

		}
		else if (imageHeader->GetFormat() == XORLCW) {
			ImageHeader * refImage = offsetToImageHeaderMap.at(imageHeader->GetRefOffset());
			imageHeader->SetRefImageHeader(refImage);
		}
		previousImageHeader = imageHeader;
	}

	for (std::vector<ImageHeader *>::iterator it = imageHeaders.begin(); it != imageHeaders.end(); ++it) {
		Decompress(*it);
	}

	int x = 3;

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

		case XORPrev:
		case XORLCW: {
			//	h.Data = CopyImageData(h.RefImage.Data);
			std::vector<unsigned char> & data = h->GetRefImageHeader()->GetData();

			std::vector<unsigned char> imageBytes(data);

			int offset = (int)(h->GetFileOffset() - shpBytesFileOffset);
			//LCWCompression::DecodeInto(shpBytes, imageBytes, offset, false);
			XORDeltaCompression::DecodeInto(shpBytes, imageBytes, offset);
			h->SetData(imageBytes);

			
			//	XORDeltaCompression.DecodeInto(shpBytes, h.Data, (int)(h.FileOffset - shpBytesFileOffset));

			break;
		}

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