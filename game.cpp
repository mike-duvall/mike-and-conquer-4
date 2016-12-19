
#include "game.h"

#include "Minigunner.h"
#include "UnitSelectCursor.h"

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

	mushroom1 = new Minigunner(this->getGraphics());

	unitSelectCursor = new UnitSelectCursor(this->getGraphics());


}

void Game::update()
{
	mushroom1->update(frameTime);
	//mushroom2->update(frameTime);
	unitSelectCursor->update(frameTime);
}



void Game::render()
{
//	graphics->spriteBegin();                // begin drawing sprites
	mushroom1->draw();
	//mushroom2->draw();
	unitSelectCursor->draw();
//	graphics->spriteEnd();                  // end drawing sprites

}


void Game::renderGame()
{
    if (SUCCEEDED(graphics->beginScene()))
    {
        render();           // call render() in derived object
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