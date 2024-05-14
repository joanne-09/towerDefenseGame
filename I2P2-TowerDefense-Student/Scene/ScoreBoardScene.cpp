#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>

#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "ScoreBoardScene.h"

void ScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    // back button
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    // switch page button
    Engine::ImageButton *prevpage, *nextpage;
    prevpage = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 650, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevOnClick, this, 1));
    AddNewControlObject(prevpage);
    AddNewObject(new Engine::Label("prev page", "pirulen.ttf", 48, halfW - 450, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    nextpage = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 250, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::NextOnClick, this, 1));
    AddNewControlObject(nextpage);
    AddNewObject(new Engine::Label("next page", "pirulen.ttf", 48, halfW + 450, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    // score board display
    AddNewObject(new Engine::Label("score board", "pirulen.ttf", 60, halfW, halfH - 350, 255, 255, 255, 255, 0.5, 0.5));
}

void ScoreBoardScene::Terminate() {
    IScene::Terminate();
}

void ScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreBoardScene::PrevOnClick(int stage) {
    if(curpage > 0){
        curpage --;
        changepage = true;
    }
}

void ScoreBoardScene::NextOnClick(int stage) {
    if(curpage < maxpage){
        curpage ++;
        changepage = true;
    }
}

void ScoreBoardScene::Draw() const {
    ;
}

void ScoreBoardScene::Update(float DeltaTime) {
    if(changepage){
        IScene::Draw();
        changepage = false;
    }
}
