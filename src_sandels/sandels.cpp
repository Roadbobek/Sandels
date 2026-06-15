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
            sandels.push_back({mousePosition.x - 6, mousePosition.y});
            sandels.push_back({mousePosition});
            sandels.push_back({mousePosition.x + 6, mousePosition.y});
            // explicitly calls the constructor (which is empty/default) to map mousePosition to pos, then structs defaults for others.
            // makes a temporary Sandel object with the structs values then moves it into the vector.
            // explicit constructor call, just aggregate initialization since we lack a constructor.
            // sandels.push_back(Sandel({mousePosition.x - 6, mousePosition.y}));
            // sandels.push_back(Sandel(mousePosition));
            // sandels.push_back(Sandel({mousePosition.x + 6, mousePosition.y}));
            // the two above lines do the same thing in our circumstances and are likely compiled identically,
            // this also applies to .insert() but not .exmplace_back(), it applies anywhere where a Sandel object is created.
            // on the line above the compiler automatically deduces the type Sandel because .push_back() expects the type Sandel
            // since it is writing to a vector constructed of the type Sandel.

            // combined three .push_back() calls into one .insert() call.
            // .insert() lets you insert multiple elements at once, it also allows for insertion anywhere in the vector.
            // we insert at the end with the position 'sandels.end()', but it is slower than .push_back() if inserting elsewhere than the end
            // since then the vectors elements must shift, with 'sandels.end()' the elements just get appended.
            // still makes a temporary Sandel object in memory before moving it into the vector.
            // compiler automatically deduces object type, type deduction.
            // we dont need to explicitly create a Sandel object, it is handled automatically.
            // although it does create a temporary array, an initialiser list, so it has to create 3 Sandel objects inside the created initialiser list,
            // then it moves the 3 Sandel objects out of the initialiser list and into our vector, which is unperfromant again.
            //sandels.insert(sandels.end(), {{mousePosition.x - 6, mousePosition.y}, {mousePosition}, {mousePosition.x + 6, mousePosition.y}});

            // .emplace_back() lets us directly insert an element at the end of an array by constructing it in place,
            // meaning no temporary object creation and moving occurs we just directly append to the vector.
            // since it direcly appends the passed object, it will not automatically deduce its type,
            // so we can explicitly create a Sandel object, but then a temporary object is created, then moved into the vector.
            // sounds familiar, this of course defeats the purpose of .emplace_back().
            // since our Sandel struct consists of 3 objects, 2 data types.
            // it contains a raylib Vector2, (which is a struct of 2 floats), then 2 floats.
            // we either need to pass an entire Sandel object or at minimum a Vector2 object and the struct handles the rest.
            // which both require temporary object creation.
            // which is still bad but better creating a Vector2 is still better than creating an entire Sandel
            // object with a Vector2 inside of it.
            // emplace_back uses iarenthesized initialization () to construct objects, while it allows flat aggregates, it fails for nested aggregates,
            // like a nested Vector2 struct inside the Sandels struct, push_back uses brace initialization {} which works for this.
            //sandels.emplace_back(Vector2{mousePosition.x - 6, mousePosition.y});
            //sandels.emplace_back(Vector2{mousePosition.x, mousePosition.y});
            //sandels.emplace_back(Vector2{mousePosition.x + 6, mousePosition.y});

            // one important thing to remember is that the compiler is so maticously optimised that all of these
            // approaches act a lot different from what you expect, they are all very optimised
        }

        for (size_t sandle_inter = 0; sandle_inter < sandels.size();)
        {
            // direct reference to memory with '&', Sandel& and &sndl have same effect
            Sandel &sndl = sandels[sandle_inter];
            //cout << "DEBUG: " "[Iteration: " << sandle_inter << ", X: " << sndl.pos.x << ", Y: " << sndl.pos.y << ", Life: " << sndl.life << ']' << endl; // DEBUG
                if (sndl.life <= 0.0001f)
            {
                // TODO: optimise deletion logic using O(N) instead of O(N²)
                // TODO: (currently everything inside the vector is shifted during deletion which is very a heavy operation)
                sandels.erase(sandels.begin() + sandle_inter); // weird accurate ig
                // line above deletes the sandel with 0 life left,
                // lines under delete the first sandel created when any sandel reaches 0 life,
                // making the above line more accurate if sandel life and spawn order
                // stops being the same, since now oldest sandel has the least health
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
