
#include "game.h"

#include "Minigunner.h"
#include "UnitSelectCursor.h"


static int circleX = 200;
static int circleY = 200;

static const int CIRCLE_RESOLUTION = 64;

struct VERTEX_2D_DIF { // transformed colorized
	float x, y, z, rhw;
	D3DCOLOR color;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

void DrawCircleFilled(LPDIRECT3DDEVICE9 device, float mx, float my, float r, D3DCOLOR color)
{
	VERTEX_2D_DIF verts[CIRCLE_RESOLUTION + 1];

	for (int i = 0; i < CIRCLE_RESOLUTION + 1; i++)
	{
		verts[i].x = mx + r*cos(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
		verts[i].y = my + r*sin(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
		verts[i].z = 0;
		verts[i].rhw = 1;
		verts[i].color = color;
	}

	device->SetFVF(VERTEX_2D_DIF::FVF);
	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_RESOLUTION - 1, &verts, sizeof(VERTEX_2D_DIF));
}



Game::Game()
{
    input = new Input();
    graphics = NULL;
    initialized = false;
}

Game::~Game()
{
	releaseAll();
    deleteAll();                // free all reserved memory
    ShowCursor(true);           // show cursor
}



LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    if(initialized)     // do not process messages if not initialized
    {
        switch( msg )
        {
            case WM_DESTROY:
                PostQuitMessage(0);        //tell Windows to kill this program
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:    // key down
                input->keyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // key up
                input->keyUp(wParam);
                return 0;

			case WM_INPUT:
			{
				RAWINPUT inputData;

				UINT DataSize = sizeof(RAWINPUT);
				GetRawInputData((HRAWINPUT)lParam,
					RID_INPUT,
					&inputData,
					&DataSize,
					sizeof(RAWINPUTHEADER));

				// set the mouse button status

				if (inputData.header.dwType == RIM_TYPEMOUSE) {


					static BOOL MouseDown;
					if (inputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN) {
						input->leftMouseDown();
						POINT mousePos;
						GetCursorPos(&mousePos);
						circleX = mousePos.x;
						circleY = mousePos.y;

					}
					if (inputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP) {
						input->leftMouseUp();
					}

					
					input->mousePosition(inputData.data.mouse.lLastX, inputData.data.mouse.lLastY);



				}



				return 0;
			} break;

        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // let Windows handle it
}

void Game::initialize(HWND hw)
{
    hwnd = hw;                                  // save window handle

    graphics = new Graphics();
    graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);


    // attempt to set up high resolution timer
    if(QueryPerformanceFrequency(&timerFreq) == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

    QueryPerformanceCounter(&timeStart);        // get starting time

    initialized = true;

	unitSelectCursor = new UnitSelectCursor(this->getGraphics());
	minigunner1 = new Minigunner(this->getGraphics(), unitSelectCursor);




}

void Game::update()
{
	minigunner1->update(frameTime);
	//mushroom2->update(frameTime);
	unitSelectCursor->update(frameTime);
}




void Game::render()
{
//	graphics->spriteBegin();                // begin drawing sprites
	minigunner1->draw();
	//mushroom2->draw();
	//unitSelectCursor->draw();
//	graphics->spriteEnd();                  // end drawing sprites

}


void Game::renderGame()
{
    if (SUCCEEDED(graphics->beginScene()))
    {
        render();
		DrawCircleFilled(graphics->get3Ddevice(), circleX, circleY,  20, graphicsNS::MAGENTA);
        graphics->endScene();
    }

    graphics->showBackbuffer();
}

void Game::run(HWND hwnd)
{
    if(graphics == NULL)            // if graphics not initialized
        return;

    // calculate elapsed time of last frame, save in frameTime
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / (float)timerFreq.QuadPart;

    //// Power saving code, requires winmm.lib
    //// if not enough time has elapsed for desired frame rate
    //if (frameTime < MIN_FRAME_TIME) 
    //{
    //    sleepTime = (DWORD)((MIN_FRAME_TIME - frameTime)*1000);
    //    timeBeginPeriod(1);         // Request 1mS resolution for windows timer
    //    Sleep(sleepTime);           // release cpu for sleepTime
    //    timeEndPeriod(1);           // End 1mS timer resolution
    //    return;
    //}

    if (frameTime > MAX_FRAME_TIME) // if frame rate is very slow
        frameTime = MAX_FRAME_TIME; // limit maximum frameTime
    timeStart = timeEnd;

    update(); 
    renderGame(); 

    if (input->isKeyDown(ESC_KEY))
		PostQuitMessage(0);

}



void Game::releaseAll()
{
//	gameTextures.onLostDevice();
	return;
}

void Game::resetAll()
{
//	gameTextures.onResetDevice();
	return;
}



void Game::deleteAll()
{
    releaseAll();               // call onLostDevice() for every graphics item
    safeDelete(graphics);
    safeDelete(input);
    initialized = false;
}