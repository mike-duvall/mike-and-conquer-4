#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif


#include <d3d9.h>
#include <d3dx9.h>


class Circle {


public:
	Circle(int x, int y);

	void Draw(LPDIRECT3DDEVICE9 device);

	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }



private:
	int x;
	int y;


};