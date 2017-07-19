#pragma once

#include <cpprest\http_listener.h>


using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;


class Minigunner;
class Game;

class TestModeRestHandler {

public:
	TestModeRestHandler(Game * aGame);



	void ClickLeftMouseButton(int x, int y);
	std::pair<int, int>  ParseMinigunnerRequest(http_request message);
	void HandlePostGdiMinigunner(http_request message);
	void HandlePostNodMinigunner(http_request message);
	void RenderAndReturnMinigunner(http_request message, Minigunner * minigunner);
	void HandleGetGdiMinigunner(http_request message);
	void HandleGetNodMinigunner(http_request message);
	void HandlePOSTLeftClick(http_request message);
	void HandleGetGameState(http_request message);
	void HandleResetGame(http_request message);

private:
	std::wstring baseUrl = L"http://*:11369";
	Game * game;
	http_listener * gdiMinigunnerListener;
	http_listener * nodMinigunnerListener;
	http_listener * leftClickListener;
	http_listener * resetGameListener;

};