#include "Player.h"
#include "raymath.h"

Player :: Player(int winWidth, int winHeight) :
    windowWidth(winWidth), windowHeight(winHeight)  //class constructor
{
    width = texture.width / MaxAnimationFrame;
    height = texture.height;
}    

Vector2 Player::getScreenPos()
{
    return Vector2{
        (static_cast<float>(windowWidth) / 2.0f) - scale * (0.5f * width),
        (static_cast<float>(windowHeight) / 2.0f) - scale * (0.5f * height)
    };
}

void Player::tick(float DeltaTime)  // tick event
{
    if(!getAlive()) return; //do not do tick function if not alive
    // key check
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(GetFrameTime());    //override of the tick function

    Vector2 origin{};
    Vector2 offSet{};
    float rotation{};
    if(rightLeft > 0.f)     //facing right
    {
        origin = {0.f, weapon.height * scale};
        offSet = {35.f, 55.f};
        weaponCollisionRec = {
        getCollisionRec().x + offSet.x, 
        getCollisionRec().y + offSet.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else    //facing left
    {
        origin = {weapon.width * scale , weapon.height * scale};
        offSet = {25.f, 55.f};
        weaponCollisionRec = {
        getCollisionRec().x + offSet.x - weapon.width * scale, 
        getCollisionRec().y + offSet.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    //draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offSet.x, getScreenPos().y + offSet.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Player::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.f) setAlive(false);
}