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
class MikeRectangle;
class GameEvent;
class ShpImageExplorer;
class GdiShpFileColorMapper;
class NodShpFileColorMapper;
class GameState;


class Game {

public:
    Game(bool testMode);
    virtual ~Game();

    LRESULT MessageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

    virtual void Initialize(HWND hwnd);

    virtual void ExecuteGameCycle();

    virtual void ReleaseAll();
    virtual void ResetAll();
    virtual void DeleteAll();
	GameState * ProcessGameEvents();

	Minigunner * GetMinigunnerAtPoint(int x, int y);
	Minigunner * GetGDIMinigunnerAtPoint(int x, int y);

    Graphics* GetGraphics() {return graphics;}
    Input* GetInput()       {return input;}
    void ExitGame()         {PostMessage(hwnd, WM_DESTROY, 0, 0);}
	Minigunner * InitializeGDIMinigunner(int minigunnerX, int minigunnerY);
	void InitializeNODMinigunner(int minigunnerX, int minigunnerY);

	std::vector<Minigunner * > * GetGDIMinigunners() { return &gdiMinigunners;  }
	Minigunner * GetNODMinigunner() { return enemyMinigunner1; }
	Circle * GetCircle() { return circle; }
	ShpImageExplorer * GetShpImageExplorer() { return shpImageExplorer; }
	GameState * GetCurrentGameState() { return currentGameState; }
	GameState * ResetGame();


	// Via Event handler
	Minigunner * CreateGDIMinigunnerViaEvent(int x, int y);
	void AddCreateNODMinigunnerEvent(int x, int y);
	void AddResetGameEvent();
	Minigunner * GetMinigunnerAtLocationViaEvent(int x, int y);
	Minigunner * GetGDIMinigunnerByIdViaEvent(int id);

	Minigunner * GetNODMinigunnerViaEvent();

	std::vector<Minigunner * > * Game::GetAllGDIMinigunnersViaEvent();
	void SelectSingleGDIUnit(Minigunner * gdiMinigunner);



protected:

	std::vector<GameEvent *> gameEvents;
	std::mutex gameEventsMutex;

	Graphics *graphics;             // pointer to the one and ONLY Graphics object
	Input   *input;                 // pointer to Input

	boolean testMode;

	std::vector<Minigunner *> gdiMinigunners;
	Minigunner  * enemyMinigunner1;
	UnitSelectCursor * unitSelectCursor;
	Circle * circle;
	ShpImageExplorer * shpImageExplorer;

	HWND    hwnd;                   // window handle
	HRESULT hr;                     // standard return type
	LARGE_INTEGER timeStart;        // Performance Counter start value
	LARGE_INTEGER timeEnd;          // Performance Counter end value
	LARGE_INTEGER timerFreq;        // Performance Counter frequency
	float   frameTime;              // time required for last frame
	DWORD   sleepTime;              // number of milli-seconds to sleep between frames

	bool    initialized;
	void HandleMouseInput(LPARAM lParam);

	GdiShpFileColorMapper * gdiShpFileColorMapper;
	NodShpFileColorMapper * nodShpFileColorMapper;


	GameState * currentGameState;


};


