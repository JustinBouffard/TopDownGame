#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D running_texture)
{
    worldPos = pos;
    texture = idle_texture;
    running = running_texture;

    width = texture.width / MaxAnimationFrame;
    height = texture.height;

    speed = 3.9f;
}

void Enemy::tick(float DeltaTime)
{
    if(!getAlive()) return;
    //get velocity
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius) undoMovment();
    BaseCharacter::tick(GetFrameTime());    //override of the tick function

    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * DeltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}