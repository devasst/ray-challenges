//
// Created by adri on 29/07/24.
//

#ifndef RAY_CHALLENGES_PARTICLE_H
#define RAY_CHALLENGES_PARTICLE_H

#include "raylib.h"

#define DEFAULT_GRAVITY 1000

class Particle {

    private:
        Vector2 position = {};
        Vector2 speed = {};
        Vector2 acceleration = {};
        float mass = 100;
        float gravity = DEFAULT_GRAVITY;

    public:
        Particle(Vector2 position, Vector2 speed);
        Particle(Vector2 position, Vector2 speed, Vector2 acceleration);
        ~Particle();

        void set_pos(Vector2 position);
        void set_posX(float posX);
        void set_posY(float posY);
        void set_speed(Vector2 speed);
        void set_accel(Vector2 accel);
        void set_mass(float m);
        void set_gravity(float g);
        void invert_speedX();
        void invert_speedY();
        Vector2 get_pos();
        Vector2 get_speed();
        Vector2 get_accel();
        float get_mass();

        Vector2 update_pos(float deltaTime);

        // TODO: acceleration+gravity, collisions...
};


#endif //RAY_CHALLENGES_PARTICLE_H
