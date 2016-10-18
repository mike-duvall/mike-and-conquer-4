#pragma once
#define WIN32_LEAN_AND_MEAN


#include <string>
#include <d3d9.h>


class Graphics;

class Texture {

private:
	LPDIRECT3DTEXTURE9 texture;

	UINT         width;
	UINT         height;


public:
	Texture(Graphics * graphics, std::string filename);
	LPDIRECT3DTEXTURE9 getDirextXTexture() { return texture;}



};
