

#include <fstream>



uint16_t ReadUInt16(std::ifstream & stream) {
//	uint8_t byte0;
//	uint8_t byte1;

	unsigned char byte0;
	unsigned char byte1;

	stream >> byte0;
	stream >> byte1;

	uint16_t sum = byte0 | (byte1 << 8);
	return sum;
}



uint32_t ReadUInt32(std::ifstream & stream) {
	//uint8_t byte0;
	//uint8_t byte1;
	//uint8_t byte2;
	//uint8_t byte3;

	unsigned char byte0;
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;


	stream >> byte0;
	stream >> byte1;
	stream >> byte2;
	stream >> byte3;

	//after breakpoint, it's reading this as 4 instead of 32
	//	reading and writing it to a file has correct value, so emulate that method for this reading

	uint32_t sum = 0;
	sum = byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24);

	return sum;
}
