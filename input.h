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
	void KeyDown(WPARAM);
	void KeyUp(WPARAM);
	bool IsKeyDown(UCHAR vkey) const;
	void LeftMouseDown();
	void LeftMouseUp();
	void RightMouseDown();
	void RightMouseUp();

	bool isLeftMouseDown() { return leftMouseButtonDown; }
	bool isRightMouseDown() { return rightMouseButtonDown; }
	void MousePosition(int x, int y);
	int getMouseX() { return mouseX;  }
	int getMouseY() { return mouseY; }

private:
    bool keysDown[inputNS::KEYS_ARRAY_LEN];     // true if specified key is down
    bool keysPressed[inputNS::KEYS_ARRAY_LEN];  // true if specified key was pressed
	bool leftMouseButtonDown;
	bool rightMouseButtonDown;
	int mouseX;
	int mouseY;

};



