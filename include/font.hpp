#ifndef BLOCKZORZ2_FONT_HPP
#define BLOCKZORZ2_FONT_HPP

#include <SDL_ttf.h>
#include "color.hpp"
#include <sstream>
#include <string>

class font {
    public:
        font();
        font(const std::string& fontfile, int size);
        ~font();

        void close();

        SDL_Surface* load_text_image(const std::string& text,
                                     const color& color);
        SDL_Surface* load_hq_text_image(const std::string& text,
                                        const color& color);

        // Draw member functions
        void draw_text(const std::string& text, color& color, int x, int y);
        void draw_text_transparent(const std::string& text, color& color, float alpha, int x, int y);
        void draw_text(const std::string& text, color& color, int x, int y, const std::string& newfont, int size);
        void draw_hq_text(const std::string& text, color& color, int x, int y);

        // Getters
        TTF_Font* get_font() const;
        int size() const;
        int style() const;
        int height() const;
        int ascent() const;
        int descent() const;
        int recommended_spacing();
        int string_width(const std::string& s);
        int string_height(const std::string& s);

        // Setters
        void set_font_file(const std::string& fontfile);
        void set_font_file(const std::string& fontfile, int size);
        void set_size(int size);
        void set_style(int style);
    
        // Type conversion
        static std::string int2string(int i);
        static std::string float2string(float f);
        static int string2int(const std::string& s);

    private:
        TTF_Font* _font;
        int _size;
};

#endif
