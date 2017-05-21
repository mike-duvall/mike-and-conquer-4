#include "Minigunner.h"

#include "graphics.h"
#include "GameSprite.h"
#include "UnitSelectCursor.h"
#include "input.h"
#include "game.h"
#include "ShpFile.h"
#include "MikeRectangle.h"



Minigunner::Minigunner(Game * game, int x, int y, UnitSelectCursor * unitSelectCursor, Input * input, bool isEnemy)
{
	this->health = 1000;
	this->state = "IDLE";
	this->game = game;
	this->graphics = game->GetGraphics();
	this->input = input;
	this->isSelected = false;
	this->unitSelectCursor = unitSelectCursor;
	this->isEnemy = isEnemy;
	this->x = x;
	this->y = y;
	this->destinationX = int(this->x);
	this->destinationY = int(this->y);

	velocity.x = 150.0;
	velocity.y = 150.0;

	ShpFile shpFile(std::string("assets/e1.shp"));
	int imageIndex = 4;
	boolean animate = true;
	gameSprite = new GameSprite(graphics->Get3Ddevice(), shpFile, graphicsNS::WHITE, animate, imageIndex);
	drawShpBoundingRectangle = false;
	shpBoundingRectangle = new MikeRectangle(x, y, gameSprite->GetWidth(), gameSprite->GetHeight());
	SetSelected(false);

}


Minigunner::~Minigunner()
{
}


void Minigunner::SetDestination(int x, int y) {
	this->destinationX = x;
	this->destinationY = y;
}

void Minigunner::HandleIdleState(float frameTime) {
	if (input->isLeftMouseDown()) {
		Minigunner * foundMinigunner = game->GetMinigunnerAtPoint(input->getMouseX(), input->getMouseY());
		if (foundMinigunner != NULL) {
			if (foundMinigunner == this) {
				SetSelected(true);
			}
			else if (GetIsSelected()) {
				// It's the enemy
				state = "ATTACKING";
				currentAttackTarget = foundMinigunner;
			}
		}
		else if (GetIsSelected()) {
			state = "MOVING";
			SetDestination(input->getMouseX(), input->getMouseY());
		}

	}

}


void Minigunner::MoveTowardsDestination(float frameTime) {
	int buffer = 2;

	if (this->x < (this->destinationX - buffer)) {
		x += (int)(frameTime * velocity.x);
	}
	else if (this->x >(this->destinationX + buffer)) {
		x -= (int)(frameTime * velocity.x);
	}

	if (this->y < (this->destinationY - buffer)) {
		y += (int) (frameTime * velocity.y);
	}
	else if (this->y >(this->destinationY + buffer)) {
		y -= (int) (frameTime * velocity.y);
	}

}

void Minigunner::HandleMovingState(float frameTime) {

	if (input->isLeftMouseDown()) {
		Minigunner * foundMinigunner = game->GetMinigunnerAtPoint(input->getMouseX(), input->getMouseY());
		if (foundMinigunner != NULL) {
			if (foundMinigunner == this) {
				SetSelected(true);
			}
			else {
				// It's the enemy
				state = "ATTACKING";
				currentAttackTarget = foundMinigunner;
			}
		}
		else if (GetIsSelected()) {
			state = "MOVING";
			SetDestination(input->getMouseX(), input->getMouseY());
		}

	}

	MoveTowardsDestination(frameTime);

}

double Distance(double dX0, double dY0, double dX1, double dY1)
{
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

int Minigunner::CalculateDistanceToTarget() {
	return (int)Distance(this->x, this->y, this->currentAttackTarget->GetX(), this->currentAttackTarget->GetY());
}

bool Minigunner::IsInAttackRange() {
	int distanceToTarget = CalculateDistanceToTarget();

	if (distanceToTarget < 200) {
		return true;
	}
	else {
		return false;
	}
}


void Minigunner::ReduceHealth(int amount) {
	if (health > 0) {
		this->health -= amount;
	}
}

void Minigunner::HandleAttackingState(float frameTime) {
	if (IsInAttackRange()) {
		currentAttackTarget->ReduceHealth(10);
	}
	else {
		SetDestination(currentAttackTarget->GetX(), currentAttackTarget->GetY());
		MoveTowardsDestination(frameTime);
	}


}


void Minigunner::Update(float frameTime) {

	if (isEnemy) {
		return;
	}

	if (state == "IDLE") {
		HandleIdleState(frameTime);
	}
	else if (state == "MOVING") {
		HandleMovingState(frameTime);
	}
	else if (state == "ATTACKING") {
		HandleAttackingState(frameTime);
	}

	if (input->isRightMouseDown()) {
		SetSelected(false);
	}

}

bool Minigunner::PointIsWithin(int x, int y)
{
	int scale = 4;
	int boundingBoxWidth = WIDTH * scale;
	int boundingBoxHeight = HEIGHT * scale;


	int yAdjustment = 14;
	int boundingBoxLeftX = int(this->x - (boundingBoxWidth / 2));
	int boundingBoxRightX = int(this->x + (boundingBoxWidth / 2));
	int boundingBoxTopY = int(this->y - yAdjustment - (boundingBoxHeight / 2));
	int boundingBoxBottomY = int(this->y - yAdjustment + (boundingBoxHeight / 2));

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



void Minigunner::Draw()
{
	gameSprite->Draw(0, x, y);

	if (isSelected) {
		unitSelectCursor->setX(x);
		unitSelectCursor->setY(y);
		unitSelectCursor->Draw();
	}

	if (drawShpBoundingRectangle) {
		shpBoundingRectangle->SetX(this->GetX());
		shpBoundingRectangle->SetY(this->GetY());
		shpBoundingRectangle->Draw(graphics->Get3Ddevice());
	}

}


