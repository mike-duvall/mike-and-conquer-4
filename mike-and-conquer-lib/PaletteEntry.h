#pragma once

#include <stdint.h>

class PaletteEntry {

public:
	PaletteEntry(uint8_t red, uint8_t green, uint8_t blue);

	uint8_t GetRed() { return red;  }
	uint8_t GetGreen() { return green; }
	uint8_t GetBlue() { return blue; }

private:

	uint8_t red;
	uint8_t green;
	uint8_t blue;

};