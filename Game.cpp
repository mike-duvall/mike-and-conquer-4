
#include "game.h"

#include "Minigunner.h"
#include "UnitSelectCursor.h"
#include "Circle.h"
#include "MikeRectangle.h"
#include "GameEvent.h"
#include "GetGDIMinigunnerGameEvent.h"
#include "GetNODMinigunnerGameEvent.h"
#include "CreateGDIMinigunnerGameEvent.h"
#include "CreateNODMinigunnerGameEvent.h"



Game::Game(bool testMode) {
    input = new Input();
    graphics = NULL;
    initialized = false;
	this->testMode = testMode;
}

Game::~Game() {
	ReleaseAll();
    DeleteAll();                // free all reserved memory
    ShowCursor(true);           // show cursor
}




void Game::HandleMouseInput(LPARAM lParam) {
	RAWINPUT inputData;

	UINT DataSize = sizeof(RAWINPUT);
	GetRawInputData((HRAWINPUT)lParam,
		RID_INPUT,
		&inputData,
		&DataSize,
		sizeof(RAWINPUTHEADER));

	// set the mouse button status

	if (inputData.header.dwType == RIM_TYPEMOUSE) {

		POINT mousePos;
		GetCursorPos(&mousePos);
		input->mousePosition(mousePos.x, mousePos.y);

		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN) {
			input->leftMouseDown();
		}
		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP) {
			input->leftMouseUp();
		}

		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN) {
			input->rightMouseDown();

		}
		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP) {
			input->rightMouseUp();
		}

	}

}


LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

void init_graphics(Graphics * graphics)
{
	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] =
	{
		{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
	};

	// create a vertex buffer interface called v_buffer

	LPDIRECT3DDEVICE9 d3ddev = graphics->Get3Ddevice();
	d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

					// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
}


void Game::Initialize(HWND hw) {
	hwnd = hw;                                  // save window handle

	graphics = new Graphics();
	graphics->Initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);


	// attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);        // get starting time

	initialized = true;


	unitSelectCursor = new UnitSelectCursor(this->GetGraphics());

	minigunner1 = NULL;
	enemyMinigunner1 = NULL;

	if (!testMode) {
		minigunner1 = new Minigunner(this, this->GetGraphics(), 300, 900, unitSelectCursor, input, false);
		enemyMinigunner1 = new Minigunner(this, this->GetGraphics(), 1000, 300, unitSelectCursor, input, true);
	}

	circle = new Circle(500, 500);
	rectangle = new MikeRectangle(-1,-1);

	init_graphics(this->GetGraphics());
}



Minigunner * Game::GetMinigunnerAtPoint(int x, int y) {
	if (minigunner1->pointIsWithin(x, y)) {
		return minigunner1;
	}
	else if (enemyMinigunner1 != NULL && enemyMinigunner1->pointIsWithin(x, y)) {
		return enemyMinigunner1;
	}
	else {
		return NULL;
	}
}

void Game::InitializeStuff() {
	minigunner1 = new Minigunner(this, this->GetGraphics(), 300, 900, unitSelectCursor, input, false);
	enemyMinigunner1 = new Minigunner(this, this->GetGraphics(), 1000, 300, unitSelectCursor, input, true);
}

void Game::InitializeGDIMinigunner(int minigunnerX, int minigunnerY) {
	bool isEnemy = false;
	minigunner1 = new Minigunner(this, this->GetGraphics(), minigunnerX, minigunnerY, unitSelectCursor, input, isEnemy);
}

void Game::AddCreateGDIMinigunnerEvent(int x, int y) {
	GameEvent * gameEvent = new CreateGDIMinigunnerGameEvent(this, x, y);
	std::lock_guard<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
}


Minigunner * Game::GetGDIMinigunnerViaEvent() {
	GetGDIMinigunnerGameEvent * gameEvent = new GetGDIMinigunnerGameEvent(this);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}

Minigunner * Game::GetNODMinigunnerViaEvent() {
	GetNODMinigunnerGameEvent * gameEvent = new GetNODMinigunnerGameEvent(this);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}



