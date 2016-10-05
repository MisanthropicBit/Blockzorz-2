#ifndef BLOCKZORZ2_EVENT_HPP
#define BLOCKZORZ2_EVENT_HPP

#include <SDL.h>

class event {
   public:
        event();
		~event();

        virtual void on_event(SDL_Event& event);

        virtual void input_focus();

        virtual void input_blur();

        virtual void key_down(SDLKey key, SDLMod modifier, Uint16 unicode);

        virtual void key_up(SDLKey key, SDLMod modifier, Uint16 unicode);

        virtual void mouse_focus();

        virtual void mouse_blur();

        virtual void mouse_move(int mx, int my, int relx, int rely, Uint8 state);

        virtual void left_button_down(int mx, int my);

        virtual void left_button_up(int mx, int my);

        virtual void right_button_down(int mx, int my);

        virtual void right_button_up(int mx, int my);

        virtual void middle_button_down(int mx, int my);

        virtual void middle_button_up(int mx, int my);

        virtual void minimize();

        virtual void restore();

        virtual void resize(int w, int h);

        virtual void expose();

        virtual void exit();
};

#endif
