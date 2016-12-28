#include "Minigunner.h"

#include "graphics.h"
#include "GameSprite.h"
#include "UnitSelectCursor.h"
#include "input.h"
#include "game.h"

const std::string IMAGE_FILE = "pictures\\m3.png";  // game textures



Minigunner::Minigunner(Game * game, Graphics * graphics, int x, int y, UnitSelectCursor * unitSelectCursor, Input * input, bool isEnemy)
{
	this->state = "IDLE";
	this->game = game;
	this->graphics = graphics;
	this->input = input;
	this->isSelected = false;
	this->unitSelectCursor = unitSelectCursor;
	this->isEnemy = isEnemy;
	this->x = (float)x;
	this->y = (float)y;
	this->destinationX = int(this->x);
	this->destinationY = int(this->y);

	//velocity.x = 300.0;
	//velocity.y = 300.0;
	velocity.x = 150.0;
	velocity.y = 150.0;

	gameSprite = new GameSprite(graphics->get3Ddevice(), IMAGE_FILE, this->width, this->height, graphicsNS::WHITE);
}


Minigunner::~Minigunner()
{
}


void Minigunner::MoveTo(int x, int y) {
	this->destinationX = x;
	this->destinationY = y;
}

void Minigunner::handleIdleState(float frameTime) {
	if (input->isLeftMouseDown()) {
		Minigunner * foundMinigunner = game->getMinigunnerAtPoint(input->getMouseX(), input->getMouseY());
		if (foundMinigunner != NULL) {
			if (foundMinigunner == this) {
				setSelected(true);
			}
			else {
				// It's the enemy
				state = "ATTACKING";
				enemyAttacking = foundMinigunner;
			}
		}
		else if (getIsSelected()) {
			state = "MOVING";
			MoveTo(input->getMouseX(), input->getMouseY());
		}

	}

}


void Minigunner::handleMovingState(float frameTime) {

	if (input->isLeftMouseDown()) {
		Minigunner * foundMinigunner = game->getMinigunnerAtPoint(input->getMouseX(), input->getMouseY());
		if (foundMinigunner != NULL) {
			if (foundMinigunner == this) {
				setSelected(true);
			}
			else {
				// It's the enemy
				state = "ATTACKING";
				enemyAttacking = foundMinigunner;
			}
		}
		else if (getIsSelected()) {
			state = "MOVING";
			MoveTo(input->getMouseX(), input->getMouseY());
		}

	}


	int buffer = 2;

	if (this->x < (this->destinationX - buffer)) {
		x += frameTime * velocity.x;
	}
	else if (this->x >(this->destinationX + buffer)) {
		x -= frameTime * velocity.x;
	}

	if (this->y < (this->destinationY - buffer)) {
		y += frameTime * velocity.y;
	}
	else if (this->y >(this->destinationY + buffer)) {
		y -= frameTime * velocity.y;
	}

}


void Minigunner::handleAttackingState(float frameTime) {

}


void Minigunner::update(float frameTime) {

	if (isEnemy) {
		return;
	}

	if (state == "IDLE") {
		handleIdleState(frameTime);
	}
	else if (state == "MOVING") {
		handleMovingState(frameTime);
	}
	else if (state == "ATTACKING") {
		handleAttackingState(frameTime);
	}

	if (input->isRightMouseDown()) {
		setSelected(false);
	}


	//int buffer = 2;

	//if (this->x < (this->destinationX - buffer)) {
	//	x += frameTime * velocity.x;
	//}
	//else if (this->x > (this->destinationX + buffer)) {
	//	x -= frameTime * velocity.x;
	//}
	//	
	//if (this->y < (this->destinationY - buffer)) {
	//	y += frameTime * velocity.y;
	//}
	//else if (this->y > (this->destinationY + buffer)) {
	//	y -= frameTime * velocity.y;
	//}


	//x += frameTime * velocity.x;
	//y += frameTime * velocity.y;

	//int boundingBoxWidth = 16 * 3;
	//int boundingBoxHeight = 16 * 3;

	//if ((x + boundingBoxWidth) > GAME_WIDTH)              // if off right screen edge
	//	velocity.x = -velocity.x;
	//else if (x - boundingBoxWidth < -WIDTH)     // else if off left screen edge
	//	velocity.x = -velocity.x;
	//if (y + boundingBoxHeight > GAME_HEIGHT)             // if off bottom screen edge
	//	velocity.y = -velocity.y;
	//else if (y - boundingBoxHeight < -HEIGHT)    // else if off top screen edge
	//	velocity.y = -velocity.y;
}

bool Minigunner::pointIsWithin(int x, int y)
{
	int scale = 4;
	int boundingBoxWidth = WIDTH * scale;
	int boundingBoxHeight = HEIGHT * scale;

	int boundingBoxLeftX = int(this->x - (boundingBoxWidth / 2));
	int boundingBoxRightX = int(this->x + (boundingBoxWidth / 2));
	int boundingBoxTopY = int(this->y - (boundingBoxHeight / 2));
	int boundingBoxBottomY = int(this->y + (boundingBoxHeight / 2));

	if (x >= boundingBoxLeftX &&
		x <= boundingBoxRightX &&
		y >= boundingBoxTopY &&
		y <= boundingBoxBottomY) {
		return true;
	}
	else {
		return false;
	}
}



void Minigunner::draw()
{
    if ( graphics == NULL)
        return;

	D3DXVECTOR2 position;

	int roundedX = (int) x;
	int roundexY = (int) y;

	position.x = (float)roundedX;
	position.y = (float)roundexY;
	gameSprite->Draw(0, position);

	if (isSelected) {
		unitSelectCursor->setX(position.x);
		unitSelectCursor->setY(position.y);
		unitSelectCursor->draw();
	}

}


