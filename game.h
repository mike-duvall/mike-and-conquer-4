#pragma once

#define WIN32_LEAN_AND_MEAN

class Game;

#include <windows.h>
#include <Mmsystem.h>

#include <vector>
#include <mutex>

#include "graphics.h"
#include "input.h"

#include "constants.h"
#include "gameError.h"



class Minigunner;
class UnitSelectCursor;
class Circle;
class GameEvent;


class Game
{

public:
    Game(bool testMode);
    virtual ~Game();

    LRESULT messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

    virtual void initialize(HWND hwnd);

    virtual void run(HWND);

    virtual void releaseAll();
    virtual void resetAll();
    virtual void deleteAll();
    virtual void renderGame();
	void ProcessGameEvents();
	virtual void update();
	virtual void render();

	Minigunner * getMinigunnerAtPoint(int x, int y);

    Graphics* getGraphics() {return graphics;}
    Input* getInput()       {return input;}
    void exitGame()         {PostMessage(hwnd, WM_DESTROY, 0, 0);}
	void InitializeStuff();
	void InitializeGDIMinigunner(int minigunnerX, int minigunnerY);
	void InitializeNODMinigunner(int minigunnerX, int minigunnerY);
	int getGDIMinigunner1X(); 
	int getGDIMinigunner1Y(); 
	int getNODMinigunner1X();
	int getNODMinigunner1Y();
	void AddCreateGDIMinigunnerEvent(int x, int y);
	void AddCreateNODMinigunnerEvent(int x, int y);
	Minigunner * GetGDIMinigunnerViaEvent();
	Minigunner * GetGDIMinigunner() { return minigunner1;  }

protected:

	std::vector<GameEvent *> gameEvents;
	std::mutex gameEventsMutex;

	Graphics *graphics;             // pointer to the one and ONLY Graphics object
	Input   *input;                 // pointer to Input

	boolean testMode;

	Minigunner  * minigunner1;
	Minigunner  * enemyMinigunner1;
	UnitSelectCursor * unitSelectCursor;
	Circle * circle;


	HWND    hwnd;                   // window handle
	HRESULT hr;                     // standard return type
	LARGE_INTEGER timeStart;        // Performance Counter start value
	LARGE_INTEGER timeEnd;          // Performance Counter end value
	LARGE_INTEGER timerFreq;        // Performance Counter frequency
	float   frameTime;              // time required for last frame
	DWORD   sleepTime;              // number of milli-seconds to sleep between frames
	bool    initialized;



	void HandleMouseInput(LPARAM lParam);



};


