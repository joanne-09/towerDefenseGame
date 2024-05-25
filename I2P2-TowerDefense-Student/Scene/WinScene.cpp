#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/InputBox.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"

int WinScene::Score = 0;
void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH + 10, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("Congrats! You Got " + std::to_string(Score) + " Points!", "pirulen.ttf", 48, halfW, halfH / 4 -30, 255, 255, 255, 255, 0.5, 0.5));

    Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Continue", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    //Engine::InputBox* box;
    box = new Engine::InputBox(halfW-250, halfH/4+10, 500, 80);
    AddNewControlObject(box);

	bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
    box->Update(deltaTime);
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
    // get info of current time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday;
    // set output name
    Name = box->getName() == "" ? "PLAYER" : box->getName();
    // write to file and sort it
    FileIO newIO;
    newIO.write(std::vector<std::string>{std::to_string(Score), ss.str(), Name + "\n"});
    newIO.sort();
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
