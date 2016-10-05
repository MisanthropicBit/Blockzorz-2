#ifndef BLOCKZORZ2_COLOR_HPP
#define BLOCKZORZ2_COLOR_HPP

#include <SDL.h>

class color {
    public:
        color(int r = 0, int g = 0, int = 0);
        
        void set_rgb(int r, int g, int b);
        void set_red(int r);
        void set_green(int g);
        void set_blue(int b);
        Uint8& red();
        Uint8& green();
        Uint8& blue();
        
        color operator+(color&) const;
        color operator-(color&) const;
        
        color& operator=(color&);
        color& operator+=(const color&);
        color& operator-=(const color&);
    
        bool operator==(const color&) const;
        
        // Grayscale
        static color black;
        static color gray;
        static color white;

        // Standard Colors
        static color red;
        static color green;
        static color blue;
        static color yellow;
        static color magenta;
        static color cyan;
        static color gold;
        static color silver;
        static color bronze;

        // Dark Colors
        static color darkblue;
    
    private:
        SDL_Color _color;
};

#endif
