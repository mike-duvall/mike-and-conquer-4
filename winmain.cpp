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


http_listener * gdiMinigunnerListener;
http_listener * nodMinigunnerListener;
http_listener * leftClickListener;


Game *game = NULL;



//* Try running game on other boxA, full screen, with test running on boxB,
//so setting mouse location will work correctly
//Will have to update localhost to actual IP address of boxA

// LeftClick function
void LeftClick()
{
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}

// MouseMove function
void MouseMove(int x, int y)
{
	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);
	INPUT  Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (LONG)fx;
	Input.mi.dy = (LONG)fy;
	::SendInput(1, &Input, sizeof(INPUT));
}



void handlePostGdiMinigunner(http_request message) {
	pplx::task<json::value> jsonValue = message.extract_json();
	web::json::value webJsonValue = jsonValue.get();
	web::json::object object = webJsonValue.as_object();

	int minigunnerX = -666;
	int minigunnerY = -666;
	    
	for (auto iter = object.cbegin(); iter != object.cend(); ++iter) {
		utility::string_t attributeName = iter->first;
		//const json::value &str = iter->first;
		const json::value &v = iter->second;

		if (attributeName == L"x") {
			minigunnerX = v.as_integer();
		}

		if (attributeName == L"y") {
			minigunnerY = v.as_integer();
		}
	}

	game->AddCreateGDIMinigunnerEvent(minigunnerX, minigunnerY);
	// TODO:  update this to return the created minigunner as JSON, instead of result message
    message.reply(status_codes::OK, U("Initialized minigunner"));
};

//Next steps
//* Add eventing to handle creating Nod minigunner
//* Add eventing to handle reading of Nod minigunner
//* Test debugging remotely

void handlePostNodMinigunner(http_request message) {
	pplx::task<json::value> jsonValue = message.extract_json();
	web::json::value webJsonValue = jsonValue.get();
	web::json::object object = webJsonValue.as_object();

	int minigunnerX = -666;
	int minigunnerY = -666;

	for (auto iter = object.cbegin(); iter != object.cend(); ++iter) {
		utility::string_t attributeName = iter->first;
		//const json::value &str = iter->first;
		const json::value &v = iter->second;

		if (attributeName == L"x") {
			minigunnerX = v.as_integer();
		}

		if (attributeName == L"y") {
			minigunnerY = v.as_integer();
		}
	}

//	game->InitializeNODMinigunner(minigunnerX, minigunnerY);
	game->AddCreateNODMinigunnerEvent(minigunnerX, minigunnerY);
	// TODO:  update this to return the created minigunner as JSON, instead of result message
	message.reply(status_codes::OK, U("Initialized minigunner"));
};




void handleGetGdiMinigunner(http_request message) {

	Minigunner * gdiMinigunner = game->GetGDIMinigunnerViaEvent();

	json::value obj;
	obj[L"x"] = json::value::number(game->getGDIMinigunner1X());
	obj[L"y"] = json::value::number(game->getGDIMinigunner1Y());
	message.reply(status_codes::OK, obj);
};

void handleGetNodMinigunner(http_request message) {
	json::value obj;
	obj[L"x"] = json::value::number(game->getNODMinigunner1X());
	obj[L"y"] = json::value::number(game->getNODMinigunner1Y());
	message.reply(status_codes::OK, obj);
};


void handlePOSTLeftClick(http_request message) {
	pplx::task<json::value> jsonValue = message.extract_json();
	web::json::value webJsonValue = jsonValue.get();
	web::json::object object = webJsonValue.as_object();

	int mouseX = -666;
	int mouseY = -666;

	for (auto iter = object.cbegin(); iter != object.cend(); ++iter) {
		utility::string_t attributeName = iter->first;
		//const json::value &str = iter->first;
		const json::value &v = iter->second;

		if (attributeName == L"x") {
			mouseX = v.as_integer();
		}

		if (attributeName == L"y") {
			mouseY = v.as_integer();
		}
	}

	MouseMove(mouseX, mouseY);
	LeftClick();
	message.reply(status_codes::OK, U("Success"));
};


//Next:
//*Get remote debugging going, app running on one box, test running on another
//	* See if can configure so that don't have to run as admin in order to open the port
//		See here: https://casablanca.codeplex.com/discussions/532385
//		Maybe HttpCfg or netsh
//	* Don't hard code IP address, try just * or no host, etc




// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int); 
bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM); 


void init_input(HWND hWnd);

HWND hwnd = NULL;

//std::wstring baseUrl = L"http://192.168.0.179:11369";
std::wstring baseUrl = L"http://*:11369";

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

		std::wstring gdiMinigunnerURL = baseUrl + L"/gdiMinigunner";
		gdiMinigunnerListener = new http_listener(gdiMinigunnerURL);
		gdiMinigunnerListener->open().wait();
		gdiMinigunnerListener->support(methods::POST, handlePostGdiMinigunner);
		gdiMinigunnerListener->support(methods::GET, handleGetGdiMinigunner);


		std::wstring nodMinigunnerURL = baseUrl + L"/nodMinigunner";
		nodMinigunnerListener = new http_listener(nodMinigunnerURL);
		nodMinigunnerListener->open().wait();
		nodMinigunnerListener->support(methods::POST, handlePostNodMinigunner);
		nodMinigunnerListener->support(methods::GET, handleGetNodMinigunner);

		std::wstring leftClickURL = baseUrl + L"/leftClick";
		leftClickListener = new http_listener(leftClickURL);
		leftClickListener->open().wait();
		leftClickListener->support(methods::POST, handlePOSTLeftClick);

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


