#include "Minigunner.h"

#include "graphics.h"
#include "GameSprite.h"
#include "UnitSelectCursor.h"
#include "input.h"
#include "game.h"
#include "ShpFile.h"

const std::string IMAGE_FILE = "pictures\\m3.png";  // game textures



Minigunner::Minigunner(Game * game, Graphics * graphics, int x, int y, UnitSelectCursor * unitSelectCursor, Input * input, bool isEnemy)
{
	this->health = 1000;
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

	velocity.x = 150.0;
	velocity.y = 150.0;

	ShpFile shpFile(std::string("assets/e1.shp"));
	int imageIndex = 0;
	gameSprite = new GameSprite(graphics->Get3Ddevice(), shpFile, graphicsNS::WHITE, imageIndex);
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
		Minigunner * foundMinigunner = game->GetMinigunnerAtPoint(input->getMouseX(), input->getMouseY());
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

//xxx Figure out how to write a UI test to test the app behaviour
//
//Investigate these: 
//	* https://engineering.riotgames.com/news/automated-testing-league-legends
//	* https://blog.testfort.com/automated-testing/video-game-test-automation
//	* http ://www.gamasutra.com/view/feature/130682/automated_tests_and_continuous_.php

void Minigunner::moveTowardsDestination(float frameTime) {
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

void Minigunner::handleMovingState(float frameTime) {

	if (input->isLeftMouseDown()) {
		Minigunner * foundMinigunner = game->GetMinigunnerAtPoint(input->getMouseX(), input->getMouseY());
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

	moveTowardsDestination(frameTime);

}

double Distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

int Minigunner::calculateDistanceToTarget() {
	return (int)Distance(this->x, this->y, this->enemyAttacking->getX(), this->enemyAttacking->getY());
}

bool Minigunner::isInAttackRange() {
	int distanceToTarget = calculateDistanceToTarget();

	if (distanceToTarget < 200) {
		return true;
	}
	else {
		return false;
	}
}


void Minigunner::reduceHealth(int amount) {
	if (health > 0) {
		this->health -= amount;
	}
}

void Minigunner::handleAttackingState(float frameTime) {
	if (isInAttackRange()) {
		enemyAttacking->reduceHealth(10);
	}
	else {
		MoveTo(enemyAttacking->getX(), enemyAttacking->getY());
		moveTowardsDestination(frameTime);
	}


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


