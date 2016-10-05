#include "game_state_highscore.hpp"
#include "game_state_menu.hpp"
#include "game_state_manager.hpp"
#include "audio_manager.hpp"
#include "graphics.hpp"
#include "screen.hpp"
#include <fstream>
#include <iostream>
#include <math.h>

game_state_highscore::game_state_highscore() {
    EyeCandy    = nullptr;
    Title       = nullptr;
    Cursor      = nullptr;
    GoldBlock   = nullptr;
    SilverBlock = nullptr;
    BronzeBlock = nullptr;

    for (int i = 0; i < MAX_HIGHSCORES; ++i) {
        highscores[i].name   = "";
        highscores[i].score  = "";
        highscores[i].combos = "";
        highscores[i].mins   = "";
        highscores[i].secs   = "";
    }
}

game_state_highscore::~game_state_highscore() {
}

bool game_state_highscore::load() {
    font title_font("./fonts/biocomv2.ttf", 40);
    eye_candy    = graphics::load_image("./Graphics/Images/EyeCandy.png");
    title        = title_font.load_hq_text_image("highscores", color::dark_blue);
    cursor       = graphics::load_image("./images/cursor.png", color::white);
    gold_block   = graphics::load_image("./images/gold_block.png");
    silver_block = graphics::load_image("./images/silver_block.png");
    bronze_block = graphics::LoadImage("./images/bronze_block.png");

    graphics::set_transparency(eye_candy, 0.5f);
    titlex = screen::get().width() / 2 - title_font.string_width("highscores")/2;
    
    subtitlefont.set_font_file("./fonts/biocomv2b.ttf", 20);
    font.set_font_file("./fonts/biocomv2.ttf", 20);

    back_button.load("Back", "./fonts/biocomv2.ttf", Color::Black, 30, 290, 400);
    back_button.set_alpha(0.8f);
    back_button.deselect();

    titlefont.Close();

    cx      = 255;
    cy      = 400;
    offsetx = 0.f;
    offsety = 0.f;
    angle   = 0.f;


    return load_highscores("./data/highscores.hs");
}

void game_state_highscore::on_event(SDL_Event& event) {
    event::on_event(event);
}

void game_state_highscore::update(int dt) {
    angle += 0.005f * dt;

    if(angle > 360.f) {
        // Cap the angle
        angle -= 360.f;
    }

    offsetx = 10.f * std::cos(angle);
    offsety = 10.f * std::sin(angle);
}

void game_state_highscore::draw() {
    screen::get().clear_screen_color(color::white);

    graphics::draw_image(Title, titlex, 10.f);

    graphics::draw_image(eye_candy, 450, 111);
    graphics::draw_image(cursor, cx + offsetx, cy + offsety);
    graphics::draw_image(gold_block, 36, 99);
    graphics::draw_image(silver_block, 36, 99 + 1.5 * font.recommended_spacing());
    graphics::draw_image(bronze_block, 36, 99 + 3 * font.recommended_spacing());
    back_button.draw();

    subtitle_font.draw_hq_text("Name",   color::dark_blue, 70, 70);
    subtitle_font.draw_hq_text("Score",  color::dark_blue, 230, 70);
    subtitle_font.draw_hq_text("Combos", color::dark_blue, 330, 70);
    subtitle_font.draw_hq_text("Time",   color::dark_blue, 430, 70);

    // 1st place
    font.draw_hq_text("1.", color::gold, 10, 100);
    font.draw_hq_text(highscores[0].name,                                           color::gold, 70, 100);
    font.draw_hq_text(highscores[0].score,                                          color::gold, 230, 100);
    font.draw_hq_text(highscores[0].combos,                                         color::gold, 330, 100);
    font.draw_hq_text(highscores[0].mins + " mins " + highscores[0].secs + " secs", color::gold, 430, 100);

    // 2nd place
    font.draw_hq_text("2.",                                                         color::silver, 10, 100 + 1.5 * font.recommended_spacing());
    font.draw_hq_text(highscores[1].name,                                           color::silver, 70, 100 + 1.5 * font.recommended_spacing());
    font.draw_hq_text(highscores[1].score,                                          color::silver, 230, 100 + 1.5 * font.recommended_spacing());
    font.draw_hq_text(highscores[1].combos,                                         color::silver, 330, 100 + 1.5 * font.recommended_spacing());
    font.draw_hq_text(highscores[1].mins + " mins " + Highscores[1].secs + " secs", color::silver, 430, 100 + 1.5 * font.recommended_spacing());

    // 3rd place
    font.draw_hq_text("3.",                                                         color::bronze, 10, 100 + 3 * font.recommended_spacing());
    font.draw_hq_text(highscores[2].name,                                           color::bronze, 70, 100 + 3 * font.recommended_spacing());
    font.draw_hq_text(highscores[2].score,                                          color::bronze, 230, 100 + 3 * font.recommended_spacing());
    font.draw_hq_text(highscores[2].combos,                                         color::bronze, 330, 100 + 3 * font.recommended_spacing());
    font.draw_hq_text(highscores[2].mins + " mins " + Highscores[2].secs + " secs", color::bronze, 430, 100 + 3 * font.recommended_spacing());

    for(int i = 3; i < MAX_HIGHSCORES; ++i) {
        font.draw_hq_text(font::int2string(i + 1) + ".",                                color::dark_blue, 10, 100 + (i + 1.5) * font.recommended_spacing());
        font.draw_hq_text(highscores[i].name,                                           color::black, 70,     100 + (i + 1.5) * font.recommended_spacing());
        font.draw_hq_text(highscores[i].score,                                          color::black, 230,    100 + (i + 1.5) * font.recommended_spacing());
        font.draw_hq_text(highscores[i].combos,                                         color::black, 330,    100 + (i + 1.5) * font.recommended_spacing());
        font.draw_hq_text(highscores[i].mins + " mins " + highscores[i].secs + " secs", color::black, 430,    100 + (i + 1.5) * font.recommended_spacing());
    }
}

