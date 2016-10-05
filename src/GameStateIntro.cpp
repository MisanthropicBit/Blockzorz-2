#include "game_state_intro.hpp"
#include "game_state_menu.hpp"
#include "game_state_manager.hpp"
#include "graphics.hpp"
#include "audio_manager.hpp"
#include "screen.hpp"
#include <iostream>

game_state_intro::game_state_intro() {
    logo  = nullptr;
    fader = nullptr;
}

bool game_state_intro::load() {
    logo            = graphics::load_image("./images/storm_games_logo.png");
    sdl_logo        = graphics::load_image("./images/sdl_logo.png");
    fader           = graphics::load_image("./images/fader.png");
    sound_effect    = "RainAndThunder";
    which_logo      = 1;
    update_interval = 40;
    reset();

    SDL_ShowCursor(0);

    if (logo && sdl_logo && fader) {
        audio_manager::get()->play_sound(sound_effect, 0);
        return true;
    }

    return false;
}

void game_state_intro::on_event(SDL_Event& event) {
    event::on_event(event);
}

void game_state_intro::update(int dt) {
    if (istate == INTRO_STATE_FADING_IN) {
        fadeintime -= dt;

        if (fadeintime <= 0) {
            alpha += 0.05f;
            graphics::set_transparency(fader, alpha);
            fadeintime = updateinterval;
        }

        if (alpha >= 1.f) {
            alpha = 1.f;
            graphics::set_transparency(fader, alpha);
            istate = INTRO_STATE_DISPLAYING;
        }
    } else if (istate == INTRO_STATE_DISPLAYING) {
        displaytime -= dt;

        if (displaytime <= 0) {
            istate = INTRO_STATE_FADING_OUT;
        }
    } else if (istate == INTRO_STATE_FADING_OUT) {
        fadeouttime -= dt;

        if (fadeouttime <= 0) {
            alpha -= 0.05f;
            graphics::set_transparency(fader, alpha);
            fadeouttime = updateinterval;
        }

        if (alpha <= 0.f) {
            alpha = 0.f;
            graphics::set_transparency(fader, alpha);

            if (which_logo == 1) {
                reset();
                ++which_logo;
            } else {
                game_state_manager::get().change_state(new game_state_menu());
            }
        }
    }
}

void game_state_intro::draw() {
    if (which_logo == 1) {
        graphics::draw_image(logo, 0, 0);
    } else {
        graphics::draw_image(sdl_logo, 0, 0);
    }

    graphics::draw_image(fader, 0, 0);
}

void game_state_intro::unload() {
    SDL_FreeSurface(logo);
    SDL_FreeSurface(sdl_logo);
    SDL_FreeSurface(fader);
    SDL_ShowCursor(1);

    logo     = nullptr;
    SDL_logo = nullptr;
    fader    = nullptr;

}

void GameStateIntro::OnKeyDown(SDLKey key, SDLMod modifier, Uint16 unicode) {
    if (which_logo == 1) {
        audio_manager::get()->all_channels_fade_out(500);
        ++which_logo;
        graphics::set_transparency(fader, 0.f);
        reset();
    } else {
        game_state_manager::get().change_state(new game_state_menu());
    }
}

void game_state_intro::left_button_down(int mx, int my) {
    if (which_logo == 1) {
        audio_manager::get()->all_channels_fadeout(500);
        ++which_logo;
        graphics::set_transparency(fader, 0.f);
        reset();
    } else {
        game_state_manager::get().change_state(new game_state_menu());
    }
}

void game_state_intro::reset() {
    alpha       = 0.f;
    fadeintime  = 100;
    displaytime = 3000;
    fadeouttime = 100;
    istate      = INTRO_STATE_FADING_IN;
}
