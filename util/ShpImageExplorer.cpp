#include "ShpImageExplorer.h"


#include "../input.h"
#include "../game.h"
#include "ShpFile.h"
#include "GdiShpFileColorMapper.h"
#include "../GameSprite.h"
#include "../gameobject/MikeRectangle.h"
#include "AnimationSequence.h"




ShpImageExplorer::ShpImageExplorer(Game * game, int x, int y, Input * input) {
	this->game = game;
	this->graphics = game->GetGraphics();
	this->input = input;
	this->x = x;
	this->y = y;

	ShpFile shpFile(std::string("assets/e1.shp"));
	int imageIndex = 4;
	boolean animate = true;
	GdiShpFileColorMapper * colorMapper = new GdiShpFileColorMapper();
	gameSprite = new GameSprite(graphics->Get3Ddevice(), shpFile, colorMapper, graphicsNS::WHITE);


	drawShpBoundingRectangle = false;
	shpBoundingRectangle = new MikeRectangle(x, y, gameSprite->GetWidth(), gameSprite->GetHeight());

	//AnimationSequence * walkingUpAnimationSequence = new AnimationSequence(10);
	//walkingUpAnimationSequence->AddFrame(16);
	//walkingUpAnimationSequence->AddFrame(17);
	//walkingUpAnimationSequence->AddFrame(18);
	//walkingUpAnimationSequence->AddFrame(19);
	//walkingUpAnimationSequence->AddFrame(20);
	//walkingUpAnimationSequence->AddFrame(21);

	//gameSprite->AddAnimationSequence(0, walkingUpAnimationSequence);

	//currentImageIndex = 0;
	//animationSequence = new AnimationSequence(10);
	//animationSequence->AddFrame(currentImageIndex);

	currentImageIndex = 0;
	animationSequence = new AnimationSequence(50);
	animationSequence->AddFrame(65);
	animationSequence->AddFrame(66);
	animationSequence->AddFrame(67);
	animationSequence->AddFrame(68);
	animationSequence->AddFrame(69);
	animationSequence->AddFrame(70);
	animationSequence->AddFrame(71);
	animationSequence->AddFrame(72);

	gameSprite->AddAnimationSequence(0, animationSequence);
	gameSprite->SetCurrentAnimationSequenceIndex(0);

}

void ShpImageExplorer::Draw() {
	gameSprite->Draw(0, x, y);

	//if (drawShpBoundingRectangle) {
	//	shpBoundingRectangle->SetX(this->GetX());
	//	shpBoundingRectangle->SetY(this->GetY());
	//	shpBoundingRectangle->Draw(graphics->Get3Ddevice());
	//}


}

void ShpImageExplorer::IncrementFrame() {
	currentImageIndex++;
	delete animationSequence;
	animationSequence = new AnimationSequence(10);
	animationSequence->AddFrame(currentImageIndex);
	gameSprite->AddAnimationSequence(0, animationSequence);
	gameSprite->AddAnimationSequence(1, animationSequence);
	gameSprite->SetCurrentAnimationSequenceIndex(1);
	gameSprite->SetCurrentAnimationSequenceIndex(0);

}

void ShpImageExplorer::DecrementFrame() {
	currentImageIndex--;
	delete animationSequence;
	animationSequence = new AnimationSequence(10);
	animationSequence->AddFrame(currentImageIndex);
	gameSprite->AddAnimationSequence(0, animationSequence);
	gameSprite->AddAnimationSequence(1, animationSequence);
	gameSprite->SetCurrentAnimationSequenceIndex(1);
	gameSprite->SetCurrentAnimationSequenceIndex(0);

}


void ShpImageExplorer::Update(float frameTime) {
	static int switchTimer = 0;
	switchTimer++;
	if (switchTimer > 10) {
		switchTimer = 0;
		if (input->IsKeyDown(VK_RIGHT)) {
			IncrementFrame();
		}
		else if (input->IsKeyDown(VK_LEFT)) {
			DecrementFrame();
		}
	}

}
