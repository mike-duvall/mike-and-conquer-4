#include "TestModeRestHandler.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <codecvt>
#include "game.h"
#include "gameobject/Minigunner.h"
#include "gamestate/GameState.h"



TestModeRestHandler::TestModeRestHandler(Game * aGame) {
	this->game = aGame;

	std::wstring gdiAllMinigunnersURL = baseUrl + L"/mac/gdiMinigunners";
	gdiAllMinigunnersURLListener = new http_listener(gdiAllMinigunnersURL);
	gdiAllMinigunnersURLListener->open().wait();


	gdiAllMinigunnersURLListener->support(
		methods::POST,
		[this](http_request request) {return HandlePostGdiMinigunner(request); });


	gdiAllMinigunnersURLListener->support(
		methods::GET,
		[this](http_request request) {return HandleGetMinigunners(request); });



	std::wstring nodMinigunnerURL = baseUrl + L"/mac/nodMinigunners";
	nodMinigunnerListener = new http_listener(nodMinigunnerURL);
	nodMinigunnerListener->open().wait();
	nodMinigunnerListener->support(
		methods::POST,
		[this](http_request request) {return HandlePostNodMinigunner(request); });


	nodMinigunnerListener->support(
		methods::GET,
		[this](http_request request) {return HandleGetNodMinigunner(request); });

	std::wstring leftClickUrl = baseUrl + L"/mac/leftClick";
	leftClickListener = new http_listener(leftClickUrl);
	leftClickListener->open().wait();
	leftClickListener->support(
		methods::POST,
		[this](http_request request) {return HandlePOSTLeftClick(request); });


	std::wstring resetGameURL = baseUrl + L"/mac/resetGame";
	resetGameListener = new http_listener(resetGameURL);
	resetGameListener->open().wait();
	resetGameListener->support(
		methods::POST,
		[this](http_request request) {return HandleResetGame(request); });

	std::wstring gameStateURL = baseUrl + L"/mac/gameState";
	gameStateListener = new http_listener(gameStateURL);
	gameStateListener->open().wait();

	gameStateListener->support(
		methods::GET,
		[this](http_request request) {return HandleGetGameState(request); });


}


void TestModeRestHandler::HandlePostGdiMinigunner(http_request message) {
	std::pair<int, int> xAndY = ParseMinigunnerRequest(message);
	Minigunner * minigunner = game->CreateGDIMinigunnerViaEvent(xAndY.first, xAndY.second);
	RenderAndReturnMinigunner(message, minigunner);
}




void TestModeRestHandler::HandlePostNodMinigunner(http_request message) {
	std::pair<int, int> xAndY = ParseMinigunnerRequest(message);
	Minigunner * minigunner = game->CreateNodMinigunnerViaEvent(xAndY.first, xAndY.second);
	RenderAndReturnMinigunner(message, minigunner);

}



void TestModeRestHandler::ClickLeftMouseButton(int x, int y) {

	double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
	double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
	double fx = x*(65535.0f / fScreenWidth);
	double fy = y*(65535.0f / fScreenHeight);

	INPUT mouseInput = { 0 };
	mouseInput.type = INPUT_MOUSE;
	mouseInput.mi.dx = LONG(fx);
	mouseInput.mi.dy = LONG(fy);
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

	if (minigunner == nullptr) {
		json::value dummyJsonObj;
		message.reply(status_codes::NotFound, dummyJsonObj);
	}
	else {
		json::value minigunnerAsJson = RenderMinigunnerToJson(minigunner);
		message.reply(status_codes::OK, minigunnerAsJson);
	}
}


json::value TestModeRestHandler::RenderMinigunnerToJson(Minigunner * minigunner) {
	json::value jsonObject;
	jsonObject[L"id"] = json::value::number(minigunner->GetId());
	jsonObject[L"x"] = json::value::number(minigunner->GetX());
	jsonObject[L"y"] = json::value::number(minigunner->GetY());
	jsonObject[L"health"] = json::value::number(minigunner->GetHealth());
	jsonObject[L"selected"] = json::value::boolean(minigunner->GetIsSelected());
	jsonObject[L"health"] = json::value::number(minigunner->GetHealth());
	return jsonObject;
}

void TestModeRestHandler::RenderAndReturnMinigunnerList(http_request message, std::vector<Minigunner * > * allGdiMinigunnerList) {

	json::value gdiMinigunnerJsonArray;
	int arrayIndex = 0;

	std::vector<Minigunner *>::iterator iter;
	for (iter = allGdiMinigunnerList->begin(); iter != allGdiMinigunnerList->end(); ++iter) {
		Minigunner * minigunner = *iter;
		json::value minigunnerJson = RenderMinigunnerToJson(minigunner);
		gdiMinigunnerJsonArray[arrayIndex] = minigunnerJson;
		arrayIndex++;
	}

	message.reply(status_codes::OK, gdiMinigunnerJsonArray);
}



int TestModeRestHandler::GetMinigunnerIdFromUriIfPresent(uri theUri) {

	std::wstring uri = theUri.path().c_str();
	int minigunnerId;
	if (1 == swscanf_s(uri.c_str(), L"/mac/gdiMinigunners/%d", &minigunnerId)) {
		return minigunnerId;
	}
	else {
		return -1;
	}
	
}
 

bool TestModeRestHandler::HandleGetMinigunnerById(http_request message) {
	int minigunnerId = GetMinigunnerIdFromUriIfPresent(message.request_uri());

	if (minigunnerId != -1) {
		Minigunner * minigunner = game->GetGDIMinigunnerByIdViaEvent(minigunnerId);
		RenderAndReturnMinigunner(message, minigunner);
		return true;
	}

	return false;
	
}

bool TestModeRestHandler::HandleGetAllMinigunners(http_request message) {
	std::vector<Minigunner * > * allGDIMinigunnerList = game->GetAllGDIMinigunnersViaEvent();
	RenderAndReturnMinigunnerList(message, allGDIMinigunnerList);

	return true;
}


void TestModeRestHandler::HandleGetMinigunners(http_request message) {

	if (!HandleGetMinigunnerById(message)) {
		if(!HandleGetMinigunnerAtLocation(message)) {
			HandleGetAllMinigunners(message);
		}
	}
}


bool TestModeRestHandler::HandleGetMinigunnerAtLocation(http_request message) {

	auto http_get_vars = uri::split_query(message.request_uri().query());
	if(http_get_vars.size() != 2) {
		return false;
	}
	utility::string_t xString = L"x";
	utility::string_t yString = L"y";

	auto xValueFromQueryParam = http_get_vars[xString];
	auto yValueFromQueryParam = http_get_vars[yString];

	int minigunnerX = _wtoi(xValueFromQueryParam.c_str());
	int minigunnerY = _wtoi(yValueFromQueryParam.c_str());

	Minigunner * minigunner = game->GetMinigunnerAtLocationViaEvent(minigunnerX, minigunnerY);
	RenderAndReturnMinigunner(message, minigunner);
	return true;
}




void TestModeRestHandler::HandleGetNodMinigunner(http_request message) {
	Minigunner * minigunner = game->GetNODMinigunnerViaEvent();
	RenderAndReturnMinigunner(message, minigunner);
}
								   
								 
void TestModeRestHandler::HandleGetGameState(http_request message) {
	GameState * currentGameState = game->GetCurrentGameState();

	std::string gameStateName = currentGameState->GetName();
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wideGameStateName = converter.from_bytes(gameStateName);

	json::value obj;
	obj[L"gameState"] = json::value::string(wideGameStateName);

	message.reply(status_codes::OK, obj);
}


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
}

void TestModeRestHandler::HandleResetGame(http_request message) {
	pplx::task<json::value> jsonValue = message.extract_json();
	game->AddResetGameEvent();
	message.reply(status_codes::OK, U("Success"));
};


