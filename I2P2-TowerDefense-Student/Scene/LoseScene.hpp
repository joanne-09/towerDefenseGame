#ifndef LOSESCENE_HPP
#define LOSESCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include "Engine/FileIO.hpp"
#include "UI/Component/InputBox.hpp"

class LoseScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::InputBox *box;
public:
    static int SpentTime;
    std::string Name;
	explicit LoseScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick(int stage);
};

#endif // LOSESCENE_HPP
