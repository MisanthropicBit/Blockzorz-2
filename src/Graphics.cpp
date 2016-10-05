#include "graphics.hpp"
#include "color.hpp"
#include "screen.hpp"

graphics::graphics() {
}

SDL_Surface* graphics::load_image(const std::string& file) {
    SDL_Surface* surf_temp   = nullptr;
    SDL_Surface* surf_return = nullptr;

	if ((surf_temp = IMG_Load(file.c_str())) == nullptr) {
		if (file.empty()) {
			printf("Unable to load image: Empty string passed!\n");
		} else {
			printf("Unable to load image: %s\n", file.c_str());
		}

		return nullptr;
	}

    surf_return = SDL_DisplayFormat(surf_temp);
    SDL_FreeSurface(surf_temp);

    return surf_return;
}

SDL_Surface* graphics::load_image(const std::string& file, const color& transparent) {
    SDL_Surface* surf_temp = nullptr;
    SDL_Surface* surf_return = nullptr;

	if ((surf_temp = IMG_Load(file.c_str())) == nullptr) {
		if (file.empty()) {
			printf("Unable to load image: Empty string passed!\n");
		} else {
			printf("Unable to load image: %s\n", file.c_str());
		}

		return nullptr;
	}

    surf_return = SDL_DisplayFormat(surf_temp);
    SDL_FreeSurface(surf_temp);
	graphics::set_transparency_color(surf_return, transparent);

    return surf_return;
}

bool graphics::draw_image(SDL_Surface* source, float x, float y) {
    if (!source) {
        return false;
    }

	SDL_Rect dest_rect;

    dest_rect.x = (Sint16)x;
    dest_rect.y = (Sint16)y;

	if (SDL_MUSTLOCK(source)) {
		SDL_LockSurface(source);
	}

	SDL_BlitSurface(source, nullptr, screen::get().get_screen_surface(), &dest_rect);

	if (SDL_MUSTLOCK(source)) {
		SDL_UnlockSurface(source);
	}

    return true;
}

bool graphics::draw_image(SDL_Surface* source, float x, float y, int sx, int sy, int w, int h) {
    if (source == nullptr) {
        return false;
    }

    SDL_Rect dest_rect;
    dest_rect.x = (Sint16)x;
    dest_rect.y = (Sint16)y;

    SDL_Rect source_rect;
    source_rect.x = sx;
    source_rect.y = sy;
    source_rect.w = w;
    source_rect.h = h;

    SDL_BlitSurface(source, &source_rect, screen::get().get_screen_surface(), &dest_rect);
    return true;
}

bool graphics::set_transparency_color(SDL_Surface* source, const Color& color) {
	if(source == nullptr) {
        return false;
    }

	SDL_SetColorKey(source, SDL_SRCCOLORKEY, SDL_MapRGB(source->format, color.red(), color.green(), color.blue()));
	return true;
}

void graphics::set_transparency(SDL_Surface* source, float alpha) {
	if (!source || (alpha < 0.f || alpha > 1.f)) {
        return;
    }

	if (SDL_SetAlpha(source, SDL_SRCALPHA, (int)((1-alpha) * 255)) == -1) {
        return;
    }
}

void graphics::draw_horizontal_line(int x1, int x2, int y, int thickness, const color& color) {
    SDL_Rect dest_rect;

    dest_rect.x = x1;
	dest_rect.y = y;
    dest_rect.h = thickness;
	dest_rect.w = x2 - x1;

	SDL_FillRect(screen::get().get_screen_surface(),
                 &dest_rect,
                 SDL_MapRGB(screen::get().get_screen_surface()->format,
                 color.red(),
                 color.green(),
                 color.blue()));
}

void graphics::draw_vertical_line(int y1, int y2, int x, int thickness, const color& color) {
    SDL_Rect dest_rect;

    dest_rect.x = x;
	dest_rect.y = y1;
    dest_rect.h = y2 - y1;
	dest_rect.w = thickness;

	SDL_FillRect(screen::get().get_screen_surface(),
                 &dest_rect,
                 SDL_MapRGB(screen::get().get_screen_surface()->format,
                 color.red(),
                 color.green(),
                 color.blue()));
}
