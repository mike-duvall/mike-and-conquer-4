#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks
#include "game.h"

#include <utility>

#include <chrono>
#include <thread>
#include "Minigunner.h"
#include "TestModeRestHandler.h"
#include "dummy.h"


//Unit test todos:
//XAdd mike-and-conquer-test project
//XAdd basic catch.hpp test
//XCheck that in
//
//(Assume mike-and-conquer is now mike-and-conquer-main)
//
//xAdd mike-and-conquer-lib project
//xPut code in it
//xTest that code in catch

// Make mike-and-conquer depend on mike-and-conquer-lib
//Gradually move stuff from mike-and-conquer to mike-and-conquer-lib

Game * game = NULL;


// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 


void init_input(HWND hWnd);

HWND hwnd = NULL;


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    MSG msg;

	int fact = Factorial(1);

	bool testMode = false;
	std::string commandLine = std::string(lpCmdLine);
	std::string TESTMODE = std::string("TESTMODE");


	if (TESTMODE == commandLine) {
		testMode = true;
	};

    game = new Game(testMode);

    if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
        return 1;

    try{
        game->Initialize(hwnd);     // throws GameError
		init_input(hwnd);

		if (testMode) {
			TestModeRestHandler * testModeRestHandler = new TestModeRestHandler(game);
		}

        int done = 0;
        while (!done)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
            {
                if (msg.message == WM_QUIT)
                    done = 1;

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else
                game->Run(hwnd);    
        }
        safeDelete(game);          
        return msg.wParam;
    }
    catch(const GameError &err) {
        game->DeleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    }
    catch(...) {
        game->DeleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
    }

    safeDelete(game);       // free memory before exit
    return 0;
}

// this is the function that initializes the Raw Input API
void init_input(HWND hWnd)
{
	RAWINPUTDEVICE Mouse;
	Mouse.usUsage = 0x02;    // register mouse
	Mouse.usUsagePage = 0x01;    // top-level mouse
	Mouse.dwFlags = NULL;    // flags
	Mouse.hwndTarget = hWnd;    // handle to a window

	RegisterRawInputDevices(&Mouse, 1, sizeof(RAWINPUTDEVICE));    // register the device
}

LRESULT WINAPI WinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    return (game->MessageHandler(hwnd, msg, wParam, lParam));
}

bool CreateMainWindow(HWND &hwnd, HINSTANCE hInstance, int nCmdShow) 
{ 
    WNDCLASSEX wcx; 
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
    wcx.cbSize = sizeof(wcx);           // size of structure 
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // redraw if size changes 
    wcx.lpfnWndProc = WinProc;          // points to window procedure 
    wcx.cbClsExtra = 0;                 // no extra class memory 
    wcx.cbWndExtra = 0;                 // no extra window memory 
    wcx.hInstance = hInstance;          // handle to instance 
    wcx.hIcon = NULL; 
    wcx.hCursor = LoadCursor(NULL,IDC_ARROW);   // predefined arrow 
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background 
    wcx.lpszMenuName =  NULL;           // name of menu resource 
    wcx.lpszClassName = CLASS_NAME;     // name of window class 
    wcx.hIconSm = NULL;                 // small class icon 
 
    if (RegisterClassEx(&wcx) == 0)    // if error
        return false;

    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPEDWINDOW;

    hwnd = CreateWindow(
        CLASS_NAME,             // name of the window class
        GAME_TITLE,             // title bar text
        style,                  // window style
        CW_USEDEFAULT,          // default horizontal position of window
        CW_USEDEFAULT,          // default vertical position of window
        GAME_WIDTH,             // width of window
        GAME_HEIGHT,            // height of the window
        (HWND) NULL,            // no parent window
        (HMENU) NULL,           // no menu
        hInstance,              // handle to application instance
        (LPVOID) NULL);         // no window parameters


    if (!hwnd)
        return false;

    if(!FULLSCREEN)             // if window
    {
        // Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);   // get size of client area of window
        MoveWindow(hwnd,
                   0,                                           // Left
                   0,                                           // Top
                   GAME_WIDTH+(GAME_WIDTH-clientRect.right),    // Right
                   GAME_HEIGHT+(GAME_HEIGHT-clientRect.bottom), // Bottom
                   TRUE);                                       // Repaint the window
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    return true;
}


