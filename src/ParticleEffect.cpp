#include "particle_effect.hpp"
#include "particle.hpp"
#include "graphics.hpp"

particle_effect::particle_effect() {
    x            = 0.f;
    y            = 0.f;
    show         = false;
    dead         = false;
    type         = EFFECT_TYPE_NONE;
    shared_image = NULL;
    gravity.Zero();
    Particles.clear();
}

particle_effect::~particle_effect() {
    for (int i = 0; i < particles.size(); ++i) {
        if (particles[i]) {
            delete particles[i];
        }
    }

    particles.clear();

    if (shared_image) {
        SDL_FreeSurface(shared_image);
    }

    shared_image = nullptr;
}

void particle_effect::update(float delta_time) {
}

void particle_effect::draw() {
    for (int i = 0; i < particles.size(); ++i) {
        if (particles[i] && !particles[i]->dead())
            particles[i]->draw(shared_image);
    }
}

void particle_effect::set_update_interval(float low, float high) {
    for (int i = 0; i < particles.size(); ++i) {
        particles[i]->set_update_interval((low + rand() % (int)(high - low + 1)));
    }
}

void particle_effect::show() {
    show = true;
}

void particle_effect::hide() {
    show = false;
}

bool particle_effect::visible() const {
    return show;
}

bool particle_effect::dead() const {
    return _dead;
}

void particle_effect::clear() {
    if (particles.empty()) {
        return;
    }

    for (int i = 0; i < particles.size(); ++i) {
        if (particles[i]) {
            delete particles[i];
        }
    }

    particles.clear();
}

int particle_effect::size() const {
    return particles.size();
}

effect_type particle_effect::type() const {
    return type;
}

void particle_effect::set_gravity(float x, float y) {
    gravity.x = x;
    gravity.y = y;
}

vector& ParticleEffect::gravity() {
    return _gravity;
}

particle_explosion_effect::particle_explosion_effect(const std::string& file,
                                                     int size,
                                                     float force,
                                                     float alphadecay,
                                                     float x,
                                                     float y)
                                                     : particle_effect() {
    this->x          = x;
    this->y          = y;
    type             = EFFECT_TYPE_EXPLOSION;
    sharedImage      = graphics::load_image(file, color::white);
    float angle_step = 360.f / static_cast<float>(size);
    
    for (int i = 0; i < size; ++i) {
        explosion_particle* ep = new explosion_particle(force, alpha_decay);
        ep->set_angle(i * angle_step);// + rand() % 11 - 5.f); // set angle +/- 5 for randomness
        ep->set_xy(x, y);

        if (!gravity.is_zero()) {
            ep->acceleration.x = gravity.x;
            ep->acceleration.y = gravity.y;
        }

        particles.push_back(ep);
    }
}

void particle_explosion_effect::update(float delta_time) {
    // No increment in this for loop!
    for (std::vector<particle*>::iterator it = particles.begin(); it != particles.end();) {
        if ((*it)->dead()) {
            delete *it;
            it = particles.erase(it);
        } else {
            if ((*it)) {
                (*it)->update(delta_time);
            }
    
            ++it;
        }
    }

    if (particles.empty()) {
        dead = true;
    }
}
