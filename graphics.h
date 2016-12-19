#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif


#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"


namespace graphicsNS
{
    const D3DCOLOR WHITE   = D3DCOLOR_ARGB(255,255,255,255);
    const D3DCOLOR MAGENTA = D3DCOLOR_ARGB(255,255,  0,255);
    const D3DCOLOR BLACK   = D3DCOLOR_ARGB(255,  0,  0,  0);
	const D3DCOLOR CYAN = D3DCOLOR_ARGB(255, 0, 255, 255);
	const D3DCOLOR CUSTOM6 = D3DCOLOR_XRGB(0, 100, 100);

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
    D3DCOLOR  backColor;      // background color

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
	void setBackColor(D3DCOLOR c);



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

    HRESULT endScene() 
    {
        result = E_FAIL;
        if(device3d)
            result = device3d->EndScene();
        return result;
    }

};



