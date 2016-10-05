#include "game_state_how_to_play.hpp"
#include "font.hpp"
#include "graphics.hpp"
#include "game_state_menu.hpp"
#include "game_state_manager.hpp"
#include "audio_manager.hpp"
#include "screen.hpp"
#include <math.h>

game_state_how_to_play::game_state_how_to_play() {
	eye_candy = nullptr;
	title     = nullptr;
	cursor    = nullptr;
	line1     = nullptr;
	line2     = nullptr;
	line3     = nullptr;
	line4     = nullptr;
	line5     = nullptr;
	line6     = nullptr;
	line7     = nullptr;
	line8     = nullptr;
}

game_state_how_to_play::~game_state_how_to_play() {
}

bool game_state_how_to_play::load() {
	font title_font("./fonts/biocomv2.ttf", 40);
	font font("./fonts/biocomv2.ttf", 20);

	eye_candy = graphics::load_image("./images/eye_candy.png");
	cursor    = graphics::load_image("./images/cursor.png", color::white);
	title     = title_font.load_hq_text_image("How to play", color::dark_blue);

	graphics::set_transparency(eye_candy, 0.5f);

	line1 = font.load_hq_text_image("- Blocks fall from the top of the screen",            color::black);
	line2 = font.load_hq_text_image("- No blocks must reach above the red line",           color::black);
	line3 = font.load_hq_text_image("- Press space or use the mouse to swap blocks",       color::black);
	line4 = font.load_hq_text_image("- Line up 3 or more blocks in any compass direction", Color::black);
	line5 = font.load_hq_text_image("  to score points",                                   color::black);
	line6 = font.load_hq_text_image("- Connecting more than 3 blocks counts as a combo",   color::black);
	line7 = font.load_hq_text_image("- Combos boost your final score",                     color::black);
	line8 = font.load_hq_text_image("  when the game is over",                             Color::Black);

	back_button.load("Back", "./fonts/biocomv2.ttf", color::black, 30, 290, 400);
	back_button.set_alpha(0.8f);
	back_button.deselect();

	titlex  = screen::get().width()/2 - title_font.string_width("How to play")/2;
	textx   = 50;
	texty   = 90;
	cx      = 255;
	cy      = 400;
	offsetx = 0.f;
	offsety = 0.f;
	angle   = 0.f;

	font.close();

	return Title && Line1 && Line2 && Line3 && Line4 && Line5 && Line6 && Line7 && Line8;
}

void game_state_how_to_play::on_event(SDL_Event& event) {
	event::on_event(event);
}

void game_state_how_to_play::update(int dt) {
	angle += 0.005f * dt;

	if (angle > 360.f) {
        angle -= 360.f; // Cap the angle
    }

	offsetx = 10.f * cos(angle);
	offsety = 10.f * sin(angle);
}

void game_state_how_to_play::draw() {
	screen::get().clear_screen_color(color::white);

	back_button.draw();
	graphics::draw_image(eye_candy, 450, 111);
	graphics::draw_image(title, titlex, 10.f);
	graphics::draw_image(cursor, cx + offsetx, cy + offsety);
	graphics::draw_image(line1, textx, texty);
	graphics::draw_image(line2, textx, texty + 20);
	graphics::draw_image(line3, textx, texty + 20 * 2);
	graphics::draw_image(line4, textx, texty + 20 * 3);
	graphics::draw_image(line5, textx, texty + 20 * 4);
	graphics::draw_image(line6, textx, texty + 20 * 6);
	graphics::draw_image(line7, textx, texty + 20 * 7);
	graphics::draw_image(line8, textx, texty + 20 * 8);
}

void game_state_how_to_play::unload() {
	SDL_FreeSurface(eye_candy);
	SDL_FreeSurface(title);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(line1);
	SDL_FreeSurface(line2);
	SDL_FreeSurface(line3);
	SDL_FreeSurface(line4);
	SDL_FreeSurface(line5);
	SDL_FreeSurface(line6);
	SDL_FreeSurface(line7);
	SDL_FreeSurface(line8);

	eye_candy = nullptr;
	title     = nullptr;
	cursor    = nullptr;
	line1     = nullptr;
	line2     = nullptr;
	line3     = nullptr;
	line4     = nullptr;
	line5     = nullptr;
	line6     = nullptr;
	line7     = nullptr;
	line8     = nullptr;
}

void game_state_how_to_play::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
	game_state_manager::get().change_state(new game_state_menu());
}

void game_state_how_to_play::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
	back_button.mouse_move(mx, my);
}

void game_state_how_to_play::left_button_down(int mx, int my) {
	if (back_button.has_mouse_hover(mx, my)) {
		game_state_manager::get().change_state(new game_state_menu());
	}
}
