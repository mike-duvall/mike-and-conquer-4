#include "TestModeRestHandler.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "game.h"
#include "Minigunner.h"



TestModeRestHandler::TestModeRestHandler(Game * aGame) {
	this->game = aGame;
	std::wstring gdiMinigunnerURL = baseUrl + L"/mac/gdiMinigunner";
	gdiMinigunnerListener = new http_listener(gdiMinigunnerURL);
	gdiMinigunnerListener->open().wait();
	gdiMinigunnerListener->support(
		methods::POST,
		[this](http_request request) {return HandlePostGdiMinigunner(request); });

	gdiMinigunnerListener->support(
		methods::GET,
		[this](http_request request) {return HandleGetGdiMinigunner(request); });

	std::wstring nodMinigunnerURL = baseUrl + L"/mac/nodMinigunner";
	nodMinigunnerListener = new http_listener(nodMinigunnerURL);
	nodMinigunnerListener->open().wait();
	nodMinigunnerListener->support(
		methods::POST,
		[this](http_request request) {return HandlePostNodMinigunner(request); });


	nodMinigunnerListener->support(
		methods::GET,
		[this](http_request request) {return HandleGetNodMinigunner(request); });

	std::wstring leftClickURL = baseUrl + L"/mac/leftClick";
	leftClickListener = new http_listener(leftClickURL);
	leftClickListener->open().wait();
	leftClickListener->support(
		methods::POST,
		[this](http_request request) {return HandlePOSTLeftClick(request); });

}

void TestModeRestHandler::HandlePostGdiMinigunner(http_request message) {
	std::pair<int, int> xAndY = ParseMinigunnerRequest(message);
	game->AddCreateGDIMinigunnerEvent(xAndY.first, xAndY.second);
	// TODO:  update this to return the created minigunner as JSON, instead of result message
	message.reply(status_codes::OK, U("Initialized minigunner"));
};


void TestModeRestHandler::HandlePostNodMinigunner(http_request message) {
	std::pair<int, int> xAndY = ParseMinigunnerRequest(message);
	game->AddCreateNODMinigunnerEvent(xAndY.first, xAndY.second);
	// TODO:  update this to return the created minigunner as JSON, instead of result message
	message.reply(status_codes::OK, U("Initialized minigunner"));
};



void TestModeRestHandler::ClickLeftMouseButton(int x, int y) {

	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);

	INPUT mouseInput = { 0 };
	mouseInput.type = INPUT_MOUSE;
	mouseInput.mi.dx = (LONG)fx;
	mouseInput.mi.dy = (LONG)fy;
	mouseInput.mi.mouseData = 0;


	mouseInput.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	::SendInput(1, &mouseInput, sizeof(INPUT));

	mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;;
	::SendInput(1, &mouseInput, sizeof(INPUT));

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &mouseInput, sizeof(INPUT));
}


std::pair<int, int>  TestModeRestHandler::ParseMinigunnerRequest(http_request message) {
	pplx::task<json::value> jsonValue = message.extract_json();
	web::json::value webJsonValue = jsonValue.get();
	web::json::object object = webJsonValue.as_object();

	int minigunnerX = -666;
	int minigunnerY = -666;

	for (auto iter = object.cbegin(); iter != object.cend(); ++iter) {
		utility::string_t attributeName = iter->first;
		//const json::value &str = iter->first;
		const json::value &v = iter->second;

		if (attributeName == L"x") {
			minigunnerX = v.as_integer();
		}

		if (attributeName == L"y") {
			minigunnerY = v.as_integer();
		}
	}

	std::pair<int, int> xAndY = std::make_pair(minigunnerX, minigunnerY);
	return xAndY;
}






void TestModeRestHandler::RenderAndReturnMinigunner(http_request message, Minigunner * minigunner) {
	json::value obj;
	obj[L"x"] = json::value::number(minigunner->GetX());
	obj[L"y"] = json::value::number(minigunner->GetY());
	obj[L"health"] = json::value::number(minigunner->GetHealth());
	message.reply(status_codes::OK, obj);
}



void TestModeRestHandler::HandleGetGdiMinigunner(http_request message) {
	Minigunner * minigunner = game->GetGDIMinigunnerViaEvent();
	RenderAndReturnMinigunner(message, minigunner);
};


void TestModeRestHandler::HandleGetNodMinigunner(http_request message) {
	Minigunner * minigunner = game->GetNODMinigunnerViaEvent();
	RenderAndReturnMinigunner(message, minigunner);
};


void TestModeRestHandler::HandlePOSTLeftClick(http_request message) {
	pplx::task<json::value> jsonValue = message.extract_json();
	web::json::value webJsonValue = jsonValue.get();
	web::json::object object = webJsonValue.as_object();

	int mouseX = -666;
	int mouseY = -666;

	for (auto iter = object.cbegin(); iter != object.cend(); ++iter) {
		utility::string_t attributeName = iter->first;
		//const json::value &str = iter->first;
		const json::value &v = iter->second;

		if (attributeName == L"x") {
			mouseX = v.as_integer();
		}

		if (attributeName == L"y") {
			mouseY = v.as_integer();
		}
	}

	ClickLeftMouseButton(mouseX, mouseY);
	message.reply(status_codes::OK, U("Success"));
};

