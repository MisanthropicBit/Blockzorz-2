#include "audio_manager.hpp"
#include "color.hpp"
#include "font.hpp"
#include "game_state_manager.hpp"
#include "game_state_pop_up.hpp"
#include "graphics.hpp"
#include "particle_effect.hpp"
#include "screen.hpp"

game_state_popup::GameStatePopUp() {
    fader = nullptr;
    popup = nullptr;
    title = nullptr;
    text  = nullptr;
}

game_state_popup::game_state_popup(const std::string& caption,
                                   const std::string& text,
                                   const std::string& confirmtext,
                                   const std::string& quittext,
                                   game_state* return_state) {
    fader = nullptr;
    popup = nullptr;
    title = nullptr;
    text  = nullptr;

    font title_font("./fonts/biocomv2.ttf", 30);
    font text_font("./fonts/biocomv2.ttf",  20);

    title = title_font.load_hq_text_image(caption, color::dark_blue);
    text  = text_font.load_hq_text_image(text, color::black);

    yes.load(confirm_text, "./fonts/biocomv2.ttf", color::black, 25, 200 - text_font.string_width(confirm_text)/2, 280);
    no.load(quit_text, "./fonts/biocomv2.ttf", color::black, 25, 400 - text_font.string_width(quit_text)/2, 280);
    yes.set_alpha(0.8f);
    no.set_alpha(0.8f);

    this->return_state = return_state;

    titlex = screen::get().width()/2 - title_font.string_width(caption)/2;
    textx  = screen::get().width()/2 - text_font.string_width(text)/2;

    title_font.close();
    text_font.close();
}

game_state_popup::~game_state_popup() {
}

bool game_state_popup::load() {
    fader = graphics::load_image("./images/fader.png");
    popup = graphics::load_image("./images/popup.png", color::magenta);
    graphics::set_transparency(fader, 0.5f);

    return fader && popup && title && text;
}

void game_state_popup::on_event(SDL_Event& event) {
    event::on_event(event);
}

void game_state_popup::update(int dt) {
}

void game_state_popup::draw() {
    graphics::draw_image(fader, 0, 0);
    graphics::draw_image(popup, 120, 140);
    graphics::draw_image(title, titlex, 150);
    graphics::draw_image(text, 140, 230);

    yes.draw();
    no.draw();
}

void game_state_popup::unload() {
    returnstate = nullptr;

    SDL_FreeSurface(fader);
    SDL_FreeSurface(popup);
    SDL_FreeSurface(title);
    SDL_FreeSurface(text);

    fader = nullptr;
    popup = nullptr;
    title = nullptr;
    text  = nullptr;
}

void game_state_popup::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
    if (key == SDLK_y || key == SDLK_RETURN) {
        if (return_state) {
            game_state_manager::get().change_state(return_state);
        } else {
            delete return_state;
            game_state_manager::get().quit();
        }
    } else if (key == SDLK_n || key == SDLK_BACKSPACE || key == SDLK_ESCAPE) {
        delete return_state;
        game_state_manager::get().pop_state();
    }
}

void game_state_popup::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
    yes.mouse_move(mx, my);
    no.mouse_move(mx, my);
}

void game_state_popup::left_button_down(int mx, int my) {
    if (yes.has_mouse_hover(mx, my)) {
        if (return_state) {
            game_state_manager::get().change_state(return_state);
        } else {
            delete return_state;
            game_state_manager::get().quit();
        }
    } else if (no.has_mouse_hover(mx, my)) {
        delete return_state;
        game_state_manager::get().pop_state();
    }
}

game_state_mode_unlocked::game_state_mode_unlocked() : game_state_popup() {
    particle_interval = 400;
}

game_state_mode_unlocked::game_state_mode_unlocked(const std::string& caption,
                                                   const std::string& text,
                                                   game_state* return_state) : game_state_popup() {
    font title_font("./fonts/biocomv2.ttf", 30);
    font text_font("./fonts/biocomv2.ttf", 20);

    title = title_font.load_hq_text_image(caption, color::dark_blue);
    text  = text_font.load_hq_text_image(text, color::black);

    awesome.load("Yeeees!", "./fonts/biocomv2.ttf", color::gold, 25, 250, 280);
    awesome.set_alpha(0.5f);

    this->return_state = return_state;
    particle_interval  = 400;
    titlex             = screen::get().width()/2 - title_font.string_width(caption)/2;
    textx              = screen::get().width()/2 - text_font.string_width(text)/2;

    title_font.close();
    text_font.close();
}

game_state_mode_unlocked::~game_state_mode_unlocked() {
}

bool game_state_mode_unlocked::Load() {
    audio_manager::get()->play_sound("screech", 0);
    audio_manager::get()->play_sound("moves", 0);

    return game_state_popup::load();
}

void game_state_mode_unlocked::on_event(SDL_Event& event) {
    event::on_event(event);
}

void game_state_mode_unlocked::update(int dt) {
    particle_interval -= dt;
    pe_manager.update(dt);

    if (particle_interval <= 0) {
        particle_interval = 400;

        particle_explosion_effect* pex = new particle_explosion_effect("./images/cursor.png", 8, 0.1f, 0.1f, rand() % 641, rand() % 481);
        pex->set_update_interval(40, 80);
        pex->show();
        pe_manager.add_effect(pex);
    }
}

void game_state_mode_unlocked::draw() {
    graphics::draw_image(fader, 0, 0);
    graphics::draw_image(popup, 120, 140);
    graphics::draw_image(title, titlex, 150);
    graphics::draw_image(text, 140, 230);

    awesome.draw();
    pe_manager.draw();
}

void game_state_mode_unlocked::unload() {
    game_state_popup::unload();
}

void game_state_mode_unlocked::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
    if (key == SDLK_RETURN) {
        game_state_manager::get().pop_state();
    }
}

void game_state_mode_unlocked::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
    if (awesome.has_mouse_hover(mx, my)) {
        if (!awesome.selected()) {
            awesome.select();
            awesome.set_alpha(0.f);
            audio_manager::get()->play_sound("click", 0);
        }
    } else {
        if (awesome.selected()) {
            awesome.deselect();
            awesome.set_alpha(0.8f);
        }
    }
}

void game_state_mode_unlocked::left_button_down(int mx, int my) {
    if (awesome.has_mouse_hover(mx, my)) {
        game_state_manager::get().pop_state();
    }
}
