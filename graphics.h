#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif


class Mushroom;

#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"


// Color defines
// ARGB numbers range from 0 through 255
// a = Alpha channel (transparency where 255 is opaque)
// r = Red, g = Green, b = Blue
#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS
{
    const COLOR_ARGB WHITE   = D3DCOLOR_ARGB(255,255,255,255);
    const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255,255,  0,255);
    const COLOR_ARGB BLACK   = D3DCOLOR_ARGB(255,  0,  0,  0);
	const COLOR_ARGB CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const COLOR_ARGB CUSTOM = D3DCOLOR_ARGB(255, 35, 146, 22);
	const COLOR_ARGB CUSTOM2 = D3DCOLOR_ARGB(255, 147, 130, 64);
	const COLOR_ARGB CUSTOM3 = D3DCOLOR_ARGB(255, 49, 165, 46);
	const COLOR_ARGB CUSTOM4 = D3DCOLOR_ARGB(255, 43, 145, 40);
	const COLOR_ARGB CUSTOM5 = D3DCOLOR_ARGB(255, 134, 155, 85);
	const COLOR_ARGB CUSTOM6 = D3DCOLOR_XRGB(0, 100, 100);

    const COLOR_ARGB TRANSCOLOR = WHITE;

    enum DISPLAY_MODE{TOGGLE, FULLSCREEN, WINDOW};
}



class Graphics
{
private:
	LPDIRECT3D9       direct3d;
	LPDIRECT3DDEVICE9 device3d;
    D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE pMode;

    HRESULT     result;         // standard Windows return codes
    HWND        hwnd;
    bool        fullscreen;
    int         width;
    int         height;
    COLOR_ARGB  backColor;      // background color

    void    initD3Dpp();

public:

    Graphics();
    virtual ~Graphics();

    void    releaseAll();

    void    initialize(HWND hw, int width, int height, bool fullscreen);

    HRESULT showBackbuffer();

    // Checks the adapter to see if it is compatible with the BackBuffer height,
    // width and refresh rate specified in d3dpp. Fills in the pMode structure with
    // the format of the compatible mode, if found.
    // Pre: d3dpp is initialized.
    // Post: Returns true if compatible mode found and pMode structure is filled.
    //       Returns false if no compatible mode found.
    bool    isAdapterCompatible();

    HRESULT reset();


	LPDIRECT3DDEVICE9 get3Ddevice()   { return device3d; }
    bool getFullscreen()        { return fullscreen; }
	void setBackColor(COLOR_ARGB c);



    HRESULT beginScene() 
    {
        result = E_FAIL;
        if(device3d == NULL)
            return result;
        // Clear back buffer, stencil buffer and depth buffer
        device3d->Clear(0, 0, 
            D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
            backColor, 1.0f, 0);

        result = device3d->BeginScene();          // begin scene for drawing
        return result;
    }

    //=============================================================================
    // EndScene()
    //=============================================================================
    HRESULT endScene() 
    {
        result = E_FAIL;
        if(device3d)
            result = device3d->EndScene();
        return result;
    }

};



