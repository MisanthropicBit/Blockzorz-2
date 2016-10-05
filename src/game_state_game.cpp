#include "game_state_game.hpp"
#include "game_state_menu.hpp"
#include "game_state_pop_up.hpp"
#include "game_state_highscore.hpp"
#include "game.hpp"
#include "game_state_manager.hpp"
#include "graphics.hpp"
#include "audio_manager.hpp"
#include "screen.hpp"
#include "grid.hpp"
#include "particle_effect.hpp"
#include <math.h>
#include <time.h>
#include <iostream>

game_state_game::game_state_game() {
	eye_candy       = nullptr;
	game_field      = nullptr;
	arrow           = nullptr;
	score           = nullptr;
	time            = nullptr;
	combos          = nullptr;
	game_started    = false;
	enter_highscore = false;
}

game_state_game::~game_state_game() {
}

bool game_state_game::load() {
	font.set_font_file("./fonts/biocomv2.ttf", 25);
	eye_candy  = graphics::load_image("./graphics/images/eye_candy.png");
	game_field = graphics::load_image("./graphics/images/game_field.png");
	arrow      = graphics::load_image("./graphics/images/arrow.png", color::white);
	score      = font.load_hq_text_image("score", color::dark_blue);
	time       = font.load_hq_text_image("time", color::dark_blue);
	combos     = font.load_hq_text_image("combos", color::dark_blue);

	quit.load("quit", "./fonts/biocomv2.ttf", color::black, 40, 280, 430);
	quit.set_alpha(0.8f);
	quit.deselect();
	music_button.load("./graphics/animations/music_icon.png", 10, 400);
	sound_button.load("./graphics/animations/sound_icon.png", 70, 400);

	if (audio_manager::get()->music_paused()) {
        music_button.set_frame(1);
    }

	if (!audio_manager::get()->sound_enabled()) {
        sound_button.set_frame(1);
    }

	graphics::set_transparency(eye_candy, 0.5f);

	srand(time(nullptr));

	grid::game_grid().set_width(8);
	grid::game_grid().set_height(14);
	grid::game_grid().spawn();
	player.load("./graphics/images/player.bmp", 7, 3);
	player.set_transparency(0.5f);

	return eye_candy && game_field && arrow && score && time && combos;
}

void game_state_game::on_event(SDL_Event& event) {
	event::on_event(event);
}

void game_state_game::update(int dt) {
	if (!grid::game_grid().is_game_over()) {
		grid::game_grid().update(dt);

		if (!grid::game_grid().spawning() && !game_started) {
			player.set_transparency(0.f);
			clock.start();
			game_started = true;
		}
	} else {
		game_state_highscore gshs;
		gshs.load_highscores("./data/highscores.hs");

		Highscore highscore;
		highscore.name   = "";
		highscore.score  = font::int2string(grid::game_grid().score());
		highscore.combos = font::int2string(grid::game_grid().combos());

		int cpos       = clock.get_pretty_print_time().find(":");
		highscore.mins = clock.get_pretty_print_time().substr(0, cpos);
		highscore.secs = clock.get_pretty_print_time().substr(cpos + 1);

		printf("Lowest score: %d\n", gshs.get_lowest_highscore());

		if (gshs.get_lowest_highscore() >= grid::game_grid().get_score()) {
			game_state_manager::get().change_state(new game_state_menu());
		} else {
			printf("Position: %d\n", gshs.get_score_position(font::string2int(highscore.score)));
			game_state_manager::get().push_state(new game_state_enter_highscore("Enter Name", gshs.get_score_position(font::string2int(highscore.score)), highscore));
		}
	}
}

void game_state_game::draw() {
	screen::get().clear_screen_color(Color::White);

	graphics::draw_image(eye_candy, 450, 111);
	graphics::draw_image(game_field, 220, 50);
	graphics::draw_image(score, 110, 55);
	font.draw_hq_text(font::int2string(grid::game_grid().score()), color::dark_blue, 120, 80);
	graphics::draw_image(time, 110, 55 + 3 * 20);
	font.draw_hq_text(clock.get_pretty_print_time(), color::dark_blue, 120, 60 + 4 * 20);
	graphics::draw_image(combos, 110, 55 + 6 * 20);
	font.draw_hq_text(font::int2string(grid::game_grid().combos()), Color::DarkBlue, 120, 60 + 7 * 20);
	graphics::draw_image(arrow, 430, 50 + grid::game_grid().highest_block() * 25 - arrow->w/2);

	quit.draw();
	music_button.draw();
	sound_button.draw();

	grid::game_grid().draw();
	player.draw();
}

