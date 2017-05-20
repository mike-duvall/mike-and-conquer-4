#include <fstream>
#include <vector>




uint8_t ReadUInt8(std::vector<unsigned char> & data, int & dataOffset) {
	return data[dataOffset++];
}


uint16_t ReadUInt16(std::vector<unsigned char> & data, int & dataOffset) {
	unsigned char unsignedCharByte0 = data[dataOffset++];
	unsigned char unsignedCharByte1 = data[dataOffset++];
	uint16_t sum = unsignedCharByte0 | (unsignedCharByte1 << 8);
	return sum;
}

uint32_t ReadUInt32(std::vector<unsigned char> & data, int & dataOffset) {
	unsigned char unsignedCarByte0 = data[dataOffset++];
	unsigned char unsignedCharByte1 = data[dataOffset++];
	unsigned char unsignedCharByte2 = data[dataOffset++];
	unsigned char unsignedCharByte3 = data[dataOffset++];
	uint32_t sum = unsignedCarByte0 | (unsignedCharByte1 << 8) | (unsignedCharByte2 << 16) | (unsignedCharByte3 << 24);
	return sum;
}


std::vector<unsigned char> ReadAllBytes(char const* filename) {
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result((unsigned int)pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	std::vector<unsigned char> unsignedResult;
	for (std::vector<char>::iterator it = result.begin(); it != result.end(); ++it) {
		unsignedResult.push_back(*it);
	}

	return unsignedResult;
}
