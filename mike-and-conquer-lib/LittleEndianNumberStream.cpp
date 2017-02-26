

#include <fstream>



uint16_t ReadUInt16(std::ifstream & stream) {
	char charByte0;
	char charByte1;
	stream >> charByte0;
	stream >> charByte1;
	return (charByte1 * 256) + charByte0;
}



uint32_t ReadUInt32(std::ifstream & stream) {
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;

	stream >> byte0;
	stream >> byte1;
	stream >> byte2;
	stream >> byte3;

	uint32_t sum = 0;
	sum = byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24);

	return sum;
}
