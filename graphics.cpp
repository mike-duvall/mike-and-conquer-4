
#include "graphics.h"



Graphics::Graphics() {
    direct3d = NULL;
    device3d = NULL;

    fullscreen = false;
    width = GAME_WIDTH;    // width & height are replaced in initialize()
    height = GAME_HEIGHT;
    backColor = graphicsNS::CUSTOM6;
}

Graphics::~Graphics() {
    ReleaseAll();
}

void Graphics::ReleaseAll() {
    //safeRelease(sprite);
    safeRelease(device3d);
    safeRelease(direct3d);
}

void Graphics::Initialize(HWND hw, int w, int h, bool full) {
    hwnd = hw;
    width = w;
    height = h;
    fullscreen = full;

    //initialize Direct3D
    direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (direct3d == NULL)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

    InitD3Dpp();        // init D3D presentation parameters
    if(fullscreen) {      // if full-screen mode
        if(IsAdapterCompatible())   // is the adapter compatible
            // set the refresh rate with a compatible one
            d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
        else
            throw(GameError(gameErrorNS::FATAL_ERROR, 
            "The graphics device does not support the specified resolution and/or format."));
    }

    // determine if graphics card supports harware texturing and lighting and vertex shaders
    D3DCAPS9 caps;
    DWORD behavior;
    result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
    // If device doesn't support HW T&L or doesn't support 1.1 vertex 
    // shaders in hardware, then switch to software vertex processing.
    if( (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
            caps.VertexShaderVersion < D3DVS_VERSION(1,1) )
        behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  // use software only processing
    else
        behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;  // use hardware only processing

    //create Direct3D device
    result = direct3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        behavior,
        &d3dpp, 
        &device3d);

    if (FAILED(result))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
 
    // Configure for alpha blend of primitives
    device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device3d->SetRenderState(D3DRS_LIGHTING, FALSE);

}

//=============================================================================
// Initialize D3D presentation parameters
//=============================================================================
void Graphics::InitD3Dpp() {
    try {
        ZeroMemory(&d3dpp, sizeof(d3dpp));              // fill the structure with 0
        // fill in the parameters we need
        d3dpp.BackBufferWidth   = width;
        d3dpp.BackBufferHeight  = height;
        if(fullscreen)                                  // if fullscreen
            d3dpp.BackBufferFormat  = D3DFMT_X8R8G8B8;  // 24 bit color
        else
            d3dpp.BackBufferFormat  = D3DFMT_UNKNOWN;   // use desktop setting
        d3dpp.BackBufferCount   = 1;
        d3dpp.SwapEffect        = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow     = hwnd;
        d3dpp.Windowed          = (!fullscreen);
        if(VSYNC)   // if vertical sync is enabled
            d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;
        else
            d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
        d3dpp.EnableAutoDepthStencil = true;
        d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;    // Depth 24, Stencil 8
    }
	catch(...) {
        throw(GameError(gameErrorNS::FATAL_ERROR, 
                "Error initializing D3D presentation parameters"));
    }
}

HRESULT Graphics::ShowBackbuffer() {
    // Display backbuffer to screen
    result = device3d->Present(NULL, NULL, NULL, NULL);
    return result;
}

//=============================================================================
// Checks the adapter to see if it is compatible with the BackBuffer height,
// width and refresh rate specified in d3dpp. Fills in the pMode structure with
// the format of the compatible mode, if found.
// Pre: d3dpp is initialized.
// Post: Returns true if compatible mode found and pMode structure is filled.
//       Returns false if no compatible mode found.
//=============================================================================
bool Graphics::IsAdapterCompatible() {
    UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, 
                                            d3dpp.BackBufferFormat);
    for(UINT i=0; i<modes; i++) {
        result = direct3d->EnumAdapterModes( D3DADAPTER_DEFAULT, 
                                        d3dpp.BackBufferFormat,
                                        i, &pMode);
        if( pMode.Height == d3dpp.BackBufferHeight &&
            pMode.Width  == d3dpp.BackBufferWidth &&
            pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
            return true;
    }
    return false;
}



//=============================================================================
// Reset the graphics device
//=============================================================================
HRESULT Graphics::Reset() {
    InitD3Dpp();                        // init D3D presentation parameters
    result = device3d->Reset(&d3dpp);   // attempt to reset graphics device

    // Configure for alpha blend of primitives
    device3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    device3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device3d->SetRenderState(D3DRS_LIGHTING, FALSE);
    return result;
}

// Set color used to clear screen
void Graphics::SetBackColor(D3DCOLOR c) {
	backColor = c;
}

