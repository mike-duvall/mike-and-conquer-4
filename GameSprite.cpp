#include "GameSprite.h"

#include "graphics.h"
#include "ShpFile.h"
#include "PaletteFile.h"
#include "ImageHeader.h"
#include "PaletteEntry.h"
#include "AnimationSequence.h"
#include "ShpFileColorMapper.h"

#include "dxerr.h"


GameSprite::GameSprite(LPDIRECT3DDEVICE9 device, ShpFile & shpFile, ShpFileColorMapper * shpFileColorMapper, D3DCOLOR transparentColor) {
	this->device = device;
	this->shpFileColorMapper = shpFileColorMapper;

	LoadAllTexturesFromShpFile(shpFile);
	
	this->InitializeDirectXSpriteInterface();

}

GameSprite::GameSprite(LPDIRECT3DDEVICE9 device, std::string file, D3DCOLOR transparentColor) {
	this->device = device;
	this->InitializeTextureFromPngFile( file, transparentColor);
	this->InitializeDirectXSpriteInterface();
}


GameSprite::~GameSprite() {
}


void populateBlankPixel(point_vertex & point_vertex, int x, int y) {
	point_vertex.x = (float)x;
	point_vertex.y = (float)y;
	point_vertex.z = 1.0f;
	point_vertex.rhw = 1.0f;
	point_vertex.colour = D3DCOLOR_RGBA(0, 0, 0, 0);
}

void GameSprite::populateNonBlankPixel(point_vertex & point_vertex, int x, int y, unsigned char colorIndex, std::vector<PaletteEntry *> & paletteEntries) {

	int mappedColorIndex = shpFileColorMapper->MapColorIndex(colorIndex);

	PaletteEntry * paletteEntry = paletteEntries[mappedColorIndex];

	float fRed = (float)paletteEntry->GetRed() / 63.0f * 255.0f;
	float fGreen = (float)paletteEntry->GetGreen() / 63.0f * 255.0f;
	float fBlue = (float)paletteEntry->GetBlue() / 63.0f  * 255.0f;

	unsigned int intRed = (unsigned int)fRed;
	unsigned int intGreen = (unsigned int)fGreen;
	unsigned int intBlue = (unsigned int)fBlue;

	point_vertex.x = (float)x;
	point_vertex.y = (float)y;
	point_vertex.z = 1.0f;
	point_vertex.rhw = 1.0f;
	point_vertex.colour = D3DCOLOR_XRGB(intRed, intGreen, intBlue);
}


point_vertex * GameSprite::mapImageData(int width, int height, std::vector<unsigned char> & byteBuffer0, std::vector<PaletteEntry *> & paletteEntries) {
	point_vertex * imageData = new point_vertex[width * height];
	int currentIndex = 0;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned char nextByte = byteBuffer0[currentIndex];
			if (nextByte != 0) 
				populateNonBlankPixel(imageData[currentIndex], x, y, nextByte, paletteEntries);
			else 
				populateBlankPixel(imageData[currentIndex], x, y);
			currentIndex++;
		}
	}

	return imageData;
}


LPDIRECT3DTEXTURE9 GameSprite::CreateTextureForDrawing() {
	LPDIRECT3DTEXTURE9 textureX;
	UINT usage = D3DUSAGE_RENDERTARGET;

	HRESULT result = D3DXCreateTexture(
		device,      // Associated Direct3D device.
		width, height, // Dimensions of surface in pixels we render to.
		1,      // Number of mipmap levels.

		usage,           // How the texture will be used.
		D3DFMT_UNKNOWN,      // Texture format (i.e., D3DFORMAT).
		D3DPOOL_DEFAULT, // Render targets must be in default pool.
		&textureX);         // Returns pointer to texture.
	if (result != D3D_OK) {
		throw("Failed calling D3DXCreateTexture()");
	}

	return textureX;
}

void GameSprite::DrawImageDataToTexture(LPDIRECT3DTEXTURE9 textureX, point_vertex * imageData) {
	LPDIRECT3DSURFACE9 surfaceToRenderTo;
	D3DSURFACE_DESC desc;
	textureX->GetSurfaceLevel(0, &surfaceToRenderTo);
	surfaceToRenderTo->GetDesc(&desc);


	ID3DXRenderToSurface * renderToSurface;
	HRESULT result = D3DXCreateRenderToSurface(device, desc.Width, desc.Height, desc.Format, TRUE, D3DFMT_D16, &renderToSurface);
	if (FAILED(result))
		throw("Failed calling D3DXCreateRenderToSurface()");

	renderToSurface->BeginScene(surfaceToRenderTo, NULL);
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	device->SetFVF(point_fvf);

	device->DrawPrimitiveUP(D3DPT_POINTLIST,        //PrimitiveType
		width * height,    // Primitive count
		imageData,                   //pVertexStreamZeroData
		sizeof(point_vertex));  //VertexStreamZeroStride

	renderToSurface->EndScene(0);

}


