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
	GameSprite(LPDIRECT3DDEVICE9 device, ShpFile & shpFile, D3DCOLOR transparentColor, boolean animate,  int imageIndex);
	~GameSprite();
	virtual void Draw(float gameTime, int x, int y);
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetSpriteCenter(int x, int y);

private:

	LPDIRECT3DTEXTURE9 InitializeTextureFromPngFile( std::string filename, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 InitializeTextureFromShpFile(ShpFile & shpFile, int imageIndex);
	LPDIRECT3DTEXTURE9 CreateTextureForDrawing();
	void DrawImageDataToTexture(LPDIRECT3DTEXTURE9 textureX, point_vertex * imageData);
	int MapColorIndex(int index);
	bool InitializeDirectXSpriteInterface();

	LPD3DXSPRITE   sprite;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 scaling;

	LPDIRECT3DTEXTURE9 texture1;
	LPDIRECT3DTEXTURE9 texture2;
	int textureTimer = 0;
	boolean animate;

	LPDIRECT3DTEXTURE9 currentTexture;
	LPDIRECT3DDEVICE9 device;

	//Attributes
	D3DCOLOR color;
	bool initialized;

	int width;
	int height;

};

