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

private:

	static void ClickLeftMouseButton(int x, int y);
	static std::pair<int, int>  ParseMinigunnerRequest(http_request message);
	void HandlePostGdiMinigunner(http_request message);
	void HandlePostNodMinigunner(http_request message);
	void RenderAndReturnMinigunner(http_request message, Minigunner * minigunner);
	static void RenderAndReturnMinigunnerList(http_request message, std::vector<Minigunner*> * allGDIMinigunnerList);
	bool HandleGetMinigunnerAtLocation(http_request message);
	void HandleGetMinigunners(http_request message);
	void HandleGetNodMinigunner(http_request message);
	static void HandlePOSTLeftClick(http_request message);
	void HandleGetGameState(http_request message);
	void HandleResetGame(http_request message);



	static int GetMinigunnerIdFromUriIfPresent(uri theUri);
	bool HandleGetMinigunnerById(http_request message);
	bool HandleGetAllMinigunners(http_request message);

	std::wstring baseUrl = L"http://*:11369";
	Game * game;
	http_listener * gameStateListener;
	http_listener * gdiAllMinigunnersURLListener;
	http_listener * nodMinigunnerListener;
	http_listener * leftClickListener;
	http_listener * resetGameListener;

};