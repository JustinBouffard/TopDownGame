#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Player : public BaseCharacter
{
public:
    Player(int winWidth, int winHeight); 
    virtual void tick(float DeltaTime) override;
    virtual Vector2 getScreenPos() override;
    float getHealth() const {return health;}
    void takeDamage(float damage);
    Rectangle getWeaponCollisionRec() const {return weaponCollisionRec;}
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif