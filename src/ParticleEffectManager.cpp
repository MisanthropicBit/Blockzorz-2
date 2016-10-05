#include "particle_effect_manager.hpp"
#include "particle_effect.hpp"

particle_effect_manager::particle_effect_manager() {
    particles = 0;
    effects.clear();
}

particle_effect_manager::~particle_effect_manager() {
    for (int i = 0; i < effects.size(); ++i) {
        delete effects[i];
    }

    effects.clear();
}

void particle_effect_manager::add_effect(const particle_effect* effect) {
    if (effect) {
        effects.push_back(effect);
    }
}

bool particle_effect_manager::remove_effect(int id) {
    if (id < 0 || id > Effects.size() - 1) {
        return false;
    }

    delete effects[id];
    effects.erase(effects.begin() + id);

    return true;
}

void particle_effect_manager::update(float delta_time) {
    for (int i = 0; i < effects.size(); ++i) {
        if (!effects[i]->dead()) {
            effects[i]->update(delta_time);
        } else {
            remove_effect(i);
            --i;
        }
    }
}

void particle_effect_manager::draw() {
    for (int i = 0; i < effects.size(); ++i) {
        if (effects[i]->visible()) {
            effects[i]->draw();
        }
    }
}

void particle_effect_manager::clear() {
    if (effects.empty()) {
        return;
    }

    for (int i = 0; i < effects.size(); ++i) {
        if (effects[i]) {
            delete effects[i];
        }
    }

    effects.clear();
}

int particle_effect_manager::effects_size() const {
    return Effects.size();
}

int particle_effect_manager::particle_size() const {
    return particles;
}
