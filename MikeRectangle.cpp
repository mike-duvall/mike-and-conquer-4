#include "MikeRectangle.h"


#include "graphics.h"


struct VERTEX_2D_DIF { // transformed colorized
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};




MikeRectangle::MikeRectangle(int x, int y) {
	this->x = x;
	this->y = y;
}

void MikeRectangle::Draw(LPDIRECT3DDEVICE9 device) {

	VERTEX_2D_DIF verts[5];

	verts[0].x = 100;
	verts[0].y = 100;
	verts[0].z = 0;
	verts[0].rhw = 1;
	verts[0].color = graphicsNS::MAGENTA;

	verts[1].x = 300;
	verts[1].y = 100;
	verts[1].z = 0;
	verts[1].rhw = 1;
	verts[1].color = graphicsNS::MAGENTA;

	verts[2].x = 300;
	verts[2].y = 400;
	verts[2].z = 0;
	verts[2].rhw = 1;
	verts[2].color = graphicsNS::MAGENTA;

	verts[3].x = 100;
	verts[3].y = 400;
	verts[3].z = 0;
	verts[3].rhw = 1;
	verts[3].color = graphicsNS::MAGENTA;

	verts[4].x = 100;
	verts[4].y = 100;
	verts[4].z = 0;
	verts[4].rhw = 1;
	verts[4].color = graphicsNS::MAGENTA;


	device->SetFVF(VERTEX_2D_DIF::FVF);
	device->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &verts, sizeof(VERTEX_2D_DIF));

	//Figure out how to draw as transformed vertices:
	//Read this: http://www.directxtutorial.com/Lesson.aspx?lessonid=9-4-4
	//	and the next one

}

