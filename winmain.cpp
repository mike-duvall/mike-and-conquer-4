#define _CRTDBG_MAP_ALLOC       // for detecting memory leaks
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>             // for detecting memory leaks
#include <crtdbg.h>             // for detecting memory leaks
#include "game.h"


#include <cpprest\http_listener.h>

using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;


http_listener *listener;
http_listener *listener2;

Game *game = NULL;


void handle_create_minigunner(http_request message) {
	//Make this a POST, make it read initial location and
	//	place only the minigunner

	//	May need to start making things threadsafe

	//	May need an 'initialize' phase followed by a 'run' phase
	//	but still will need to be able read things in a threadsafe manner

	pplx::task<json::value> jsonValue = message.extract_json();
	web::json::value webJsonValue = jsonValue.get();
	web::json::object object = webJsonValue.as_object();

	//webJsonValue.as_object().cbegin
	int minigunnerX = -666;
	int minigunnerY = -666;
	    
	for (auto iter = object.cbegin(); iter != object.cend(); ++iter)
	{
		// Make sure to get the value as const reference otherwise you will end up copying 
		// the whole JSON value recursively which can be expensive if it is a nested object. 
		utility::string_t t = iter->first;
		//const json::value &str = iter->first;
		const json::value &v = iter->second;

		if (t == L"x") {
			minigunnerX = v.as_integer();
		}

		if (t == L"y") {
			minigunnerY = v.as_integer();
		}

		// Perform actions here to process each string and value in the JSON object...
		//std::wcout << L"String: " << str.as_string() << L", Value: " << v.to_string() << endl;
		std::wcout << L"String: " << t << L", Value: " << v.to_string() << std::endl;
	}


//	game->InitializeStuff();
	game->InitialGDIMinigunner(minigunnerX, minigunnerY);
    message.reply(status_codes::OK, U("Initialized game"));
};




void handle_get_minigunner(http_request message) {

	json::value obj;

	
	obj[L"x"] = json::value::number(game->getMinigunner1X());
	obj[L"y"] = json::value::number(game->getMinigunner1Y());

	message.reply(status_codes::OK, obj);

};


// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 



void handle_create_minigunner(http_request message);

void init_input(HWND hWnd);

HWND hwnd = NULL;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    #if defined(DEBUG) | defined(_DEBUG)
        _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    MSG msg;

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
        game->initialize(hwnd);     // throws GameError
		init_input(hwnd);

		listener = new http_listener(L"http://localhost:11369/gdiMinigunner");
		listener->open().wait();
		listener->support(methods::POST, handle_create_minigunner);

		listener2 = new http_listener(L"http://localhost:11369/getMinigunner");
		listener2->open().wait();
		listener2->support(methods::GET, handle_get_minigunner);


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
                game->run(hwnd);    
        }
        safeDelete(game);          
        return msg.wParam;
    }
    catch(const GameError &err)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    }
    catch(...)
    {
        game->deleteAll();
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
    return (game->messageHandler(hwnd, msg, wParam, lParam));
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


