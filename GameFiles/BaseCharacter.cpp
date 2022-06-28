#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovment()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float DeltaTime)
{
    worldPosLastFrame = worldPos;

    // ANIMATION
    RunningTime += DeltaTime;
    if (RunningTime >= UpdateTime)
    {
        AnimationFrame++;
        RunningTime = 0.f;
        if (AnimationFrame > MaxAnimationFrame) AnimationFrame = 0;
    }

    // update maPos position
    if (Vector2Length(velocity) != 0.0f)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // right left if statement
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = running;
    }
    else // run or idle
    {
        texture = idle;
    }
    velocity = {};

    //DRAW THE CHARACTER
    Rectangle SourceRec{AnimationFrame * width, 0.f, rightLeft * width, height}; // create player source rec
    Rectangle DestRec{getScreenPos().x, getScreenPos().y, scale * width, scale * height}; // create player dest rec
    DrawTexturePro(texture, SourceRec, DestRec, Vector2{}, 0.0f, WHITE);    // draw texture to the screen    
}
