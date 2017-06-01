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
    virtual void RenderGame();
	void ProcessGameEvents();
	virtual GameState *  Update();

	Minigunner * GetMinigunnerAtPoint(int x, int y);

    Graphics* GetGraphics() {return graphics;}
    Input* GetInput()       {return input;}
    void ExitGame()         {PostMessage(hwnd, WM_DESTROY, 0, 0);}
	void InitializeGDIMinigunner(int minigunnerX, int minigunnerY);
	void InitializeNODMinigunner(int minigunnerX, int minigunnerY);
	void AddCreateGDIMinigunnerEvent(int x, int y);
	void AddCreateNODMinigunnerEvent(int x, int y);
	Minigunner * GetGDIMinigunnerViaEvent();
	Minigunner * GetNODMinigunnerViaEvent();
	Minigunner * GetGDIMinigunner() { return minigunner1;  }
	Minigunner * GetNODMinigunner() { return enemyMinigunner1; }
	Circle * GetCircle() { return circle; }
	ShpImageExplorer * GetShpImageExplorer() { return shpImageExplorer; }


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


