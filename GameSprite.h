#pragma once

#include <d3dx9.h>

#include <vector>
#include <map>

class ShpFile;
class ShpFileColorMapper;
class PaletteEntry;
class AnimationSequence;

const DWORD point_fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;


struct point_vertex {
	float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
	DWORD colour;        // The vertex colour.
};



class GameSprite {

public:
	GameSprite(LPDIRECT3DDEVICE9 device, std::string file,  D3DCOLOR transparentColor);
	GameSprite(LPDIRECT3DDEVICE9 device, ShpFile & shpFile, ShpFileColorMapper * shpFileColorMapper, D3DCOLOR transparentColor);
	~GameSprite();
	virtual void Draw(float gameTime, int x, int y);
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetSpriteCenter(int x, int y);
	void AddAnimationSequence(unsigned int key, AnimationSequence * animationSequence);
	void SetCurrentAnimationSequenceIndex(unsigned int animationSequence);
	unsigned int GetCurrentAnimationSequenceIndex() { return currentAnimationSequenceIndex; }
	void setScaling(float scaling);
	void SetAnimate(bool newValue);

private:

	void InitializeTextureFromPngFile( std::string filename, D3DCOLOR transparentColor);
	void LoadAllTexturesFromShpFile(ShpFile & shpFile);
	LPDIRECT3DTEXTURE9 CreateTextureForDrawing();
	void DrawImageDataToTexture(LPDIRECT3DTEXTURE9 textureX, point_vertex * imageData);

	ShpFileColorMapper * shpFileColorMapper;

	void populateNonBlankPixel(point_vertex & point_vertex, int x, int y, unsigned char colorIndex, std::vector<PaletteEntry *> & paletteEntries);
	point_vertex * mapImageData(int width, int height, std::vector<unsigned char> & byteBuffer0, std::vector<PaletteEntry *> & paletteEntries);


	bool InitializeDirectXSpriteInterface();

	LPD3DXSPRITE   sprite;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 scaling;

	std::vector<LPDIRECT3DTEXTURE9> textureList;

	std::map < unsigned int, AnimationSequence * > animationSequenceMap;

	unsigned int currentAnimationSequenceIndex;

	LPDIRECT3DTEXTURE9 currentTexture;
	LPDIRECT3DDEVICE9 device;

	D3DCOLOR color;
	bool initialized;

	int width;
	int height;

};

