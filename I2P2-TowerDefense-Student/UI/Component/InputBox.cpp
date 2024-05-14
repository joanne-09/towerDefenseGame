#include <iostream>
#include "InputBox.hpp"

namespace Engine {
    InputBox::InputBox(float x, float y, float w, float h, float anchorX, float anchorY) : IObject(x, y, w, h, anchorX,anchorY) {
        x1 = x, y1 = y, x2 = x + w, y2 = y + h;
        name = "";
        namelabel = new Engine::Label(name, "pirulen.ttf", 48, x1 + 10, y1 + 12, 255, 255, 255);
    }

    void InputBox::Draw() const {
        al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255), 5);
        namelabel->Draw();
    }

    void InputBox::Update(float DeltaTime) {
        namelabel->Draw();
    }

    void InputBox::OnKeyDown(int keyCode) {
        if (keyCode == ALLEGRO_KEY_BACKSPACE && !name.empty()) {
            name.pop_back();
        } else if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z && name.length() < maxsize) {
            char append = keyCode - ALLEGRO_KEY_A + 'A';
            name.push_back(append);
        } else if(keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9 && name.length() < maxsize){
            char append = keyCode - ALLEGRO_KEY_0 + '0';
            name.push_back(append);
        }
        namelabel->Text = name;
    }
}