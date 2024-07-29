/*******************************************************************************************
*
*   ray-challenges using raylib - particle simulation
*
*   Copyright (c) 2014 Adrian Santiago (@devasst)
*
********************************************************************************************/


#include <cstdlib>
#include <iostream>
#include "Particle.h"
#include "external/glad.h"

#define NUM_PARTICLES 1000
#define MAX_SPEED 500
#define BALL_RADIUS 5


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //---------------------------------------------------------
    // Init
    //---------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "[ray-challenges] - particle simulation using raylib");

    double prevTime = GetTime();
    double currTime = 0.0;
    float deltaTime = 0.0f;
    float simTime = 0.0f;
    bool pause = false;

    auto *particles = (Particle *) malloc(sizeof(Particle) * NUM_PARTICLES);
    for (int i = 0; i < NUM_PARTICLES; i++){
        Vector2 pos = {static_cast<float>(GetRandomValue(0, GetScreenWidth())),
                       static_cast<float>(GetRandomValue(0,GetScreenHeight()))};
        Vector2 sp = {static_cast<float>(GetRandomValue(- MAX_SPEED, MAX_SPEED)),
                      static_cast<float>(GetRandomValue(- MAX_SPEED,MAX_SPEED))};
        particles[i] = Particle(pos, sp, {0, 0});
    }

    int framesCounter = 0;
    int targetFPS = 60;

    SetTargetFPS(targetFPS);

    //---------------------------------------------------------
    // Main Loop
    //---------------------------------------------------------
    while (!WindowShouldClose())
    {
        //-----------------------------------------------------
        // Update
        //-----------------------------------------------------

        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause) {
            for (int i = 0; i < NUM_PARTICLES; i++) {
                auto old_position = particles[i].get_pos();
                auto old_speed = particles[i].get_speed();
                auto new_position = particles[i].update_pos(deltaTime);

                // Check walls collision for bouncing
                if ((new_position.x >= static_cast<float>(GetScreenWidth() - BALL_RADIUS)) ||
                    (new_position.x <= BALL_RADIUS)) {
                    particles[i].invert_speedX();
                }
                if ((new_position.y >= static_cast<float>(GetScreenHeight() - BALL_RADIUS)) ||
                    (new_position.y <= BALL_RADIUS)) {
                    particles[i].invert_speedY();
                    if (new_position.y >= static_cast<float>(GetScreenHeight() - BALL_RADIUS)){
                        particles[i].set_posY(static_cast<float>(GetScreenHeight() - BALL_RADIUS));
                    }
                }
            }

            simTime += deltaTime;
        }
        framesCounter++;

        //-----------------------------------------------------
        // Time Operations
        //-----------------------------------------------------
        currTime = GetTime();

        if (targetFPS > 0)
        {
            // Fixed frame rate
            double waitTime = (1.0f/(float)targetFPS) - (currTime - prevTime);
            if (waitTime > 0.0)
            {
                WaitTime((float)waitTime);
                currTime = GetTime();
            }
        }
        deltaTime = (float)(currTime - prevTime);
        prevTime = currTime;

        //-----------------------------------------------------
        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < NUM_PARTICLES; i++) {
            DrawCircleV(particles[i].get_pos(), (float) BALL_RADIUS, MAGENTA);
        }

        // On pause, we draw a blinking message
        if (pause && ((framesCounter/targetFPS)%2)) {
            DrawText("PAUSED", GetScreenWidth()/2, GetScreenHeight()/2, 30, GRAY);
        }

        DrawFPS(10, 10);

        EndDrawing();
        glFinish();
        //-----------------------------------------------------


    }

    // De-Initialization
    free(particles);

    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}