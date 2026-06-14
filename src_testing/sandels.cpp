//
// Created by Roadb on 11/06/2026 ~6pm.
//


// Preprocessing :

#include <iostream>
#include <vector>
#include  "raylib.h"
// #include "sandels.h"

using namespace std;


// Globals and Declarations :

struct Sandel
{ // '{}' automatically assigns default empty values
    Vector2 pos {};
    float velocity {};
    float life {};
};


// Function Definitions :

// empty


// running program code
int main()
{
    // Initialisation(s) :

    InitWindow(1920, 1080, "Sandels");
    //HideCursor();
    SetTargetFPS(180); // temp until delta time

    // Pre-Main Loop / One-Time Code :

    vector<Sandel> sandels;
    sandels.reserve(1024);

    // IMPLEMENT ON YOUR OWN!!! // seed random number generator

    // main game loop
    while (!WindowShouldClose())
    {
        // --- Update / Simulation :

        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        { // TODO: fix last sandle being fucking weirdly longer?
            // cout << "DEBUG: " "Mouse [X: " << mousePosition.x << ", " << "Y: " << mousePosition.y << ']' << endl; // debug

            sandels.push_back(Sandel({mousePosition.x - 3, mousePosition.y}, 1.0f, 1.0f));
            sandels.push_back(Sandel(mousePosition, 1.0f, 1.0f));
            sandels.push_back(Sandel({mousePosition.x + 3, mousePosition.y}, 1.0f, 1.0f));
        }

        int sandle_inter = 0;
        // TODO: fix this the last sandle being fucking weird?
        for (Sandel &sndl: sandels) // direct reference with '&', Sandel& and &sndl have same effect
        {
            // cout << "DEBUG: " "[Sandel: " << sandle_inter << ", X: " << sndl.pos.x << ", Y: " << sndl.pos.y << ", Life: " << sndl.life << ']' << endl; // debug

            sndl.life -= 0.004;
            sndl.pos.y += 4;
            // IMPLEMENT ON YOUR OWN!!! // random -1 or +1

            if (sndl.life <= 0.0001f)
            {
                sandels.erase(sandels.begin() + sandle_inter); // weird accurate maybe
                //sandels.erase(sandels.begin()); // weird simpler faster
                //sandels.erase(begin(sandels)); // same weird simple fast
            } else {
                // only increment iterator if nothing is removed from vector to avoid having the iterator shift, since when we
                // delete a part of the vector the next part shifts left into the position of our current iterator,
                // so incrementing after a deletion would skip the next object.
                sandle_inter++;
            }
        }


        // --- Draw / Render :

        // start drawing and prerequisites
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // cursor
        DrawCircleV(mousePosition, 5, RAYWHITE);

        // draw sandels
        for (Sandel sandel: sandels)
        {
            DrawCircleV(sandel.pos, 2.6f, YELLOW);
        }

        // draw fps counter
        DrawFPS(12, 10);

        // finish drawing
        EndDrawing();
    }

    // Clean Up / Exit :
    CloseWindow();
    return 0;
}
