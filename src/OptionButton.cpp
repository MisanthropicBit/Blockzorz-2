#include "option_button.hpp"
#include "audio_manager.hpp"
#include "graphics.hpp"

option_button::option_button() {
    current = 0;
    alpha   = 0.f;
    color   = color::black;
    selections.clear();
}

option_button::~option_button() {
    font.close();
    selections.clear();
}

bool option_button::load(const std::string& font_file,
                         const color& color,
                         int size,
                         int x,
                         int y) {
    this->color = color;
    font.set_font_file(font_file, size);

    rect.x = x;
    rect.y = y;
    rect.w = 0;
    rect.h = font.height();

    return true;
}

void option_button::draw() {
    if (current >= 0 && current <= selections.size()) {
        font.draw_text_transparent(selections[current], color, alpha, rect.x, rect.y);
    }
}

void option_button::add_selection(const std::string& selection) {
    if (!selection.empty()) {
        selections.push_back(selection);
        rect.w = font.string_width(selection);
    }
}

bool option_button::set_selection(const std::string& selection) {
    for (int i = 0; i < selections.size(); i++) {
        if (selections[i] == selection) {
            current = i;
            rect.w  = font.string_width(selections[current]);
            return true;
        }
    }

    return false;
}

std::string option_button::selection() {
    if (!selections.empty() && current >= 0 && current <= selections.size()) {
        return selections[current];
    }

    return "";
}

void option_button::select() {
    selected = true;
}

void option_button::deselect() {
    selected = false;
}

bool option_button::is_selected() const {
    return selected;
}

void option_button::set_alpha(float alpha) {
    if (alpha >= 0.f && alpha <= 1.f) {
        this->alpha = alpha;
    }
}

bool option_button::has_mouse_hover(int mx, int my) {
    return mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
}

void option_button::left_button_down(int mx, int my) {
    if (has_mouse_hover(mx, my)) {
        ++current;

        if (current >= selections.size()) {
            current = 0;
        }

        rect.w = font.string_width(selections[current]);
    }
}

void option_button::mouse_move(int mx, int my) {
    if (has_mouse_hover(mx, my)) {
        if (!is_selected()) {
            select();
            set_alpha(0.f);
            audio_manager::get()->play_sound("click", 0);
        }
    } else {
        if (is_selected()) {
            deselect();
            set_alpha(0.8f);
        }
    }
}