void GameSprite::LoadAllTexturesFromShpFile(ShpFile & shpFile) {

	width = shpFile.Width();
	height = shpFile.Height();

	PaletteFile paletteFile(std::string("assets/temperat.pal"));
	std::vector<PaletteEntry *> & paletteEntries = paletteFile.GetPaletteEntries();

	int x = 0;
	std::vector<ImageHeader *> &  imageHeaders = shpFile.ImageHeaders();
	for (std::vector<ImageHeader *>::iterator it = imageHeaders.begin(); it != imageHeaders.end(); ++it) {
		ImageHeader * imageHeader = *it;
		std::vector<unsigned char> & byteBuffer0 = imageHeader->GetData();
		point_vertex * imageData = mapImageData(width, height, byteBuffer0, paletteEntries);
		LPDIRECT3DTEXTURE9 texture = CreateTextureForDrawing();
		DrawImageDataToTexture(texture, imageData);

		textureList.push_back(texture);
		x++;
	}
}


#include "dbghelp.h"

#define TRACE_MAX_STACK_FRAMES 1024
#define TRACE_MAX_FUNCTION_NAME_LENGTH 1024

#include <stdio.h>
#include <Windows.h>

#define BUFSIZE MAX_PATH

#include <tchar.h>



int printStackTrace()
{
	void *stack[TRACE_MAX_STACK_FRAMES];
	HANDLE process = GetCurrentProcess();

	bool doit = false;
	if (doit) {
		SetCurrentDirectory("C:\\remotetemp");
		SymInitialize(process, "C:\\remotetemp", TRUE);
	}
	else {
		SymInitialize(process, NULL, TRUE);
	}


	char path[255];
	SymGetSearchPath(process, path, 255 );

	TCHAR Buffer[BUFSIZE];
	DWORD dwRet = GetCurrentDirectory(BUFSIZE, Buffer);


	WORD numberOfFrames = CaptureStackBackTrace(0, TRACE_MAX_STACK_FRAMES, stack, NULL);
	SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO) + (TRACE_MAX_FUNCTION_NAME_LENGTH - 1) * sizeof(TCHAR));
	symbol->MaxNameLen = TRACE_MAX_FUNCTION_NAME_LENGTH;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	DWORD displacement;
	IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
	line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);


	for (int i = 0; i < numberOfFrames; i++)
	{
		DWORD64 address = (DWORD64)(stack[i]);
		SymFromAddr(process, address, NULL, symbol);
		if (SymGetLineFromAddr64(process, address, &displacement, line))
		{
			char buffer[500];
			sprintf(buffer, "\tat %s in %s: line: %lu: address: 0x%0X\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
			printf("\tat %s in %s: line: %lu: address: 0x%0X\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
		}
		else
		{
			char buffer1[500];
			sprintf(buffer1, "\tSymGetLineFromAddr64 returned error code %lu.\n", GetLastError());
			printf("\tSymGetLineFromAddr64 returned error code %lu.\n", GetLastError());

			char buffer2[500];
			sprintf(buffer2, "\tat %s, address 0x%0X.\n", symbol->Name, symbol->Address);
			printf("\tat %s, address 0x%0X.\n", symbol->Name, symbol->Address);
		}
	
	}
	return 0;
}

void GameSprite::InitializeTextureFromPngFile(std::string filename, D3DCOLOR transparentColor) {
	// Get width and height from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (FAILED(result)) {
		//throw(GameError(gameErrorNS::FATAL_ERROR, "Failed calling D3DXGetImageInfoFromFile()"));
		//WCHAR result = DXGetErrorString(result);
		std::string errorString = DXGetErrorString(result);
		std::string errorDescription = DXGetErrorDescription(result);

		std::string errorMessage = "Error in InitializeTextureFromPngFile():  filename=" + filename + 
			".  Error string: " + errorString + ".  Error description:" + errorDescription;
		//throw("Failed calling D3DXGetImageInfoFromFile()");

		printStackTrace();


		throw(errorMessage);

	}

	width = info.Width;
	height = info.Height;

	LPDIRECT3DTEXTURE9 textureX;
	// Create the new texture by loading from file
	result = D3DXCreateTextureFromFileEx(
		device,           //3D device
		filename.c_str(),           //image filename
		info.Width,         //texture width
		info.Height,        //texture height
		1,                  //mip-map levels (1 for no chain)
		0,                  //usage
		D3DFMT_UNKNOWN,     //surface format (default)
		D3DPOOL_DEFAULT,    //memory class for the texture
		D3DX_FILTER_POINT,       //image filter
		D3DX_FILTER_NONE,       //mip filter
		transparentColor,
		&info,              //bitmap file info (from loaded file)
		NULL,               //color palette
		&textureX);         //destination texture
	if (FAILED(result)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed calling D3DXCreateTextureFromFileEx()"));
	}

	textureList.push_back(textureX);

}

