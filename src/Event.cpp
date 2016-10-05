#include "event.hpp"

event::event() {
}

event::~event() {
}

void event::on_event(SDL_Event& event) {
    switch(event.type) {
        case SDL_ACTIVEEVENT: {
            switch(event.active.state) {
                case SDL_APPMOUSEFOCUS: {
					if (event.active.gain) {
						mouse_focus();
                    } else {
						mouse_blur();
                    }

                    break;
                }

                case SDL_APPINPUTFOCUS: {
                    if (event.active.gain) {
						input_focus();
                    } else {
						input_blur();
                    }

                    break;
                }
                case SDL_APPACTIVE: {
                    if (event.active.gain) {
						restore();
                    } else {
						minimize();
                    }

                    break;
                }
            }

            break;
        }

        case SDL_KEYDOWN: {
            key_down(event.key.keysym.sym,
                     event.key.keysym.mod,
                     event.key.keysym.unicode);
            break;
        }

        case SDL_KEYUP: {
            key_up(event.key.keysym.sym,
                   event.key.keysym.mod,
                   event.key.keysym.unicode);
            break;
        }

        case SDL_MOUSEMOTION: {
            mouse_move(event.motion.x,
                       event.motion.y,
                       event.motion.xrel,
                       event.motion.yrel,
                       event.motion.state);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: {
                    left_button_down(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    right_button_down(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    middle_button_down(event.button.x, event.button.y);
                    break;
                }
            }

            break;
        }

        case SDL_MOUSEBUTTONUP: {
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: {
                    left_button_up(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    right_button_up(event.button.x, event.button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    middle_button_up(event.button.x, event.button.y);
                    break;
                }
            }

            break;
        }

        case SDL_QUIT: {
            exit();
            break;
        }

        case SDL_VIDEORESIZE: {
            resize(event.resize.w, event.resize.h);
            break;
        }

        case SDL_VIDEOEXPOSE: {
            expose();
            break;
        }

        default:
            break;
    }
}

void event::input_focus() {
}

void event::input_blur() {
}

void event::key_down(SDLKey key, SDLMod modifier, Uint16 unicode) {
}

void event::key_up(SDLKey key, SDLMod modifier, Uint16 unicode) {
}

void event::mouse_focus() {
}

void event::mouse_blur() {
}

void event::mouse_move(int mx, int my, int relx, int rely, Uint8 state) {
}

void event::left_button_down(int mx, int my) {
}

void event::left_button_up(int mx, int my) {
}

void event::right_button_down(int mx, int my) {
}

void event::right_button_up(int mx, int my) {
}

void event::middle_button_down(int mx, int my) {
}

void event::middle_button_up(int mx, int my) {
}

void event::minimize() {
}

void event::restore() {
}

void event::resize(int w, int h) {
}

void event::expose() {
}

void event::exit() {
}
