#include "Circle.h"


#include "../graphics.h"



Circle::Circle(int x, int y) {
	this->x = x;
	this->y = y;
}


static const int CIRCLE_RESOLUTION = 64;

struct VERTEX_2D_DIF { // transformed colorized
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

void DrawCircleFilled(LPDIRECT3DDEVICE9 device, int mx, int my, int r, D3DCOLOR color) {
	VERTEX_2D_DIF verts[CIRCLE_RESOLUTION + 1];

	for (int i = 0; i < CIRCLE_RESOLUTION + 1; i++)
	{
		verts[i].x = mx + r*cos(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
		verts[i].y = my + r*sin(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
		verts[i].z = 0;
		verts[i].rhw = 1;
		verts[i].color = color;
	}

	device->SetFVF(VERTEX_2D_DIF::FVF);
	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_RESOLUTION - 1, &verts, sizeof(VERTEX_2D_DIF));
}




void Circle::Draw(LPDIRECT3DDEVICE9 device) {
	DrawCircleFilled(device, x, y, 5, graphicsNS::MAGENTA);
}
