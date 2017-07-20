#include "MikeRectangle.h"


#include "../graphics.h"


struct VERTEX_2D_DIF { // transformed colorized
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};




MikeRectangle::MikeRectangle(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	scale = 4;
}

void MikeRectangle::Draw(LPDIRECT3DDEVICE9 device) {

// TODO: Refactor and clean up this class, have better name
// TODO: Make drawing of outline work for any game sprite
// TODO: Fixup selection cursor

	VERTEX_2D_DIF verts[5];

	int xOffset = (width * scale) / 2;
	int yOffset = (height * scale) / 2;

	verts[0].x = (float)(x - xOffset);
	verts[0].y = (float)(y - yOffset);
	verts[0].z = 1;
	verts[0].rhw = 1;
	verts[0].color = graphicsNS::MAGENTA;

	verts[1].x = (float)(x + xOffset);
	verts[1].y = (float)(y - yOffset);
	verts[1].z = 1;
	verts[1].rhw = 1;
	verts[1].color = graphicsNS::MAGENTA;

	verts[2].x = (float)(x + xOffset);
	verts[2].y = (float)(y + yOffset);
	verts[2].z = 1;
	verts[2].rhw = 1;
	verts[2].color = graphicsNS::MAGENTA;

	verts[3].x = (float)(x - xOffset);
	verts[3].y = (float)(y + yOffset);
	verts[3].z = 1;
	verts[3].rhw = 1;
	verts[3].color = graphicsNS::MAGENTA;

	verts[4].x = (float)(x - xOffset);
	verts[4].y = (float)(y - yOffset);
	verts[4].z = 1;
	verts[4].rhw = 1;
	verts[4].color = graphicsNS::MAGENTA;

	device->SetFVF(VERTEX_2D_DIF::FVF);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP,4, &verts, sizeof(VERTEX_2D_DIF));

}