void Game::InitializeNODMinigunner(int minigunnerX, int minigunnerY) {
	bool isEnemy = true;
	enemyMinigunner1 = new Minigunner(this, this->GetGraphics(), minigunnerX, minigunnerY, unitSelectCursor, input, isEnemy);
}

void Game::AddCreateNODMinigunnerEvent(int x, int y) {
	GameEvent * gameEvent = new CreateNODMinigunnerGameEvent(this, x, y);
	std::lock_guard<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
}



LRESULT Game::MessageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
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
				HandleMouseInput(lParam);
				return 0;
			} break;

        }
    }
    return DefWindowProc( hwnd, msg, wParam, lParam );    // let Windows handle it
}



void Game::ProcessGameEvents() {
	std::vector<GameEvent *>::iterator iter;
	std::lock_guard<std::mutex> lock(gameEventsMutex);
	for (iter = gameEvents.begin(); iter != gameEvents.end(); ++iter) {
		GameEvent * nextGameEvent = *iter;
		nextGameEvent->Process();
	}
	gameEvents.clear();

}

void Game::Update() {

	ProcessGameEvents();
	if (minigunner1 != NULL) {
		minigunner1->update(frameTime);
	}
	if (enemyMinigunner1 != NULL) {
		enemyMinigunner1->update(frameTime);
	}
	if (input->isLeftMouseDown()) {
		circle->SetX(input->getMouseX());
		circle->SetY(input->getMouseY());
	}

}


void Game::Render() {
//	graphics->spriteBegin();                // begin drawing sprites
	if (minigunner1 != NULL) {
		minigunner1->draw();
	}

	if (enemyMinigunner1 != NULL) {
		if (enemyMinigunner1->GetHealth() > 0) {
			enemyMinigunner1->draw();
		}
	}

	circle->Draw(graphics->Get3Ddevice());
	rectangle->Draw(graphics->Get3Ddevice());
//	graphics->spriteEnd();                  // end drawing sprites

}


void Game::RenderGame() {
    if (SUCCEEDED(graphics->BeginScene()))
    {
        Render();

		//////////////////////////////////////////////////
		// SET UP THE PIPELINE

		D3DXMATRIX matRotateY;    // a matrix to store the rotation information

		static float index = 0.0f;// index += 0.05f;    // an ever-increasing float value

		LPDIRECT3DDEVICE9 d3ddev = graphics->Get3Ddevice();
		d3ddev->SetFVF(CUSTOMFVF);
													  // build a matrix to rotate the model based on the increasing float value
		D3DXMatrixRotationY(&matRotateY, index);

		// tell Direct3D about our matrix
		d3ddev->SetTransform(D3DTS_WORLD, &matRotateY);

		D3DXMATRIX matView;    // the view transform matrix

		D3DXMatrixLookAtLH(&matView,
			&D3DXVECTOR3(0.0f, 0.0f, 10.0f),    // the camera position
			&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
			&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

		d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

		D3DXMATRIX matProjection;     // the projection transform matrix

		D3DXMatrixPerspectiveFovLH(&matProjection,
			D3DXToRadian(45),    // the horizontal field of view
			(FLOAT)GAME_WIDTH / (FLOAT)GAME_HEIGHT, // aspect ratio
			1.0f,    // the near view-plane
			100.0f);    // the far view-plane

		d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection
																   // select the vertex buffer to display
		d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

		// copy the vertex buffer to the back buffer
		d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);


		//////////////////////////////////////////////////



        graphics->endScene();
    }

    graphics->ShowBackbuffer();


}

void Game::Run(HWND hwnd) {
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

    Update(); 
    RenderGame(); 

    if (input->isKeyDown(ESC_KEY))
		PostQuitMessage(0);

}



void Game::ReleaseAll() {
//	gameTextures.onLostDevice();
	return;
}

void Game::ResetAll() {
//	gameTextures.onResetDevice();
	return;
}



void Game::DeleteAll() {
    ReleaseAll();               // call onLostDevice() for every graphics item
    safeDelete(graphics);
    safeDelete(input);
    initialized = false;
}