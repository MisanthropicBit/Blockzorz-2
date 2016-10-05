#include "game_state_menu.hpp"
#include "graphics.hpp"
#include "game_state_game.hpp"
#include "game_state_popup.hpp"
#include "game_state_highscore.hpp"
#include "game_state_options.hpp"
#include "game_state_how_to_play.hpp"
#include "game_state_manager.hpp"
#include "audio_manager.hpp"
#include "color.hpp"
#include "font.hpp"
#include "screen.hpp"
#include "game.hpp"
#include <math.h>
#include <iostream>

game_state_menu::game_state_menu() {
	eye_candy = nullptr;
	title     = nullptr;
	cursor    = nullptr;
	popup     = nullptr;
}

bool game_state_menu::load() {
	font font("./fonts/biocomv2.ttf", 60);
	eye_candy = graphics::load_image("./images/eye_candy.png");
	title     = font.load_hq_text_image("BlockZorz 2", color::dark_blue);
	cursor    = graphics::load_image("./images/cursor.png", color::white);
	popup     = graphics::load_image("./images/popup.png", color::magenta);

	graphics::set_transparency(eye_candy, 0.5f);

	buttons[0].load("Play",        "./fonts/biocomv2.ttf", color::black, 50, 180, 130);
	buttons[1].load("Highscores",  "./fonts/biocomv2.ttf", color::black, 50, 180, 190);
	buttons[2].load("Options",     "./fonts/biocomv2.ttf", color::black, 50, 180, 250);
	buttons[3].load("How to play", "./fonts/biocomv2.ttf", color::black, 50, 180, 310);
	buttons[4].load("Quit",        "./fonts/biocomv2.ttf", color::black, 50, 180, 370);
	buttons[0].set_alpha(0.f);
	buttons[1].set_alpha(0.8f);
	buttons[2].set_alpha(0.8f);
	buttons[3].set_alpha(0.8f);
	buttons[4].set_alpha(0.8f);

	// Set sound volume again, to ensure correct sound volume. This is because AllChannelsFadeOut(500)
	// is potentially called from the GameStateIntro when a key is pressed or the left mouse button is
	// clicked, and this sets the sound volume to 80.
	audio_manager::get()->set_sound_volume(MIX_MAX_VOLUME * game::game_settings.sound_volume / 100.f);

	titlex   = screen::get().width() / 2 - font.string_width("BlockZorz 2")/2;
	selected = 0;
	cx       = 145;
	cy       = 130;
	offsetx  = 0.f;
	offsety  = 0.f;
	angle    = 0.f;

	font.close();

	if (eye_candy && title && cursor) {
		if (!audio_manager::get()->music_paused() && !audio_manager::get()->music_playing()) {
            audio_manager::get()->play_music("tetris_attack", -1);
        }

		return true;
	}

	return false;
}

void game_state_menu::on_event(SDL_Event& event) {
	event::on_event(event);
}

void game_state_menu::update(int dt) {
	angle += 0.005f * dt;

	if (angle > 360.f) {
        angle -= 360.f; // Cap the angle
    }

	offsetx = 10.f * std::cos(angle);
	offsety = 10.f * std::sin(angle);
}

void game_state_menu::draw() {
	screen::get().clear_screen_color(color::white);

	graphics::draw_image(eye_candy, 450, 111);
	graphics::draw_image(title, titlex, 20);
	graphics::draw_image(cursor, cx + offsetx, cy + offsety);

	for (int i = 0; i < 5; i++) {
		buttons[i].draw();
	}
}

void game_state_menu::unload() {
	SDL_FreeSurface(eye_candy);
	SDL_FreeSurface(title);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(popup);

	eye_candy = nullptr;
	title     = nullptr;
	cursor    = nullptr;
	popup     = nullptr;
}

void game_state_menu::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
	if (SDL_GetKeyState(nullptr)[SDLK_c] && SDL_GetKeyState(nullptr)[SDLK_f]) {
		if (!game::game_settings.cf_mode_unlocked) {
			game::game_settings.cf_mode_unlocked = true;
			game_state_manager::get().push_state(new game_state_mode_unlocked("Mode Unlocked!", "Captain Falcon Mode unlocked!", nullptr));
		} else {
            game::game_settings.cf_mode_unlocked = false;    
        }
	}

	switch(key) {
		case SDLK_UP:
			buttons[selected].set_alpha(0.8f);

			if (selected == 0) {
                selected = 4;
            } else {
                --selected;
            }

			audio_manager::get()->play_sound("click", 0);
			buttons[selected].set_alpha(0.f);
			cy = 130 + selected * 60;
			break;

		case SDLK_DOWN:
			buttons[selected].SetAlpha(0.8f);

			if (selected == 4) {
                selected = 0;
            } else {
				++selected;
            }

			audio_manager::get()->play_sound("click", 0);
			buttons[selected].set_alpha(0.f);
			cy = 130 + selected * 60;
			break;

		case SDLK_RETURN:
			if (selected == 0) {
                game_state_manager::get().change_state(new game_state_game());
            } else if (selected == 1) {
                game_state_manager::get().change_state(new game_state_highscore());
            } else if (selected == 2) {
                game_state_manager::get().change_state(new game_state_options());
            } else if (selected == 3) {
                game_state_manager::get().change_state(new game_state_how_to_play());
            } else if (selected == 4) {
                game_state_manager::get().push_state(new game_state_popup("Exit Game", "Are you sure you want to quit?", "Yes", "No", nullptr));
            }

			break;

		default:
			break;
	}
}

void game_state_menu::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
	for (int i = 0; i < 5; ++i) {
		if (buttons[i].has_mouse_hover(mx, my)) {
			if (selected != i) {
				buttons[selected].set_alpha(0.8f);
				audio_manager::get()->play_sound("click", 0);
			}

			buttons[i].set_alpha(0.f);
			selected = i;
			cy = 130 + i * 60;
			return;
		} else {
			if (selected != i) {
                buttons[i].set_alpha(0.8f);
            }
		}
	}
}

void game_state_menu::left_button_down(int mx, int my) {
	if (buttons[0].has_mouse_hover(mx, my)) {
		game_state_manager::get().change_state(new game_state_game());
	} else if (buttons[1].has_mouse_hover(mx, my)) {
		game_state_manager::get().change_state(new game_state_highscore());
	} else if (buttons[2].has_mouse_hover(mx, my)) {
		game_state_manager::get().change_state(new game_state_options());
	} else if (buttons[3].has_mouse_hover(mx, my)) {
		game_state_manager::get().change_state(new game_state_how_to_play());
	} else if (buttons[4].has_mouse_hover(mx, my)) {
		game_state_manager::get().push_state(new game_state_popup("Exit Game", "Are you sure you want to quit?", "Yes", "No", nullptr));
	}
}
