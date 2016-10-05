#include "game_state_options.hpp"
#include "game_state_menu.hpp"
#include "game_state_manager.hpp"
#include "audio_manager.hpp"
#include "graphics.hpp"
#include "screen.hpp"
#include "game.hpp"
#include <math.h>

game_state_options::game_state_options() {
    eye_candy  = nullptr;
    title      = nullptr;
    cursor     = nullptr;
    music      = nullptr;
    sound      = nullptr;
    video_mode = nullptr;
}

game_state_options::~game_state_options() {
}

bool game_state_options::load() {
    font title_font("./fonts/biocomv2.ttf", 40);
    font.set_font_file("./fonts/biocomv2.ttf", 20);
    eye_candy  = graphics::load_image("./images/eye_candy.png");
    title      = title_font.load_hq_text_image("Options",    color::dark_blue);
    cursor     = graphics::load_image("./images/cursor.png", color::white);
    music      = font.load_hq_text_image("Music Volume:",    color::black);
    sound      = font.load_hq_text_image("Sound Volume:",    color::black);
    video_mode = font.load_hq_text_image("Video Mode:",      color::black);

    graphics::set_transparency(eye_candy, 0.5f);

    back_button.load("Back", "./fonts/biocomv2.ttf", color::black, 30, 290, 400);
    back_button.set_alpha(0.8f);
    back_button.deselect();
    musicvolume.load("./Graphics/Images/Slider.png", 150, 110, 0, 100);
    soundvolume.load("./Graphics/Images/Slider.png", 150, 210, 0, 100);
    videomode.load("./Fonts/biocomv2.ttf", Color::Black, 20, 300, 300);
    videomode.set_alpha(0.8f);
    videomode.add_selection("Windowed Mode");
    videomode.add_selection("Fullscreen");

    if (game::game_settings.fullscreen) {
        videomode.set_selection("Fullscreen");
    }

    if (audio_manager::get()->music_paused() || !audio_manager::get()->music_playing()) {
        music_volume = 0;
    } else {
        music_volume = game::game_settings.music_volume;
    }

    //if(AudioManager::GetManager()->IsSoundEnabled())
        sound_volume = game::game_settings.sound_volume;
    //else
        //svolume = 0;

    fullscreen = game::game_settings.fullscreen;
    music_volume.set_value(music_volume);
    sound_volume.set_value(sound_volume);
    selected = 0;
    titlex   = screen::get().width()/2 - titlefont.string_width("Options")/2;
    cx       = 255;
    cy       = 400;
    offsetx  = 0.f;
    offsety  = 0.f;
    angle    = 0.f;

    titlefont.close();

    return eye_candy && title && cursor && music && sound && video_mode;
}

void game_state_options::on_event(SDL_Event& event) {
    event::on_event(event);
}

void game_state_options::update(int dt) {
    angle += 0.005f * dt;

    if(angle > 360.f) {
        angle -= 360.f; // Cap the angle
    }

    offsetx = 10.f * std::cos(angle);
    offsety = 10.f * std::sin(angle);
}

void game_state_options::draw() {
    screen::get().clear_screen_color(Color::White);

    graphics::draw_image(title, titlex, 10.f);
    graphics::draw_image(eye_candy, 450, 111);

    graphics::draw_image(Music, 150, 80);
    font.draw_hq_text(font::int2string(music_volume.value()) + " %", color::black, 380, 80);
    music_volume.draw();

    graphics::draw_image(sound, 150, 180);
    font.draw_hq_text(font::int2string(sound_volume.value()) + " %", color::black, 380, 180);
    sound_volume.draw();

    graphics::draw_image(video_mode, 150, 300);
    video_mode.draw();

    back_button.draw();
    graphics::draw_image(cursor, cx + offsetx, cy + offsety);
}

void game_state_options::unload() {
    game::game_settings.music_volume = music_volume.value();
    game::game_settings.sound_volume = sound_volume.value();

    if (video_mode.selection() == "Windowed Mode") {
        game::game_settings.fullscreen = false;
    } else {
        game::games_ettings.fullscreen = true;
    }

    font.close();

    SDL_FreeSurface(eye_candy);
    SDL_FreeSurface(title);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(music);
    SDL_FreeSurface(sound);
    SDL_FreeSurface(video_mode);

    eye_candy  = nullptr;
    title      = nullptr;
    cursor     = nullptr;
    music      = nullptr;
    sound      = nullptr;
    video_mode = nullptr;
}

void game_state_options::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
    game_state_manager::get().change_state(new game_state_menu());
}

void game_state_options::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
    music_volume.mouse_move(mx, my, relx, rely, state);
    sound_volume.mouse_move(mx, my, relx, rely, state);
    video_mode.mouse_move(mx, my);
    back_button.mouse_move(mx, my);

    if (music_volume.value() != music_volume) {
        music_volume = musi_volume.value();

        if (music_volume == 0) {
            audio_manager::get()->pause_music();
        } else {
            if (audio_manager::get()->music_paused()) {
                audio_manager::get()->resume_music();
            }

            audio_manager::get()->set_music_volume(MIX_MAX_VOLUME * mvolume / 100);
        }
    }
}

void game_state_options::left_button_down(int mx, int my) {
    music_volume.left_button_down(mx, my);
    sound_volume.left_button_down(mx, my);
    video_mode.left_button_down(mx, my);

    if (video_mode.selection() == "Fullscreen" && !fullscreen) {
        screen::get().set_video_resolution(640, 480, 0, SDL_FULLSCREEN | SDL_SWSURFACE);
        fullscreen = true;
    } else if (video_mode.selection() == "Windowed Mode" && fullscreen) {
        screen::get().set_video_resolution(640, 480, 0, SDL_SWSURFACE);
        fullscreen = false;
    }

    if (back_button.has_mouse_hover(mx, my)) {
        game_state_manager::get().change_state(new game_state_menu());
    }
}

void game_state_options::left_button_up(int mx, int my) {
    music_volume.left_button_up(mx, my);
    sound_volume.left_button_up(mx, my);

    if (sound_volume.value() != sound_volume) {
        if (sound_volume == 0 || !audio_manager::get()->sound_enabled()) {
            audio_manager::get()->enable_sounds();
        }

        sound_volume = sound_volume.value();

        if (sound_volume == 0) {
            audio_manager::get()->disable_sounds();
        } else {
            audio_manager::get()->set_sound_volume(MIX_MAX_VOLUME * svolume / 100.f);
            audio_manager::get()->play_sound("click", 0);
        }
    }
}
