#include "timer.hpp"
#include "font.hpp"

timer::timer() {
    started    = false;
    paused     = false;
    startTick  = 0;
    pausedTick = 0;
    lastTick   = 0;
    fpsTick    = 0;
    fps        = 0;
    frames     = 0;
}

void timer::start() {
    started    = true;
    paused     = false;
    start_tick = SDL_GetTicks();//Timer::GetElapsedTime() - pausedTick;
}

void timer::pause() {
    if (!paused) {
        started     = false;
        paused      = true;
        paused_tick = timer::elapsed_time() - start_tick;
    }
}

bool timer::is_paused() const {
    return paused;
}

// Gets the current time elaspsed since last pause
int timer::time() const {   
    if (started) {
        return timer::elapsed_time() - start_tick;
    } else {
        return paused_tick;
    }

    return 0;
}

// By calling this function in the main loop, we can calculate the fps when one second has passed.
void timer::update() {
    if (SDL_GetTicks() >= (fps_tick + 1000)) {
        fps_tick = SDL_GetTicks();
        fps      = frames;
        frames   = 0;
    }

    ++frames;
}

string timer::get_pretty_print_time() {
    if ((time() / 1000) % 60 < 10) {
        return (font::int2string(time() / 1000 / 60) + ":0" + font::int2string((time() / 1000) % 60));
    } else {
        return (font::int2string(time() / 1000 / 60) + ":" + font::int2string((time() / 1000) % 60));
    }
}

// This function is static since it makes more sense. Elapsed time is not an individual property of each timer.
int timer::elapsed_time() {
    return SDL_GetTicks();
}

int timer::elapsed_minutes() {
    return (elapsed_time() / 1000) / 60;
}

int timer::elapsed_seconds() {
    return (elapsed_time() / 1000) % 60;
}

// Gets the time elapsed since this function was called
int timer::delta_time() {
    int delta_time = SDL_GetTicks() - last_tick; // miliseconds
    last_tick      = SDL_GetTicks();

    return delta_time;
}

int timer::fps() const {
    return _fps;
}