void game_state_game::unload() {
	grid::game_grid().despawn();

	SDL_FreeSurface(eye_candy);
	SDL_FreeSurface(game_field);
	SDL_FreeSurface(arrow);
	SDL_FreeSurface(score);
	SDL_FreeSurface(time);
	SDL_FreeSurface(combos);

	EyeCandy  = nullptr;
	Gamefield = nullptr;
	Arrow     = nullptr;
	Score	  = nullptr;
	Time	  = nullptr;
	Combos	  = nullptr;
}

void game_state_game::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
	if (!grid::game_grid().spawning()) {
		switch (key) {
			case SDLK_UP:
				if (player.row() != 0) {
                    player.row() -= 1;
                }
				break;

			case SDLK_DOWN:
				if (player.row() != GRID_MAX_ROWS - 1) {
                    player.row() += 1;
                }
				break;

			case SDLK_LEFT:
				if (player.coloumn() != 0) {
                    player.coloumn() -= 1;
                }
				break;

			case SDLK_RIGHT:
				if (player.column() != GRID_MAX_COLUMNS - 2) {
                    player.column() += 1;
                }
				break;

			case SDLK_SPACE:
				grid::game_grid().swap_blocks(player.row(), player.column());
				break;

			case SDLK_s:
				if (audio_manager::get()->sound_enabled()) {
					sound_button.set_frame(1);
					audio_manager::get()->all_channels_fadeout(1000);
					audio_manager::get()->disable_sounds();
				} else {
					sound_button.set_frame(0);
					if (game::game_settings.sound_volume != 0) {
                        audio_manager::get()->enable_sounds();
                    }
				}
				break;

			case SDLK_m:
				if (!audio_manager::get()->music_paused()) {
					music_button.set_frame(1);
					audio_manager::get()->pause_music();
				} else if (!audio_manager::get()->music_playing()) {
					music_button.set_frame(0);

					if(game::game_settings.music_volume != 0) {
                        audio_manager::get()->fadein("tetris_attack", -1, 1000);
                    }
				}
				break;

			case SDLK_q:
				game_state_manager::get().push_state(new game_state_popup("Return to Main Menu?", "Are you sure you want to quit?", "Yes", "No, go back", new game_state_menu()));
				break;

			case SDLK_BACKSPACE:
				game_state_manager::get().push_state(new game_state_popup("Return to Main Menu?", "Are you sure you want to quit?", "Yes", "No, go back", new game_state_menu()));
				break;

			case SDLK_d:
				grid::game_grid().print_grid();
				break;
		}
	}
}

void game_state_game::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
	if (!grid::game_grid().spawning()) {
		int gridcol = (mx - 220) / 25;
		int gridrow = (my - 50) / 25;

		if (gridcol >= 0 && gridcol < GRID_MAX_COLUMNS - 1) {
            player.column() = gridcol;
        }

		if (gridrow >= 0 && gridrow < GRID_MAX_ROWS) {
            player.row() = gridrow;
        }
	}

	quit.mouse_move(mx, my);
}

void game_state_game::left_button_down(int mx, int my) {
	if (mx >= 220 && mx < 420 && my >= 50 && my < 400) {
		if ((mx - 220) / 25 != 7) {
            grid::game_grid().swap_blocks((my - 50) / 25, (mx - 220) / 25);
        } else if ((mx - 220) / 25 == 7) {
			grid::game_grid().swap_blocks((my - 50) / 25, 6);
        }
	} else if(mx >= 10 && mx <= 62 && my >= 400 && my <= 452) {
		if (audio_manager::get()->music_playing()) {
			music_button.set_frame(1);
			audio_manager::get()->pause_music();
		} else if (audio_manager::get()->music_paused() || !audio_manager::get()->music_playing()) {
			music_button.set_frame(0);

			if (game::game_settings.music_volume != 0) {
                audio_manager::get()->fadein("tetris_attack", -1, 1000);
            }
		}
	} else if (mx >= 70 && mx <= 122 && my >= 400 && my <= 452) {
		if (audio_manager::get()->sound_enabled()) {
			sound_button.set_frame(1);
			audio_manager::get()->all_channels_fade_out(500);
			audio_manager::get()->disable_sounds();
		} else {
			sound_button.set_frame(0);

			if (game::game_settings.sound_volume != 0) {
                audio_manager::get()->enable_sounds();
            }
		}
	} else if (quit.has_mouse_hover(mx, my)) {
		game_state_manager::get().push_state(new game_state_popup("Return to Main Menu?", "Are you sure you want to quit?", "Yes", "No, go back", new game_state_menu()));
	}
}
