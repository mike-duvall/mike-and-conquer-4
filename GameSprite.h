#pragma once


#include <d3dx9.h>
#include <string>

#include <vector>
#include <map>

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
	virtual void Draw(float gameTime, int x, int y);
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetSpriteCenter(int x, int y);
	void IncrementFrame();
	void DecrementFrame();
	void AddAnimationSequence(unsigned int key, std::vector<unsigned int> animationSequence);
	void SetCurrentAnimationSequenceIndex(unsigned int animationSequence);
	unsigned int GetCurrentAnimationSequenceIndex() { return currentAnimationSequenceIndex; }

private:

	LPDIRECT3DTEXTURE9 InitializeTextureFromPngFile( std::string filename, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 InitializeTextureFromShpFile(ShpFile & shpFile, int imageIndex);
	void LoadAllTexturesFromShpFile(ShpFile & shpFile);
	LPDIRECT3DTEXTURE9 CreateTextureForDrawing();
	void DrawImageDataToTexture(LPDIRECT3DTEXTURE9 textureX, point_vertex * imageData);
	int MapColorIndex(int index);
	bool InitializeDirectXSpriteInterface();

	LPD3DXSPRITE   sprite;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 scaling;

	std::vector<LPDIRECT3DTEXTURE9> textureList;
	int textureTimer = 0;
	unsigned int currentAnimationFrame;
	unsigned int numFrames;
	std::map < unsigned int , std::vector<unsigned int> > animationSequenceMap;
	unsigned int currentAnimationSequenceIndex;

	LPDIRECT3DTEXTURE9 currentTexture;
	LPDIRECT3DDEVICE9 device;

	D3DCOLOR color;
	bool initialized;

	int width;
	int height;

};

