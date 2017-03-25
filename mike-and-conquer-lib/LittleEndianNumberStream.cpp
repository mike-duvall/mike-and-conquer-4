

#include <fstream>



uint16_t ReadUInt16(std::ifstream & stream) {

	char charByte0;
	char charByte1;

	stream.get(charByte0);
	stream.get(charByte1);

	unsigned char unsignedCharByte0 = charByte0;
	unsigned char unsignedCharByte1 = charByte1;


	uint16_t sum = unsignedCharByte0 | (unsignedCharByte1 << 8);
	return sum;
}



uint32_t ReadUInt32(std::ifstream & stream) {


	char charByte0;
	char charByte1;
	char charByte2;
	char charByte3;

	stream.get(charByte0);
	stream.get(charByte1);
	stream.get(charByte2);
	stream.get(charByte3);

	unsigned char unsignedCarByte0 = charByte0;
	unsigned char unsignedCharByte1 = charByte1;
	unsigned char unsignedCharByte2 = charByte2;
	unsigned char unsignedCharByte3 = charByte3;

	uint32_t sum = unsignedCarByte0 | (unsignedCharByte1 << 8) | (unsignedCharByte2 << 16) | (unsignedCharByte3 << 24);

	return sum;
}
