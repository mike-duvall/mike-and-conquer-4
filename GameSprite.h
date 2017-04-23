#pragma once


#include <d3dx9.h>
#include <string>


class ShpFile;


const DWORD point_fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;


struct point_vertex {
	float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
	DWORD colour;        // The vertex colour.
};



class GameSprite {

public:
	GameSprite(LPDIRECT3DDEVICE9 device, std::string file,  D3DCOLOR transparentColor);
	GameSprite(LPDIRECT3DDEVICE9 device, ShpFile & shpFile, D3DCOLOR transparentColor);
	~GameSprite();
	virtual void Draw(float gameTime, D3DXVECTOR2 position);

private:

	void InitializeTextureFromPngFile( std::string filename, D3DCOLOR transparentColor);
	void InitializeTextureFromShpFile(ShpFile & shpFile);
	void CreateTextureForDrawing();
	void DrawImageDataToTexture(point_vertex * imageData);
	int mapColorIndex(int index);
	bool InitializeSprite();

	LPD3DXSPRITE   sprite;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 scaling;


	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DDEVICE9 device;

	//Attributes
	D3DCOLOR color;
	bool initialized;

	int width;
	int height;

	//point_vertex * imageData;
};

