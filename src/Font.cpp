#include "font.hpp"
#include "graphics.hpp"

font::font() {
    font = nullptr;
}

font::font(const std::string& fontfile, int size) {
    font = nullptr;

    if (!fontfile.empty()) {
        set_size(size);
        set_font_file(fontfile.c_str());
    }
}

font::~font() {
}

void font::close() {
    if (font) {
        TTF_CloseFont(font);
    }

    font = nullptr;
}

SDL_Surface* font::load_text_image(const std::string& text, const color& color) {
    if (text.empty() || !font) {
        printf("Error: No loaded font prior to call or empty string passed to font::load_text_image(const std::string& text, const color& color)");
        return nullptr;
    }

    SDL_Color sdl_color = { color.red(), color.green(), color.blue() };

    return TTF_RenderText_Solid(font, text.c_str(), sdl_color);
}

SDL_Surface* font::load_hq_text_image(const std::string& text, const Color& color) {
    if (text.empty() || !font) {
        printf("Error: No loaded font prior to call or empty string passed to Font::LoadHQTextImage(const string& text, Color& color)");
        return nullptr;
    }

    SDL_Color sdl_color = { color.red(), color.green(), color.blue() };

    return TTF_RenderText_Blended(font, text.c_str(), sdl_color);
}

void font::draw_text(const std::string& text, const color& color, int x, int y) {
    SDL_Surface* txt_image = load_text_image(text, color);

    if (!txt_image) {
        return;
    }

    graphics::draw_image(txt_image, x, y);
    SDL_FreeSurface(txt_image);
    txt_image = nullptr;
}

void font::draw_text_transparent(const std::string& text, const color& color, float alpha, int x, int y) {
    SDL_Color sdl_color = { color.red(), color.green(), color.blue() };
    SDL_Surface* txt_image = TTF_RenderText_Solid(font, text.c_str(), sdl_color);

    if (!txtimage) {
        return;
    }

    graphics::set_transparency(txt_image, alpha);
    graphics::draw_image(txt_image, x, y);
    SDL_FreeSurface(txt_image);
    txtimage = nullptr;
}

void font::draw_text(const std::string& text, const color& color, int x, int y, const std::string& newfontfile, int size) {
    TTF_Font* new_font = TTF_OpenFont(newfontfile.c_str(), size);

    if (!new_font) {
        TTF_CloseFont(new_font);
        return;
    }

    SDL_Color sdl_color = { color.red(), color.green(), color.blue() };
    SDL_Surface* txt_image = TTF_RenderText_Solid(new_font, text.c_str(), sdl_color);

    if (!txt_image) {
        TTF_CloseFont(new_font);
        SDL_FreeSurface(txt_image);
        txtimage = nullptr;
        return;
    }

    graphics::draw_image(txt_image, x, y);
    TTF_CloseFont(new_font);
    SDL_FreeSurface(txt_image);
    new_font = nullptr;
    txt_image = nullptr;
}

void font::draw_hq_text(const string& text, Color& color, int x, int y) {
    if (text.empty() || !font) {
        return;
    }

    SDL_Color sdl_color = { color.red(), color.green(), color.blue() };
    SDL_Surface* txt_image = TTF_RenderText_Blended(font, text.c_str(), sdl_color);

    if (!txt_image) {
        return;
    }

    graphics::draw_image(txt_image, x, y);
    SDL_FreeSurface(txt_image);
    txt_image = nullptr;
}

TTF_Font* font::get_font() const {
    return font;
}

int font::size() const {
    return _size;
}

int font::style() const {
    return TTF_GetFontStyle(font);
}

int font::height() const {
    return TTF_FontHeight(font);
}

int font::ascent() const {
    return TTF_FontAscent(font);
}

int font::descent() const {
    return TTF_FontDescent(font);
}

int font::recommended_spacing() {
    return TTF_FontLineSkip(font);
}

int font::string_width(const std::string& s) {
    int w;
    TTF_SizeText(font, s.c_str(), &w, nullptr);

    return w;
}

int font::string_height(const std::string& s) {
    int h;
    TTF_SizeText(font, s.c_str(), nullptr, &h);

    return h;
}

void font::set_font_file(const std::string& font_file) {
    if (font_file.empty() || size < 0) {
        return;
    }

    if((font = TTF_OpenFont(fontfile.c_str(), size)) == nullptr) {
        fprintf(stderr, "Could not open desired font (%s)\n", fontfile.c_str());
        return;
    }

    return;
}

void font::set_font_file(const std::string& font_file, int size) {
    if (font_file.empty() || size <= 0) {
        return;
    }

    set_size(size);
    set_font_file(font_file);
}

void font::set_size(int size) {
    this->size = size;
}

// 'style' can be eiher TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE or TTF_STYLE_NORMAL
void font::set_style(int style) {
    TTF_SetFontStyle(font, style);
}

std::string font::int2string(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::string font::float2string(float f) {
    std::stringstream ss;
    ss << f;
    return ss.str();
}

int font::string2int(const std::string& s) {
    int i = 0;
    std::istringstream iss(s);

    iss >> dec >> i;

    return i;
}
