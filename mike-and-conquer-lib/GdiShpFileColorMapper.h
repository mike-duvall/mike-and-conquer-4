#pragma once

#include "ShpFileColorMapper.h"


class GdiShpFileColorMapper : public ShpFileColorMapper {

	int MapColorIndex(int index) { return index;  }
};

