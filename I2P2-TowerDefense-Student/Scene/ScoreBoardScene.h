//
// Created by User on 5/11/2024.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_SCOREBOARDSCENE_H
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_SCOREBOARDSCENE_H

#include <allegro5/allegro_audio.h>
#include <memory>
#include <vector>
#include <utility>
#include "Engine/IScene.hpp"

class ScoreBoardScene final : public Engine::IScene {
private:
    /// each page display five player
    bool changepage = true;
    int curpage = 0;
    int maxpage, remainder, cursize ,capacity = 7;
    std::vector<std::pair<std::pair<int, int>, std::string>> records;
    std::vector<std::vector<Engine::Label*>> highscores;
    Engine::Label* pageLabel;
public:
    explicit ScoreBoardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PageInfo();
    void BackOnClick(int stage);
    void PrevOnClick(int stage);
    void NextOnClick(int stage);
    void Draw() const override;
    void Update(float DeltaTime) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_SCOREBOARDSCENE_H
