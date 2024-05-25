#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_MOCKBOARD_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_MOCKBOARD_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include <vector>
#include <utility>
#include "Engine/IScene.hpp"

class MockBoard final : public Engine::IScene {
private:
    /// each page display five player
    bool changepage = true;
    int curpage = 0;
    int maxpage, capacity = 7;
    std::vector<std::pair<int, std::pair<std::string, std::string>>> records;
    std::vector<std::vector<Engine::Label*>> highscores;
    Engine::Label* pageLabel;

    FileIO newIO;
public:
    explicit MockBoard() = default;
    void Initialize() override;
    void Terminate() override;
    void PageInfo();
    void BackOnClick(int stage);
    void PrevOnClick(int stage);
    void NextOnClick(int stage);
    void Draw() const override;
    void Update(float DeltaTime) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_MOCKBOARD_HPP
