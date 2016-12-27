#include "input.h"



//Clean up mouse code
//Have clicking the minigunner select him
//click elsewhere delsects? 
//Then left click to move to position


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



void Input::keyDown(WPARAM wParam)
{
    // make sure key code is within buffer range
    if (wParam < inputNS::KEYS_ARRAY_LEN)
    {
        keysDown[wParam] = true;    // update keysDown array
        // key has been "pressed, erased by clear()
        keysPressed[wParam] = true; // update keysPressed array
    }
}

void Input::keyUp(WPARAM wParam)
{
    // make sure key code is within buffer range
    if (wParam < inputNS::KEYS_ARRAY_LEN)
        // update state table
        keysDown[wParam] = false;
}


bool Input::isKeyDown(UCHAR vkey) const
{
    if (vkey < inputNS::KEYS_ARRAY_LEN)
        return keysDown[vkey];
    else
        return false;
}

void Input::leftMouseDown()
{
	leftMouseButtonDown = true;
}

void Input::leftMouseUp()
{
	leftMouseButtonDown = false;
}

void Input::rightMouseDown()
{
	rightMouseButtonDown = true;
}

void Input::rightMouseUp()
{
	rightMouseButtonDown = false;
}


void Input::mousePosition(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;
}


