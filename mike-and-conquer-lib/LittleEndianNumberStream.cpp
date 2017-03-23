

#include <fstream>



uint16_t ReadUInt16(std::ifstream & stream) {

	char xbyte0;
	char xbyte1;

	stream.get(xbyte0);
	stream.get(xbyte1);

	unsigned char byte0 = xbyte0;
	unsigned char byte1 = xbyte1;


	uint16_t sum = byte0 | (byte1 << 8);
	return sum;
}



uint32_t ReadUInt32(std::ifstream & stream) {

	char xbyte0;
	char xbyte1;
	char xbyte2;
	char xbyte3;

	stream.get(xbyte0);
	stream.get(xbyte1);
	stream.get(xbyte2);
	stream.get(xbyte3);

	unsigned char byte0 = xbyte0;
	unsigned char byte1 = xbyte1;
	unsigned char byte2 = xbyte2;
	unsigned char byte3 = xbyte3;

	uint32_t sum = 0;
	sum = byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24);

	return sum;
}
