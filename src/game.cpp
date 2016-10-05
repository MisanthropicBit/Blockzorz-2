#include "game.hpp"
#include "screen.hpp"
#include <SDL_ttf.h>
#include "audio_manager.hpp"
#include "game_state_intro.hpp"
#include "game_state_manager.hpp"
#include "font.hpp"
#include <fstream>
#include <iostream>

settings game::game_settings;

game::game() {
}

game::~game() {
}

int game::run()
{
	if (!initialize()) {
        return -1;
    }

	while (game_state_manager::get().is_running()) {
		while (SDL_PollEvent(&event)) {
			handle_event();
		}

		update();
		draw();
	}

	clean_up();
	return 0;
}

bool game::initialize() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        return false;
    }

	// Load TTF
	if (TTF_Init() == -1) {
        return false;
    }

	// Load the audiomanager...
	if (!audio_manager::load_audio_manager(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1000)) {
        return false;
    }

	// ...and sounds
	audio_manager::load_sounds("./sounds/sounds.txt");
	audio_manager::load_music("./music/music.txt");
	audio_manager::get()->allocate_channels(2);

	// Set settings to default values
	game::game_settings.music_volume     = 50;
	game::game_settings.sound_volume     = 50;
	game::game_settings.full_screen      = false;
	game::game_settings.cf_mode_unlocked = false;

	debug_text.set_font_file("./fonts/biocomv2.ttf", 20);

    std::ifstream file("./data/settings.b2s");
    std::string line;
    std::string temp;
	int counter = 0;
    std::size_t npos = 0;

	if (file.is_open()) {
        std::getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);
		game::game_settings.music_volume = font::string2int(temp);

        std::getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);
		game::game_settings.sound_volume = font::string2int(temp);

        std::getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);

		if (font::string2int(temp) == 1) {
            game::game_settings.fullscreen = true;
        } else {
			game::game_settings.fullscreen = false;
        }

        std::getline(file, line);
		npos = line.find_first_of(":");
		temp = line.substr(npos + 1);
		
		if (font::string2int(temp) == 1) {
			game::gamesettings.cf_mode_unlocked = true;
        } else {
			game::gamesettings.cf_mode_unlocked = false;
        }
	} else {
        std::cerr << "Error: Failed to load game settings" << std::endl
			      << "File: " << file << std::endl;
	}

	audio_manager::get()->set_sound_volume(MIX_MAX_VOLUME * game::game_settings.sound_volume / 100.f);
	audio_manager::get()->set_music_volume(MIX_MAX_VOLUME * game::game_settings.music_volume / 100.f);

	// Create the screen
	if (game::game_settings.full_screen) {
		if (!screen::create_screen(640, 480, 0, SDL_FULLSCREEN | SDL_HWSURFACE)) {
            return false;
        }
	} else {
		if (!screen::create_screen(640, 480, 0, SDL_SWSURFACE)) {
            return false;
        }
	}

	screen::get().set_caption("Blockzorz 2 (" + VERSION + ")");
	screen::get().set_icon("./graphics/images/icon.bmp");
	game_state_manager::get().change_state(new game_state_intro());

	return true;
}

void game::handle_event() {
	GameStateManager::get().pass_event(event);
}

void game::update() {
	int dt = game_timer.delta_time();
	game_timer.update();
	game_state_manager::get().update_states(dt);
}

void game::draw() {
	game_state_manager::get().draw_states();
	screen::get().update_screen();

	debug_text.draw_hq_text("FPS: " + font::int2string(game_timer.fps()), color::dark_blue, 5, 5);
}

void game::clean_up() {
	// Save settings
    std::ofstream file;
    file.open("./Data/settings.b2s", ios::trunc); // Clear last save

	if (file.is_open()) {
        file.close();
    }

	file.open("./data/settings.b2s");

	if (file.is_open()) {
		file << "MusicVolume:" << font::int2string(game::game_settings.music_volume) << std::endl;
		file << "SoundVolume:" << font::int2string(game::game_settings.sound_volume) << std::endl;

		if (game::game_settings.full_screen) {
            file << "Fullscreen:1" << std::endl;
        } else {
			file << "Fullscreen:0" << std::endl;
        }

		if (game::game_settings.cf_mode_unlocked) {
            file << "ModeUnlocked:1";
        } else {
            file << "ModeUnlocked:0";
        }

		file.close();
	} else {
        std::cerr << "Error: Failed to save settings" << std::endl;
	}

	game_state_manager::get().clean_up_states();
	audio_manager::un_load_sounds();
	audio_manager::un_load_music();
	TTF_Quit();
	screen::destroy_screen();

	SDL_Quit();
}

// Main function
int main(int argc, char* args[]) {
	game game;

	return game.run();
}
