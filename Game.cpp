#include "game.h"


#include "gameobject/Minigunner.h"
#include "gameobject/UnitSelectCursor.h"
#include "gameobject/Circle.h"
#include "gameevent/AsyncGameEvent.h"
#include "gameevent/GetGDIMinigunnerByIdGameEvent.h"
#include "gameevent/GetNodMinigunnerByIdGameEvent.h"
#include "gameevent/GetNODMinigunnerGameEvent.h"
#include "gameevent/GetAllGDIMinigunnersGameEvent.h"
#include "gameevent/GetAllNodMinigunnersGameEvent.h"


#include "gameevent/CreateGDIMinigunnerGameEvent.h"
#include "gameevent/GetGdiMinigunnerAtLocationGameEvent.h"
#include "gameevent/GetNodMinigunnerAtLocationGameEvent.h"
#include "gameevent/CreateNODMinigunnerGameEvent.h"
#include "GdiShpFileColorMapper.h"
#include "NodShpFileColorMapper.h"
#include "gamestate/PlayingGameState.h"
#include "gameevent/ResetGameGameEvent.h"


Game::Game(bool testMode) {
    input = new Input();
    graphics = nullptr;
    initialized = false;
	this->testMode = testMode;
}


void Game::Initialize(HWND hw) {
	hwnd = hw;                                  // save window handle

	graphics = new Graphics();
	graphics->Initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);


	// attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);        // get starting time

	unitSelectCursor = new UnitSelectCursor(this->GetGraphics());

	circle = nullptr;

	gdiShpFileColorMapper = new GdiShpFileColorMapper();
	nodShpFileColorMapper = new NodShpFileColorMapper();

	//shpImageExplorer = new ShpImageExplorer(this, 100, 100, input);
	shpImageExplorer = nullptr;

	currentGameState = ResetGame();
}



void Game::DeleteAndClearGdiMinigunners() {
	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners.begin(); iter != gdiMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		delete nextMinigunner;
	}
	gdiMinigunners.clear();
}


void Game::DeleteAndClearNodMinigunners() {
	std::vector<Minigunner *>::iterator iter;
	for (iter = nodMinigunners.begin(); iter != nodMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		delete nextMinigunner;
	}
	nodMinigunners.clear();
}


GameState * Game::ResetGame() {
	initialized = false;

	DeleteAndClearGdiMinigunners();
	DeleteAndClearNodMinigunners();


	delete circle;

	if (!testMode) {
		Minigunner * gdiMinigunner = new Minigunner(this, 300, 900, unitSelectCursor, input, false, gdiShpFileColorMapper);
		gdiMinigunners.push_back(gdiMinigunner);

		Minigunner * nodMinigunner = new Minigunner(this, 1000, 300, unitSelectCursor, input, true, nodShpFileColorMapper);
		nodMinigunners.push_back(gdiMinigunner);
	}

	circle = new Circle(300, 900);

	initialized = true;
	return new PlayingGameState(*this);
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
		input->MousePosition(mousePos.x, mousePos.y);

		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN) {
			input->LeftMouseDown();
		}
		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP) {
			input->LeftMouseUp();
		}

		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN) {
			input->RightMouseDown();

		}
		if (inputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP) {
			input->RightMouseUp();
		}

	}

}


void Game::SelectSingleGDIUnit(Minigunner * gdiMinigunner) {

	gdiMinigunner->SetSelected(true);

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners.begin(); iter != gdiMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner != gdiMinigunner) {
			nextMinigunner->SetSelected(false);
		}
	}

}


Minigunner * Game::GetGDIMinigunnerAtPoint(int x, int y) {

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners.begin(); iter != gdiMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if(nextMinigunner->PointIsWithin(x,y)) {
			return nextMinigunner;
		}
	}

	return nullptr;
}





Minigunner * Game::CreateGDIMinigunnerViaEvent(int x, int y) {
	CreateGDIMinigunnerGameEvent * gameEvent = new CreateGDIMinigunnerGameEvent(this, x, y);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
    return gdiMinigunner;
}

Minigunner * Game::CreateNodMinigunnerViaEvent(int x, int y) {
	CreateNODMinigunnerGameEvent * gameEvent = new CreateNODMinigunnerGameEvent(this, x, y);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}


