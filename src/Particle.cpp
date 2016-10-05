#include "particle.hpp"
#include "graphics.hpp"
#include <cstdlib>

particle::particle(float alpha_decay) {
    this->alpha_decay = alpha_decay;
    lifetime          = 0.f; // 0% transparency
    updateinterval    = 0.f;
    speed.x           = 1.f; //(rand() % 10 + 1) / 10.f;
    speed.y           = 1.f; //(rand() % 10 + 1) / 10.f;
    w                 = 0;
    h                 = 0;
}

void particle::reset(float x, float y)
{
    position.x = x;
    position.y = y;
    life_time  = 0.f;
    time_left  = update_interval;
    dead       = false;

    graphics::set_transparency(image, 0.f);
}

// This member function has not yet been tested!
void particle::reset(object* attached_to) {
    if (!attached_to) {
        return;
    }
    
    position.x = attached_to->position.x + attached_to->w / 2 - w / 2;
    position.y = attached_to->position.y + attached_to->h / 2 - h / 2;
    life_time  = 0.f;
    time_left  = update_interval;
    dead       = false;

    graphics::set_transparency(image, 0.f);

    if (speed.is_zero()) {
        speed.set_angle(rand() % 360);
        speed *= (((rand() % (5 + 1)) + 5.f) / 10.f); // Scales the speed vector by a random factor between 0.5 and 1.0
    } else {
        float object_angle = attachedto->speed.angle();
        float low_angle    = objectangle - 135; // Image the attached object's speed is going in a 45 degree angle
        float high_angle   = objectangle + 135;

        speed.set_angle(low_angle + rand() % (int)(high_angle - low_angle));
        speed *= (((rand() % (5 + 1)) + 5.f) / 10.f); // Scales the speed vector by a random factor between 0.5 and 1.0
    }
}

void particle::set_xy(float x, float y) {
    position.x = x;
    position.y = y;
}

void particle::set_angle(float angle) {
    speed.set_angle(angle);
}

void particle::set_update_interval(float update_interval) {
    this->update_interval = update_interval;
    time_left = update_interval;
}

void particle::draw(sdl_surface* shared_image) {
    graphics::set_transparency(shared_image, life_time);
    graphics::draw_image(shared_image, position.x, position.y);
}

explosion_particle::explosion_particle(float force, float alpha_decay) : particle(alpha_decay) {
    this->force  = force;
    speed       *= force;
}

void explosion_particle::update(float delta_time) {
    time_left -= delta_time;
    object::update(delta_time);

    if (time_left <= 0) {
        // Time to change alpha value
        life_time += alpha_decay;

        if (life_time > 1.f) {
            life_time = 1.f;
        }

        time_left = update_interval;

        if (life_time >= 1.f) {
            dead = true;
        }
    }
}
