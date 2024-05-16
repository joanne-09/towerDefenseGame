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
    PageInfo();

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
    AddNewObject(new Engine::Label("score board", "pirulen.ttf", 60, halfW, halfH - 350, 30, 120, 100, 255, 0.5, 0.5));
    highscores.clear();
    for(int i=0; i<capacity; ++i){
        //std::cout << records[i].first << " " << records[i].second.first << " " << records[i].second.second << std::endl;
        highscores.push_back(std::vector<Engine::Label*>{new Engine::Label("", "pirulen.ttf", 40, halfW-400, halfH - 250 + i*70, 255, 255, 255, 255, 0, 0.5),
                                                         new Engine::Label("", "pirulen.ttf", 40, halfW, halfH - 250 + i*70, 255, 255, 255, 255, 0, 0.5),
                                                         new Engine::Label("", "pirulen.ttf", 40, halfW+300, halfH - 250 + i*70, 255, 255, 255, 255, 0, 0.5)});
    }
    pageLabel = new Engine::Label(std::to_string(curpage+1)+"/"+std::to_string(maxpage+1), "pirulen.ttf", 30, halfW + 650, halfH * 3 / 2, 30, 120, 100, 255, 1,  0.5);
    AddNewObject(pageLabel);
}

void ScoreBoardScene::Terminate() {
    IScene::Terminate();
}

void ScoreBoardScene::PageInfo() {
    maxpage = records.size() / capacity;
    if(records.size() % capacity == 0) maxpage--;

    curpage = 0;
    changepage = true;
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
    pageLabel->Draw();
    for(int i=0; i<capacity && i<records.size(); ++i){
        for(int j=0; j<3; ++j){
            highscores[i][j]->Draw();
        }
    }
}

void ScoreBoardScene::Update(float DeltaTime) {
    if(changepage){
        pageLabel->Text = std::to_string(curpage+1)+"/"+std::to_string(maxpage+1);
        for(int i=0; i<capacity && i<records.size(); ++i){
            highscores[i][0]->Text = std::to_string(i+1 + curpage*capacity)+": "+records[i + curpage*capacity].second.second;
            highscores[i][1]->Text = std::to_string(records[i + curpage*capacity].first);
            highscores[i][2]->Text = records[i + curpage*capacity].second.first;
        }
        changepage = false;
    }
}