bool GameSprite::InitializeDirectXSpriteInterface() {

	bool success = true;
	try {
		HRESULT     result;         // standard Windows return codes
		result = D3DXCreateSprite(device, &sprite);
		if (FAILED(result))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D sprite"));

		//float overallScaling = 5.0f;
		float overallScaling = 4.0f;

		// Original C&C resolution was 640 x 400, which is what the original artwork was scaled for
		// But current actual screen resolution is being set to  640 x 480
		// 400 is 83.33333 percent of 480
		// So multiply desired scaling by 0.8333333 to get actual scaled height

		//float widthAdjustmentAmount = 400.0f / 480.0f;
		//float actualWidthScaling = overallScaling * widthAdjustmentAmount;
		//float actualHeightScaling = overallScaling;
		//scaling = D3DXVECTOR2(actualWidthScaling, actualHeightScaling);
		scaling = D3DXVECTOR2(overallScaling, overallScaling);

		//spriteCenter = D3DXVECTOR2((float)(actualWidthScaling /  2),
		//	(float)(actualHeightScaling / 2));

		spriteCenter = D3DXVECTOR2((float)(width /  2),
			(float)(height / 2));



	}
	catch (...) { return false; }
	initialized = true;                    // set true when initialized
	return success;
}

void GameSprite::setScaling(float newScaling) {
	scaling = D3DXVECTOR2(newScaling, newScaling);
}

void GameSprite::SetSpriteCenter(int x, int y) {
	spriteCenter = D3DXVECTOR2((float)x,
		(float)y);
}


void GameSprite::Draw(float gameTime, int x, int y) {

	D3DXVECTOR2 position;
	position.x = (float)x;
	position.y = (float)y;

	D3DCOLOR color = graphicsNS::WHITE;


	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DDEVICE9 device3d = device;
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device3d->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);

	device3d->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device3d->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	D3DXVECTOR2 translate = position;
	float xOffset = this->width / 2.0f;
	float yOffset = this->height / 2.0f;
	translate.x = translate.x - xOffset;
	translate.y = translate.y - yOffset;
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		&spriteCenter,               // keep origin at top left when scaling
		0.0f,               // no scaling rotation
		&scaling,           // scale amount
		&spriteCenter,      // rotation center
		(float)0,			// rotation angle
		&translate);        // X,Y location


	sprite->SetTransform(&matrix);

	AnimationSequence * currentAnimationSequence = animationSequenceMap[currentAnimationSequenceIndex];
	currentAnimationSequence->Update();
	int currentTextureIndex = currentAnimationSequence->GetCurrentFrame();
	currentTexture = textureList[currentTextureIndex];


	sprite->Draw(currentTexture, NULL, NULL, NULL, color);
	sprite->End();

}

void GameSprite::SetCurrentAnimationSequenceIndex(unsigned int aniatmionSequenceIndex){
	if (currentAnimationSequenceIndex == aniatmionSequenceIndex) {
		return;
	}

	currentAnimationSequenceIndex = aniatmionSequenceIndex;

	AnimationSequence * animationSequence = animationSequenceMap[currentAnimationSequenceIndex];
	animationSequence->SetCurrentFrameIndex(0);

	unsigned int currentTextureIndex = animationSequence->GetCurrentFrame();
	currentTexture = textureList[currentTextureIndex];
}


void GameSprite::AddAnimationSequence(unsigned int key, AnimationSequence * animationSequence) {
	animationSequenceMap[key] = animationSequence;
}

void GameSprite::SetAnimate(bool newValue) {
	AnimationSequence * animationSequence = animationSequenceMap[currentAnimationSequenceIndex];
	animationSequence->SetAnimate(newValue);
}