Minigunner * Game::GetGdiMinigunnerAtLocationViaEvent(int x, int y) {
	GetGdiMinigunnerAtLocationGameEvent * gameEvent = new GetGdiMinigunnerAtLocationGameEvent(this, x, y );
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}


Minigunner * Game::GetNodMinigunnerAtLocationViaEvent(int x, int y) {
	GetNodMinigunnerAtLocationGameEvent * gameEvent = new GetNodMinigunnerAtLocationGameEvent(this, x, y);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}



Minigunner * Game::GetGDIMinigunnerByIdViaEvent(int id) {
	GetGDIMinigunnerByIdGameEvent * gameEvent = new GetGDIMinigunnerByIdGameEvent(this, id);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}


Minigunner * Game::GetNodMinigunnerByIdViaEvent(int id) {
	GetNodMinigunnerByIdGameEvent * gameEvent = new GetNodMinigunnerByIdGameEvent(this, id);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}


std::vector<Minigunner * > * Game::GetAllGDIMinigunnersViaEvent() {
	GetAllGDIMinigunnersGameEvent * gameEvent = new GetAllGDIMinigunnersGameEvent(this);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	return gameEvent->GetAllGdiMinigunners();
}

std::vector<Minigunner * > * Game::GetAllNodMinigunnersViaEvent() {
	GetAllNodMinigunnersGameEvent * gameEvent = new GetAllNodMinigunnersGameEvent(this);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	return gameEvent->GetAllNodMinigunners();
}


Minigunner * Game::GetNODMinigunnerViaEvent() {
	GetNODMinigunnerGameEvent * gameEvent = new GetNODMinigunnerGameEvent(this);
	std::unique_lock<std::mutex> lock(gameEventsMutex);
	gameEvents.push_back(gameEvent);
	lock.unlock();
	Minigunner * gdiMinigunner = gameEvent->GetMinigunner();
	return gdiMinigunner;
}



Minigunner * Game::InitializeGDIMinigunner(int minigunnerX, int minigunnerY) {
	bool isEnemy = false;
	Minigunner * minigunner = new Minigunner(this, minigunnerX, minigunnerY, unitSelectCursor, input, isEnemy, gdiShpFileColorMapper);
	gdiMinigunners.push_back(minigunner);
	return minigunner;
}


Minigunner * Game::InitializeNODMinigunner(int minigunnerX, int minigunnerY) {
	bool isEnemy = true;
	Minigunner * nodMinigunner = new Minigunner(this, minigunnerX, minigunnerY, unitSelectCursor, input, isEnemy, nodShpFileColorMapper);
	nodMinigunners.push_back(nodMinigunner);
	return nodMinigunner;

}




void Game::AddResetGameEvent() {
	AsyncGameEvent * gameEvent = new ResetGameGameEvent(this);
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
                input->KeyDown(wParam);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:        // key up
                input->KeyUp(wParam);
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



GameState * Game::ProcessGameEvents() {
	GameState * newGameState = nullptr;

	std::vector<AsyncGameEvent *>::iterator iter;
	std::lock_guard<std::mutex> lock(gameEventsMutex);
	for (iter = gameEvents.begin(); iter != gameEvents.end(); ++iter) {
		AsyncGameEvent * nextGameEvent = *iter;
		GameState * returnedGameState = nextGameEvent->Process();
		if( returnedGameState != nullptr && newGameState == nullptr) {
			newGameState = returnedGameState;
		}
	}
	gameEvents.clear();
	return newGameState;

}



void Game::ExecuteGameCycle() {
	if(!initialized) {
		return;
	}

    // calculate elapsed time of last frame, save in frameTime
    QueryPerformanceCounter(&timeEnd);
    frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart ) / (float)timerFreq.QuadPart;


    if (frameTime > MAX_FRAME_TIME) // if frame rate is very slow
        frameTime = MAX_FRAME_TIME; // limit maximum frameTime
    timeStart = timeEnd;

    //GameState * newGameState = Update(); 
    //RenderGame(); 

	currentGameState = currentGameState->Update(frameTime);

    if (input->IsKeyDown(ESC_KEY))
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