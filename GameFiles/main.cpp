#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    // create window
    const int windowWidth{384}; 
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "TopDownGame");

    Texture2D map = LoadTexture("nature_tileset/sans titre.png"); // load map texture
    Vector2 mapPos{0.0f, 0.0f}; 
    const float mapScale{4.0f};

    Player player{windowWidth, windowHeight};  //create instance of player class
    Prop propArray[2]{      //create instance of the prop class
        Prop{Vector2{850.f, 850.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{845.f, 1500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{    //create instance of the enemy class
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_spritesheet.png"), 
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"), 
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemyArray[]{&goblin, &slime};

    for(auto enemy:enemyArray)
    {
        enemy->setTarget(&player);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(player.getWorldPos(), -1.f);
    
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);  // draw map to the screen
        player.tick(GetFrameTime());    //instance of tick function

        for (auto prop : propArray)  //initialize every prop in array 
        {
            prop.Render(player.getWorldPos());
        }

        if(!player.getAlive())  //player alive 
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else    //player not alive
        {
            std::string playerHealth = "Health: ";
            playerHealth.append(std::to_string(player.getHealth()), 0, 5);
            DrawText(playerHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        
        
        //check if player is out of the map boundaries
        if( player.getWorldPos().x < 0.f ||
            player.getWorldPos().y < 0.f || 
            player.getWorldPos().x + windowWidth > map.width * mapScale || 
            player.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            player.undoMovment();
        }

        for (auto prop : propArray) //initialize prop array
        {
            if (CheckCollisionRecs(player.getCollisionRec(), prop.getCollisionRec(player.getWorldPos()))) 
                player.undoMovment(); //check prop collision
        }

        for(auto enemy:enemyArray)  //initialize enemy array
        {
            enemy->tick(GetFrameTime());
        }

        //check sword collision
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for(auto enemy:enemyArray)
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), player.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        
        EndDrawing();
    }
    CloseWindow();
}