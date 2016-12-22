#pragma once

#define WIN32_LEAN_AND_MEAN


#include <windows.h>
#include <string>
#include "constants.h"
#include "gameError.h"


namespace inputNS
{
    const int KEYS_ARRAY_LEN = 256;     // size of key arrays
    
    const UCHAR KEYS_DOWN = 1;
    const UCHAR KEYS_PRESSED = 2;
}


class Input
{

public:
	Input();
	void keyDown(WPARAM);
	void keyUp(WPARAM);
	bool isKeyDown(UCHAR vkey) const;
	void leftMouseDown();
	void leftMouseUp();
	void mousePosition(int x, int y);


private:
    bool keysDown[inputNS::KEYS_ARRAY_LEN];     // true if specified key is down
    bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // true if specified key was pressed
	bool leftMouseButtonDown;
	int mouseX;
	int mouseY;

};



