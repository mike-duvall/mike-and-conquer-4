#pragma once


#include <d3dx9.h>
#include <string>

class GameSprite
{
public:
	GameSprite(LPDIRECT3DDEVICE9 device, std::string file, int width, int height, D3DCOLOR transparentColor);
	~GameSprite();
	virtual void Draw(float gameTime, D3DXVECTOR2 position);

private:

	void InitializeTexture( std::string filename, D3DCOLOR transparentColor);
	bool InitializeSprite( std::string file);

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
};

