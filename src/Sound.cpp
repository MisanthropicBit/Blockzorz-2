#include "sound.hpp"

sound::sound(const std::string& file) {
    _sound = nullptr;

    if (!file.empty()) {
        _sound = Mix_LoadWAV(file.c_str());
    }
    
    if (!_sound) {
        Mix_FreeChunk(_sound);
        _sound = nullptr;
    }
}

sound::~sound() {
    if (_sound) {
        Mix_FreeChunk(_sound);
    }

    _sound = nullptr;
}

Mix_Chunk* sound::sound() const {
    if (_sound) {
        return _sound;
    } else {
        return nullptr;
    }
}

bool sound::valid() {
    return _sound != nullptr;
}
