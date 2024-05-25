#include <functional>
#include <string>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/InputBox.hpp"
#include "UI/Component/Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"

int LoseScene::SpentTime = 0;
void LoseScene::Initialize() {
	// TODO: [HACKATHON-1-SCENE] (1/4): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("lose/benjamin-happy.png", halfW, halfH + 10, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You survive for only " + std::to_string(SpentTime) + " seconds!?", "pirulen.ttf", 48, halfW, halfH / 4 - 30, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&LoseScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Continue", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    box = new Engine::InputBox(halfW-250, halfH / 4 + 10, 500, 80);
    AddNewControlObject(box);

    bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, PlayScene::DangerTime);
}
void LoseScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void LoseScene::BackOnClick(int stage) {
    // get info of current time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday;
    // set output name
    Name = box->getName() == "" ? "PLAYER" : box->getName();
    // write to file and sort it
    FileIO newIO("../Resource/mockboard.txt");
    newIO.write(std::vector<std::string>{std::to_string(SpentTime), ss.str(), Name + "\n"});
    newIO.sort(0);
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
