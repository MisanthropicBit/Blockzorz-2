#include "menu.hpp"
#include "menu_item.hpp"
#include "graphics.hpp"
#include "screen.hpp"
#include "audio_manager.hpp"

menu::menu(const std::string& title,
           const std::string& font_file,
           int font_size,
           const std::string& image_file,
           int x,
           int y) {
    load(title, font_file, font_size, image_file, x, y);
    visible    = false;
    button_gap = 5;
    alpha      = 0.f;
    selected   = 0;
    sound_name = "";
}

menu::~menu() {
    for (int i = 0; i < menu_items.size(); ++i) {
        delete menu_items[i];
    }

    menu_items.clear();
}

void menu::load(const std::string& title,
                const std::string& fontfile,
                int font_size,
                const std::string& image_file,
                int x,
                int y) {
    this->x = x;
    this->y = y;

    if (image) {
        SDL_FreeSurface(image);
        image = nullptr;
    }

    image = graphics::load_image(image_file);
    font.set_font(font_file, font_size);
    menu_items.clear();
}

void menu::handle_event(SDL_Event& event) {
    if (!visible() || menu_items.empty()) {
        // Menu not visible or no items to evaluate, so no need to handle events
        return;
    }

    if (event.type == SDL_KEYDOWN) {
        // Handle keyboard
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                menu_items[selected]->deselect();
            
                if (selected == 0) {
                    selected = menu_items.size() - 1;
                } else {
                    selected -= 1;
                }

                if (!sound_name.empty()) {
                    audio_manager::get()->play_sound(sound_name, 0);
                }

                menu_items[selected]->select();
                break;

            case SDLK_DOWN:
                menu_items[selected]->deselect();
            
                if (selected == menu_items.size() - 1) {
                    selected = 0;
                } else {
                    selected += 1;
                }

                if (!sound_name.empty()) {
                    audio_manager::get()->play_sound(sound_name, 0);
                }

                menu_items[selected]->select();
                break;

            case SDLK_RIGHT:
                if (menu_items[selected]->right_key()) {
                    audio_manager::get()->play_sound(sound_name, 0);
                }
                break;

            case SDLK_LEFT:
                if (menu_items[selected]->left_key()) {
                    audio_manager::get()->play_sound(sound_name, 0);
                }
                break;

            case SDLK_RETURN:
                menu_items[selected]->enter();
                break;

            default:
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        menu_items[selected]->clicked(false);
    } else if (event.type == SDL_MOUSEMOTION) {
        // Handle mouse movement
        int shift_hover = -1;

        for (int i = 0; i < menu_items.size(); i++) {
            if (menu_items[i]->mouse_motion(event.motion.x, event.motion.y)) {
                shift_hover = i;
            }
        }

        if (shift_hover >= 0) {
            if (!sound_name.empty() && shift_hover != selected) {
                audio_manager::get()->play_sound(sound_name, 0);
            }

            menu_items[selected]->deselect();
            selected = shift_hover;
            menu_items[selected]->select();
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        // Handle mouse button
        for (int i = 0; i < menu_items.size(); ++i) {
            menu_items[i]->mouse_button_down(event.button.x, event.button.y);
        }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        for (int i = 0; i < MenuItems.size(); ++i) {
            menu_items[i]->mouse_button_up();
        }
    }
}

void menu::draw() {
    if (!visible()) {
        return;
    }

    graphics::draw_image(image, x - w/2, y - (size() * button_gap) / 2);

    for(int i = 0; i < menu_items.size(); ++i) {
        menu_items[i]->draw();
    }
}

void menu::add_menu_item(menu_item* item) {
    item->set_menu(this);
    menu_items.push_back(item);

    if (menu_items.size() == 1) {
        // If this is the first button, select it.
        button->Select();
    }
}

void menu::add_button(const std::string& title, const color& normal_color, const color& selected_color) {
    button* button  = new button(title, normal_color, selected_color, text.string_width(title), text.string_height(title));
    button->pos().x = x + w/2 - button->width() / 2;
    button->pos().y = y + menu_items.size() * (text.size() + button_gap);
    button->set_menu(this);

    menu_items.push_back(button);

    if (menu_items.size() == 1) {
        // If this is the first button, select it. 
        button->select();
    }
}

void menu::add_selection(const std::string& default, const std::vector<std::string>& choices, const color& normal_color, const color& selected_color) {
    selection* selection = new selection(default, choices, normal_color, selected_color);
    selection->pos().x   = x + w/2 - text.string_width(default) / 2;
    selection->pos().y   = y + menu_items.size() * (text.size() + button_gap);
    selection->set_menu(this);

    menu_items.push_back(selection);

    if(MenuItems.size() == 1) {
        // If this is the first button, select it.
        selection->select();
    }
}

void menu::center() {
    x = screen::get().width()/2 - w/2;
    y = Screen::get().height()/2 - h/2;

    // Also center for menu's children
    for (int i = 0; i < MenuItems.size(); ++i) {
        menu_items[i]->pos().x = x + w/2 - menu_items[i]->width()/2;
        menu_items[i]->pos().y = y + i * (text.size() + buttongap);
    }
}

void menu::set_button_gap(int button_gap) {
    if (button_gap >= 0) {
        this->button_gap = button_gap;
    }
}

void menu::set_alpha_unselected(float alpha) {
    if (alpha >= 0.f && alpha <= 1.f) {
        this->alpha = alpha;
    }
}

void menu::set_select_sound(const std::string& sound_name) {
    this->sound_name = sound_name;
}

void menu::show() {
    visible = true;

    // Reset all items
    if (!menu_items.empty()) {
        for (int i = 0; i < menu_items.size(); ++i) {
            menu_items[i]->deselect();
            menu_items[i]->clicked(false);
        }

        selected = 0;
        menu_items[0]->select();
    }
}

void menu::hide() {
    visible = false;
}

bool menu::visible() {
    return visible;
}

// Returns the item (1, 2, 3 etc.) that was clicked, if any
int menu::clicked() {
    if (menu_items.empty() || !visible()) {
        return 0;
    }

    for (int i = 0; i < MenuItems.size(); ++i) {
        if (menu_items[i]->clicked()) {
            return i + 1;
        }
    }

    return 0;
}

std::string menu::item_title(int id) {
    if (id < 1 || id > menu_items.size()) {
        return "";
    }

    return menu_items[id - 1]->title();
}

font* menu::font() {
    return &_font;
}

int menu::x() const {
    return x;
}

int menu::y() const {
    return y;
}

int menu::width() const {
    return w;
}

int menu::height() const {
    return h;
}

float menu::alpha() const {
    return alpha;
}

int menu::button_gap() const {
    return buttongap;
}

int menu::size() const {
    return menu_items.size();
}
