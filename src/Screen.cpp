#include "screen.hpp"
#include "graphics.hpp"
#include "color.hpp"

screen screen::screen;

screen::screen() {
    screen_surface = nullptr;
}

screen::~screen() {
}

bool screen::create_screen(int width, int height, int bpp, Uint32 flags) {
    return screen::screen.set_video_resolution(width, height, bpp, flags);
}

void screen::destroy_screen() {
    if (screen::get().screen_surface()) {
        SDL_FreeSurface(screen::get().screen_surface());
    }
}

screen screen::screen() {
    return screen::screen;
}

// Use this for resize events
bool screen::set_video_resolution(int width, int height, int bpp, Uint32 flags) {
    // SDL_Quit() takes care of deleting the video surface properly,
    // so we can safely resize
    screen_surface = SDL_SetVideoMode(width, height, bpp, flags);

    return screen_surface != nullptr;
}

int screen::height() {
    return screen_surface->h;
}

int screen::width() {
    return screen_surface->w;
}

int screen::bits_per_pixel() {
    return screen_surface->format->BytesPerPixel * 8;
}

int screen::bytes_per_pixel() {
    return screen_surface->format->BytesPerPixel;
}

Uint32 screen::flags() {
    return screen_surface->flags;
}

void screen::set_caption(const std::string& text) {
    caption = text;
    SDL_WM_SetCaption(caption.c_str(), nullptr);
}

void screen::set_icon(const std::string& icon_file) {
    if (!icon_file.empty()) {
        // The IMG_Load(...) function from SDL_image does not seem to work in this case
        SDL_Surface* icon = SDL_LoadBMP(icon_file.c_str());
    
        if (icon) {
            SDL_WM_SetIcon(icon, nullptr);
        }

        SDL_FreeSurface(icon);
        Icon = nullptr;
    }
}

std::string screen::caption() {
    return _caption;
}

SDL_Surface* screen::screen_surface() {
    return screen_surface;
}

void screen::update_screen() {
    SDL_Flip(screen_surface);
}

void screen::clear_screen() {
    // Fills the entire screen with black
    SDL_FillRect(screen_surface, nullptr, 0);
}

void screen::clear_screen_color(const color& color) {
    SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, color.red(), color.green(), color.blue()));
}
