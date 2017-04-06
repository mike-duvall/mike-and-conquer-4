#pragma once

#include <stdint.h>

class PaletteEntry {

public:
	PaletteEntry(uint8_t red, uint8_t green, uint8_t blue);

private:

	uint8_t red;
	uint8_t green;
	uint8_t blue;

};