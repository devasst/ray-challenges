//
// Created by adri on 29/07/24.
//

#include "../include/Particle.h"

Particle::Particle(Vector2 position, Vector2 speed) {
    this->position = position;
    this->speed = speed;
    this->acceleration = {0, 0};
}

Particle::Particle(Vector2 position, Vector2 speed, Vector2 acceleration) {
    this->position = position;
    this->speed = speed;
    this->acceleration = acceleration;
}

Particle::~Particle() = default;

void Particle::set_pos(Vector2 pos){
    this->position = pos;
}
void Particle::set_posX(float posX){
    this->position.x = posX;
}
void Particle::set_posY(float posY){
    this->position.y = posY;
}
void Particle::set_speed(Vector2 sp){
    this->speed = sp;
}
void Particle::set_accel(Vector2 accel){
    this->acceleration = accel;
}
void Particle::set_mass(float m) {
    this->mass = m;
}
void Particle::set_gravity(float g) {
    this->gravity = g;
}
void Particle::invert_speedX(){
    this->speed.x *= -1.0f;
}
void Particle::invert_speedY(){
    this->speed.y *= -1.0f;
}
Vector2 Particle::get_pos(){
    return this->position;
}
Vector2 Particle::get_speed(){
    return this->speed;
}
Vector2 Particle::get_accel(){
    return this->acceleration;
}
float Particle::get_mass(){
    return this->mass;
}
Vector2 Particle::update_pos(float deltaTime) {
    if (this->gravity != 0){
        this->acceleration.y += this->gravity * this->mass / this->position.y;
    }

    this->speed.x += this->acceleration.x * deltaTime;
    this->speed.y += this->acceleration.y * deltaTime;

    this->position.x += this->speed.x * deltaTime;
    this->position.y += this->speed.y * deltaTime;

    return this->position;
}

