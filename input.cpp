#include "input.h"

Input::Input()
{

	this->leftMouseButtonDown = false;
	this->rightMouseButtonDown = false;

    // clear key down array
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysDown[i] = false;
    // clear key pressed array
    for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
        keysPressed[i] = false;
}



void Input::KeyDown(WPARAM wParam)
{
    // make sure key code is within buffer range
    if (wParam < inputNS::KEYS_ARRAY_LEN)
    {
        keysDown[wParam] = true;    // update keysDown array
        // key has been "pressed, erased by clear()
        keysPressed[wParam] = true; // update keysPressed array
    }
}

void Input::KeyUp(WPARAM wParam)
{
    // make sure key code is within buffer range
    if (wParam < inputNS::KEYS_ARRAY_LEN)
        // update state table
        keysDown[wParam] = false;
}


bool Input::IsKeyDown(UCHAR vkey) const
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysDown[vkey];
    else
        return false;
}

void Input::LeftMouseDown()
{
	leftMouseButtonDown = true;
}

void Input::LeftMouseUp()
{
	leftMouseButtonDown = false;
}

void Input::RightMouseDown()
{
	rightMouseButtonDown = true;
}

void Input::RightMouseUp()
{
	rightMouseButtonDown = false;
}


void Input::MousePosition(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;
}


