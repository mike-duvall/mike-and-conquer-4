#pragma once



#include <d3dx9.h>
#include <string>

class GameSprite
{
public:
	//Constructors and Destructor
	GameSprite();
	~GameSprite();

	//Sprite Functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void Draw(float gameTime, D3DXVECTOR2 position);
private:

	void InitializeTexture( std::string filename);
	bool InitializeSprite( std::string file);

	LPD3DXSPRITE   sprite;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 scaling;


	//Pointers
	LPDIRECT3DTEXTURE9 texture;
//	LPD3DXSPRITE sprite;
	LPDIRECT3DDEVICE9 device;

	//Attributes
	D3DCOLOR color;
	bool initialized;


	int width;
	int height;
};

