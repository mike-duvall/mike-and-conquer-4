#pragma once


#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif


#include <d3d9.h>
#include <d3dx9.h>


// TODO Use namespaces.  Naming MikeRectangle to not conflict with Windows Rectangle() function
class MikeRectangle {


public:
	MikeRectangle(int x, int y, int width, int height);

	void Draw(LPDIRECT3DDEVICE9 device);

	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }

private:
	int x;
	int y;
	int width;
	int height;
	int scale;

};