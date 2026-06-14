//
// Created by Roadb on 11/06/2026 ~6pm.
//

#include <iostream>
#include <vector>
#include  "raylib.h"
// #include "sandels.h"

using namespace std;

// Pre-run stuff idk what its called search this up!!!

struct Sandel
{
    Vector2 pos;
    float velocity;
    float life;
};


int main()
{
    // Initialisation(s) :
    InitWindow(1920, 1080, "Sandels");
    //HideCursor();
    SetTargetFPS(60);

    vector<Sandel> sandels;
    sandels.reserve(10000);

    // main game loop
    while (!WindowShouldClose())
    {
        // --- Update / Simulation :

        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            cout << "DEBUG: " "Mouse [X: " << mousePosition.x << ", " << "Y: " << mousePosition.y << ']' << endl; // debug
            sandels.push_back(Sandel(mousePosition, 1, 1));
        }

        int sandle_inter = 0;
        for (Sandel &sandel: sandels) // TODO: fix this the last sandle is weird?
        {
            sandel.pos.y += 10;
            sandel.life -= 0.02;

            if (sandel.life <= 0)
            {
                //sandels.erase( sandels.begin() + sandle_inter); // weird accurate maybe
                //sandels.erase(sandels.begin()); // weird simpler faster
                sandels.erase(begin(sandels)); // ? ? ?
            }

            sandle_inter++;
        }


        // --- Draw / Render :

        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawCircleV(mousePosition, 5, RAYWHITE); // cursor

        for (Sandel sandel: sandels)
        {
            DrawCircleV(sandel.pos, 3, YELLOW);
        }

        EndDrawing();
    }

    // Exit / Clean Up :
    CloseWindow();
    return 0;
}
