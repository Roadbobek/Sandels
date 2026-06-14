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
    float velocity {1.0f};
    float life {1.0f};
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

    // TODO: IMPLEMENT ON YOUR OWN!!! // seed random number generator

    // main game loop
    while (!WindowShouldClose())
    {
        // --- Update / Simulation :

        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            //cout << "DEBUG: " "Mouse [X: " << mousePosition.x << ", " << "Y: " << mousePosition.y << ']' << endl; // DEBUG

            // maps {mousePosition} directly to the struct members, being pos, then structs defaults for others.
            // just makes a temporary Sandel object with the structs values then moves it into the vector.
            // aggregate initialization.
            //sandels.push_back({mousePosition});
            // explicitly calls the constructor (which is empty/default) to map mousePosition to pos, then structs defaults for others.
            // makes a temporary Sandel object with the structs values then moves it into the vector.
            // explicit constructor call, just aggregate initialization since we lack a constructor.
            //sandels.push_back(Sandel(mousePosition));
            // the two above lines do the same thing in our circumstances and are likely compiled identically,
            // this also applies to .insert() but not .exmplace_back(), it applies anywhere where a Sandel object is created.
            // on the line above the compiler automatically deduces the type Sandel because .push_back() expects the type Sandel
            // since it is writing to a vector constructed of the type Sandel.

            // combined three .push_back() calls into one .insert() call.
            // .insert() lets you insert multiple elements at once, it also allows for insertion anywhere in the vector.
            // we insert at the end with the position 'sandels.end()', but it is slower than .push_back() if inserting elsewhere than the end
            // since then the vectors elements must shift, with 'sandels.end()' the elements just get appended.
            sandels.insert(sandels.end(), {{mousePosition}, {mousePosition.x - 13, mousePosition.y}, {mousePosition.x + 13, mousePosition.y}});

            // TODO: explore .emplace_back() tomorrow for possible performance increase
        }

        for (size_t sandle_inter = 0; sandle_inter < sandels.size();)
        {
            // direct reference to memory with '&', Sandel& and &sndl have same effect
            Sandel &sndl = sandels[sandle_inter];
            //cout << "DEBUG: " "[Iteration: " << sandle_inter << ", X: " << sndl.pos.x << ", Y: " << sndl.pos.y << ", Life: " << sndl.life << ']' << endl; // DEBUG
                if (sndl.life <= 0.0001f)
            {
                sandels.erase(sandels.begin() + sandle_inter); // weird accurate ig
                // line above deletes the sandel with 0 life left,
                // lines under delete the first sandel created when any sandel reaches 0 life,
                // making the above line more accurate if sandel life and spawn order
                // stops being the same, since now oldest sandel has least health
                //sandels.erase(sandels.begin()); // weird simpler faster
                //sandels.erase(begin(sandels)); // same weird simple fast, whats diff
            } else {
                // only increment iterator if nothing is removed from vector to avoid having the iterator shift,
                // since when we delete a part of the vector the next part shifts left into the position of our current iterator,
                // so incrementing after a deletion would skip the next object.
                sndl.life -= 0.01;
                sndl.pos.y += 4;
                sandle_inter++;
                // TODO: IMPLEMENT ON YOUR OWN!!! // random -1 or +1
            }
        }


        // --- Draw / Render :

        // start drawing plus prerequisites
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
