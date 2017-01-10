
#include "game.h"

#include "Minigunner.h"
#include "UnitSelectCursor.h"
#include "Circle.h"




Game::Game(bool testMode) {
    input = new Input();
    graphics = NULL;
    initialized = false;
	this->testMode = testMode;
}

Game::~Game() {
	releaseAll();
    deleteAll();                // free all reserved memory
    ShowCursor(true);           // show cursor
}


int Game::getGDIMinigunner1X() {
	return minigunner1->getX();
}

int Game::getGDIMinigunner1Y() {
	return minigunner1->getY();
}

int Game::getNODMinigunner1X() {
	return enemyMinigunner1->getX();
}

int Game::getNODMinigunner1Y() {
	return enemyMinigunner1->getY();
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

void Game::initialize(HWND hw) {
	hwnd = hw;                                  // save window handle

	graphics = new Graphics();
	graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);


	// attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);        // get starting time

	initialized = true;


	unitSelectCursor = new UnitSelectCursor(this->getGraphics());

	minigunner1 = NULL;
	enemyMinigunner1 = NULL;

	if (!testMode) {
		minigunner1 = new Minigunner(this, this->getGraphics(), 300, 900, unitSelectCursor, input, false);
		enemyMinigunner1 = new Minigunner(this, this->getGraphics(), 1000, 300, unitSelectCursor, input, true);
	}

	circle = new Circle(500, 500);

}



Minigunner * Game::getMinigunnerAtPoint(int x, int y) {
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
	minigunner1 = new Minigunner(this, this->getGraphics(), 300, 900, unitSelectCursor, input, false);
	enemyMinigunner1 = new Minigunner(this, this->getGraphics(), 1000, 300, unitSelectCursor, input, true);
}

void Game::InitializeGDIMinigunner(int minigunnerX, int minigunnerY) {
	bool isEnemy = false;
	minigunner1 = new Minigunner(this, this->getGraphics(), minigunnerX, minigunnerY, unitSelectCursor, input, isEnemy);
}

void Game::InitializeNODMinigunner(int minigunnerX, int minigunnerY) {
	bool isEnemy = true;
	enemyMinigunner1 = new Minigunner(this, this->getGraphics(), minigunnerX, minigunnerY, unitSelectCursor, input, isEnemy);
}


LRESULT Game::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
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


void Game::update()
{
	if (minigunner1 != NULL) {
		minigunner1->update(frameTime);
	}
	if (enemyMinigunner1 != NULL) {
		enemyMinigunner1->update(frameTime);
	}
	if (input->isLeftMouseDown()) {
		circle->setX(input->getMouseX());
		circle->setY(input->getMouseY());
	}

}




void Game::render()
{
//	graphics->spriteBegin();                // begin drawing sprites
	if (minigunner1 != NULL) {
		minigunner1->draw();
	}

	if (enemyMinigunner1 != NULL) {
		if (enemyMinigunner1->getHealth() >= 0) {
			enemyMinigunner1->draw();
		}
	}

	circle->Draw(graphics->get3Ddevice());
//	graphics->spriteEnd();                  // end drawing sprites

}


void Game::renderGame()
{
    if (SUCCEEDED(graphics->beginScene()))
    {
        render();
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