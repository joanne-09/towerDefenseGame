#include <allegro5/allegro_audio.h>
#include <functional>

#include "Engine/GameEngine.hpp"
#include "Engine/FileIO.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "ScoreBoardScene.h"

FileIO newIO;
void ScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    records = newIO.read();
    maxpage = records.size() / capacity, remainder = records.size() % capacity == 0 ? capacity : records.size() % capacity;
    cursize = curpage == maxpage ? remainder : capacity;
    //SortRecord();

    // back button
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    // switch page button
    Engine::ImageButton *prevpage, *nextpage;
    prevpage = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 650, halfH * 3 / 2 + 50, 400, 100);
    prevpage->SetOnClickCallback(std::bind(&ScoreBoardScene::PrevOnClick, this, 1));
    AddNewControlObject(prevpage);
    AddNewObject(new Engine::Label("prev page", "pirulen.ttf", 48, halfW - 450, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    nextpage = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 250, halfH * 3 / 2 + 50, 400, 100);
    nextpage->SetOnClickCallback(std::bind(&ScoreBoardScene::NextOnClick, this, 1));
    AddNewControlObject(nextpage);
    AddNewObject(new Engine::Label("next page", "pirulen.ttf", 48, halfW + 450, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    // score board display
    AddNewObject(new Engine::Label("score board", "pirulen.ttf", 60, halfW, halfH - 350, 255, 255, 255, 255, 0.5, 0.5));
    for(int i=0; i<cursize; ++i){
        highscores.push_back(std::vector<Engine::Label*>{new Engine::Label(std::to_string(i+1)+": "+records[i].second, "pirulen.ttf", 40, halfW-300, halfH - 250 + i*70, 255, 255, 255, 255, 0, 0.5),
                                                         new Engine::Label(std::to_string(records[i].first.first), "pirulen.ttf", 40, halfW + 100, halfH - 250 + i*70, 255, 255, 255, 255, 0, 0.5),
                                                         new Engine::Label(std::to_string(records[i].first.second), "pirulen.ttf", 40, halfW+200, halfH - 250 + i*70, 255, 255, 255, 255, 0, 0.5)});
    }
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

void ScoreBoardScene::Draw() const{
    IScene::Draw();
    for(int i=0; i<cursize; ++i){
        for(int j=0; j<3; ++j){
            highscores[i][j]->Draw();
        }
    }
}

void ScoreBoardScene::Update(float DeltaTime) {
    cursize = curpage == maxpage ? remainder : capacity;
    if(changepage){
        for(int i=0; i<cursize; ++i){
            highscores[i][0]->Text = std::to_string(i+1 + curpage*capacity)+": "+records[i + curpage*capacity].second;
            highscores[i][1]->Text = std::to_string(records[i + curpage*capacity].first.first);
            highscores[i][2]->Text = std::to_string(records[i + curpage*capacity].first.second);
        }
        changepage = false;
    }
}

void ScoreBoardScene::SortRecord() {
    ;
}