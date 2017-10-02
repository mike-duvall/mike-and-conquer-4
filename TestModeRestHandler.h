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
	static json::value RenderMinigunnerToJson(Minigunner* minigunner);
	static void RenderAndReturnMinigunnerList(http_request message, std::vector<Minigunner*> * allGDIMinigunnerList);
	bool HandleGetGdiMinigunnerAtLocation(http_request message);
	bool HandleGetNodMinigunnerAtLocation(http_request message);
	void HandleGetGdiMinigunners(http_request message);
	void HandleGetNodMinigunners(http_request message);
	static void HandlePOSTLeftClick(http_request message);
	void HandleGetGameState(http_request message);
	void HandleResetGame(http_request message);



	static int GetGdiMinigunnerIdFromUriIfPresent(uri theUri);
	int GetNodMinigunnerIdFromUriIfPresent(uri theUri);
	bool HandleGetGdiMinigunnerById(http_request message);
	bool HandleGetNodMinigunnerById(http_request message);
	bool HandleGetAllGdiMinigunners(http_request message);
	bool HandleGetAllNodMinigunners(http_request message);

	std::wstring baseUrl = L"http://*:11369";
	Game * game;
	http_listener * gameStateListener;
	http_listener * gdiAllMinigunnersURLListener;
	http_listener * nodMinigunnerListener;
	http_listener * leftClickListener;
	http_listener * resetGameListener;

};