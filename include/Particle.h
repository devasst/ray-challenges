/*!
 * @file Particle.h
 *
 * Definition of Class for individual particles
 *
 * Features:
 *      - Position
 *      - Speed
 *      - Acceleration
 *      - Bouncing
 *      - Update movement: position based on {speed, acceleration}
 *
 * Created by devasst on 29/07/24.
*/

#ifndef RAY_CHALLENGES_PARTICLE_H
#define RAY_CHALLENGES_PARTICLE_H

#include "raylib.h"

#define DEFAULT_GRAVITY 10
#define DEFAULT_BOUNCING 0.75

/*!
 * @class Particle
 * \brief Class for Particles movements and interactions
 *
*/
class Particle {

    private:
        Vector2 position = {}; /*!< x,y vector components of position */
        Vector2 speed = {}; /*!< x,y vector components of speed */
        Vector2 acceleration = {}; /*!< x,y vector components of acceleration */
        float mass = 10; /*!< weight/mass of the object for gravity/collision purposes (default: 10) */
        float gravity = DEFAULT_GRAVITY; /*!< force for gravity purposes (default: 10) */
        float bouncing_ratio = DEFAULT_BOUNCING; /*!< bouncing capabilities, ratio 0-1 (from less elastic to more rigid) */

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
        void set_bouncing_ratio(float b);
        void invert_speedX();
        void invert_speedY();
        Vector2 get_pos();
        Vector2 get_speed();
        Vector2 get_accel();
        float get_mass();
        float get_bouncing_ratio();

        Vector2 update_mov(float deltaTime);

        // TODO: collisions...
};


#endif //RAY_CHALLENGES_PARTICLE_H
