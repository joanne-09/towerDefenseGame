#ifndef INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_INPUTBOX_HPP
#define INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_INPUTBOX_HPP
#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <functional>
#include <memory>
#include <string>
#include "Engine/GameEngine.hpp"
#include "Engine/IControl.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Image.hpp"

namespace Engine {
    class InputBox : public Engine::IObject, public Engine::IControl {
    private:
        std::string name;
        Engine::Label *namelabel;
        int maxsize = 9;
        float x1, y1, x2, y2;
        int transparent, count;
    protected:
        ;
    public:
        /// <summary>
        /// Construct a image object.
        /// </summary>
        /// <param name="img">The mouse-out image path in 'Resource/images/'</param>
        /// <param name="imgIn">The mouse-in image path in 'Resource/images/'</param>
        /// <param name="x">X-coordinate.</param>
        /// <param name="y">Y-coordinate.</param>
        /// <param name="w">Width of the image, 0 indicates original size.</param>
        /// <param name="h">Height of the image, 0 indicates original size.</param>
        /// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
        /// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
        explicit InputBox(float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);

        /// <summary>
        /// draw initial rectangle box for input
        void Draw() const override;
        /// <summary>
        /// update the ticking of input bar
        void Update(float deltaTime) override;
        /// <summary>
        /// get the key input and append it to the string
        void OnKeyDown(int keyCode) override;
        // used for writing file to get private member
        std::string getName(){
            return name;
        }
    };
}

#endif //INC_2024_I2P2_TOWERDEFENSE_WITH_ANSWER_INPUTBOX_HPP
