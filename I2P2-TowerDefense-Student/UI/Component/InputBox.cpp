#include <iostream>
#include "InputBox.hpp"

namespace Engine {
    InputBox::InputBox(float x, float y, float w, float h, float anchorX, float anchorY) : IObject(x, y, w, h, anchorX,anchorY) {
        x1 = x, y1 = y, x2 = x + w, y2 = y + h;
        name = "";
        count = 0, transparent = 255;
        allowInput = false;
        namelabel = new Engine::Label(name, "pirulen.ttf", 48, x1 + 10, y1 + 12, 255, 255, 255);
    }

    void InputBox::Draw() const {
        int x = namelabel->GetTextWidth();

        if(allowInput){
            al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255), 5);
            al_draw_line(x1 + x + 20, y1+10, x1 + x + 20, y2-10, al_map_rgba(255, 255, 255, transparent), 5);
            namelabel->Color = al_map_rgb(255, 255, 255);
        } else{
            al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 255, 255));
            namelabel->Color = al_map_rgb(0, 0, 0);
        }
        namelabel->Draw();
    }

    void InputBox::Update(float deltaTime) {
        count++;
        if(count == 30){
            transparent = 255 - transparent;
            count = 0;
        }
    }

    void InputBox::OnKeyDown(int keyCode) {
        if(keyCode == ALLEGRO_KEY_ENTER) allowInput = !allowInput;

        if(!allowInput) return;
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