void game_state_highscore::unload() {
    subtitle_font.close();
    font.Close();

    SDL_FreeSurface(EyeCandy);
    SDL_FreeSurface(title);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(gold_block);
    SDL_FreeSurface(silver_block);
    SDL_FreeSurface(bronze_block);

    eye_candy    = nullptr;
    title        = nullptr;
    cursor       = nullptr;
    gold_block   = nullptr;
    silver_block = nullptr;
    bronze_block = nullptr;
}

void game_state_highscore::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
    game_state_manager::get().change_state(new game_state_menu());
}

void game_state_highscore::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
    backbutton.mouse_move(mx, my);
}

void game_state_highscore::left_button_down(int mx, int my) {
    if (back_button.has_mouse_hover(mx, my)) {
        game_state_manager::get().change_state(new game_state_menu());
    }
}

void game_state_highscore::save_highscores(const std::string& filename) {
    if (filename.empty()) {
        return;
    }

    std::ofstream file(filename.c_str(), ios_base::trunc); // Open file with truncation
    std::string line;
    std::size_t npos = 0;
    int counter      = 0;

    if (file.is_open()) {
        for(int i = 0; i < MAX_HIGHSCORES; ++i) {
            file << highscores[i].name << "|" << highscores[i].score << "|" << highscores[i].combos << "|"
                 << highscores[i].mins << "|" << highscores[i].secs << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Error: Unable to open " << filename << " for saving highscores" << std::endl;
    }
}

bool game_state_highscore::load_highscores(const std::string& filename) {
    if (filename.empty()) {
        return false;
    }

    // Highscore format:
    // Name|score|combos|mins|secs
    std::ifstream file(filename.c_str());
    std::string line;
    std::size_t npos = 0;
    int counter      = 0;

    if (file.is_open()) {
        while (!file.eof() && counter != MAX_HIGHSCORES) {
            std::getline(file, line);

            npos = line.find_first_of("|");
            highscores[counter].name = line.substr(0, npos);
            line = line.substr(npos + 1);
            npos = line.find_first_of("|");
            highscores[counter].score = line.substr(0, npos);
            line = line.substr(npos + 1);
            npos = line.find_first_of("|");
            highscores[counter].combos = line.substr(0, npos);
            line = line.substr(npos + 1);
            npos = line.find_first_of("|");
            highscores[counter].mins = line.substr(0, npos);
            line = line.substr(npos + 1);
            highscores[counter].secs = line.substr(0);

            ++counter;
        }

        file.close();
        return true;
    } else {
        return false;
    }
}

void game_state_highscore::pass_new_highscore(int position, highscore highscore) {
    if (position > 9 || position < 0) {
        return;
    }

    if (position == 9) {
        Highscores[9] = highscore;
        return;
    }

    highscore temp[10];

    for(int i = position; i < MAX_HIGHSCORES; ++i) {
        temp[i].name   = highscores[i].name;
        temp[i].score  = highscores[i].score;
        temp[i].combos = highscores[i].combos;
        temp[i].mins   = highscores[i].mins;
        temp[i].secs   = highscores[i].secs;
    }
    
    highscores[position].name   = highscore.name;
    highscores[position].score  = highscore.score;
    highscores[position].combos = highscore.combos;
    highscores[position].mins   = highscore.mins;
    highscores[position].secs   = highscore.secs;

    for(int j = position, i = position + 1; i < MAX_HIGHSCORES; ++i) {
        highscores[i].name   = temp[j].name;
        highscores[i].score  = temp[j].score;
        highscores[i].combos = temp[j].combos;
        highscores[i].mins   = temp[j].mins;
        highscores[i].secs   = temp[j].secs;
        ++j;
    }

    save_highscores("./data/highscores.hs");
}

int game_state_highscore::lowest_highscore() const {
    return font::string2int(highscores[9].score);
}

int GameStateHighscore::GetScorePosition(int score) {
    if (score < font::string2int(highscores[9].score)) {
        return -1;
    }

    // Locate new position
    for (int i = 0; i < 10; ++i) {
        if (score > font::string2int(highscores[i].score)) {
            return i;
        }
    }
}

game_state_enter_highscore::game_state_enter_highscore(const std::string& caption, int position, highscore score) : game_state_pop_up() {
    Font title_font("./fonts/biocomv2.ttf", 30);
    textfont.set_font_file("./fonts/biocomv2.ttf", 20);
    std::string place_postfix = "";

    if (position == 0) {
        place_postfix = "st";
    } else if (position == 1) {
        place_postfix = "nd";
    } else if (position == 2) {
        place_postfix = "rd";
    } else {
        place_postfix = "th";
    }

    title = title_font.load_hq_text_image(caption, color::dark_blue);
    text  = text_font.load_hq_text_image("You got " + font::int2string(position + 1) + place_postfix + " place!", color::black);
    this->position = position;

    this->score.name   = "";
    this->score.score  = score.score;
    this->score.combos = score.combos;
    this->score.mins   = score.mins;
    this->score.secs   = score.secs;
    submit.load("Submit", "./fonts/biocomv2.ttf", color::black, 25, screen::get().width()/2 - text_font.string_width("Submit") / 2, 290);
    submit.set_alpha(0.8f);

    returnstate = nullptr;

    titlex = screen::get().width()/2 - title_font.string_width(caption)/2;
    textx  = screen::get().width()/2 - text_font.string_width("You got " + font::int2string(position + 1) + place_postfix + " place!")/2;

    titlefont.close();
}

game_state_enter_highscore::~game_state_enter_highscore() {
}

bool game_state_enter_highscore::load() {
    if (game_state_popup::load()) {
        SDL_EnableUNICODE(SDL_ENABLE);
        return true;
    }
    
    return false;
}

void game_state_enter_highscore::on_event(SDL_Event& event) {
    event::on_event(event);
}

void game_state_enter_highscore::update(int dt) {
}

void game_state_enter_highscore::draw() {
    graphics::draw_image(fader, 0, 0);
    graphics::draw_image(popup, 120, 140);
    graphics::draw_image(title, titlex, 150);
    graphics::draw_image(text, textx, 210);

    submit.draw();
    textfont.draw_hq_text(score.name, color::dark_blue, screen::get().width()/2 - text_font.string_width(score.name)/2, 250);
}

void game_state_enter_highscore::unload() {
    SDL_EnableUNICODE(SDL_DISABLE);

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

void game_state_enter_highscore::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
    if (key == SDLK_BACKSPACE) {
        if (!score.name.empty()) {
            score.name.erase(score.name.length() - 1);
        }
    } else if (key == SDLK_RETURN) {
        if (!score.name.empty()) {
            game_state_highscore gshs;
            gshs.load_highscores("./data/highscores.hs");
            gshs.pass_new_highscore(position, score);
            game_state_manager::get().change_state(new game_state_menu());
        }
    } else {
        if (score.name.length() < MAX_NAME_SIZE) {
            if (unicode == ' ') {
                score.name += (char)unicode;
            } else if (unicode >= 'a' && unicode <= 'z') {
                score.name += (char)unicode;
            } else if (unicode >= 'A' && unicode <= 'Z') {
                score.name += (char)unicode;
            } else if(unicode >= '0' && unicode <= '9') {
                score.name += (char)unicode;
            }
        }
    }
}

void game_state_enter_highscore::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
    submit.mouse_move(mx, my);
}

void game_state_enter_highscore::left_button_down(int mx, int my) {
    if (submit.has_mouse_hover(mx, my)) {
        if (!score.name.empty()) {
            game_state_highscore gshs;
            gshs.load_highscores("./data/highscores.hs");
            gshs.pass_new_highscore(position, score);
            game_state_manager::get().change_state(new game_state_menu());
        }
    }
}
