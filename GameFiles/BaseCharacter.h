#ifndef BASE_CHARACTER_H 
#define BASE_CHARACTER_H

#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() const {return worldPos;};
    void undoMovment();
    Rectangle getCollisionRec();
    virtual void tick(float DeltaTime);
    virtual Vector2 getScreenPos() = 0 ;
    bool getAlive() const {return alive;}
    void setAlive(bool isAlive){alive = isAlive;}
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};   //base texture of the character 
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};  //idle animation of the character
    Texture2D running{LoadTexture("characters/knight_run_spritesheet.png")};    //running animation of the character
    Vector2 worldPos{}; //position of the world 
    Vector2 worldPosLastFrame{};    //position of the character in the last frame 
    float RunningTime{};  //running time of the animation
    int AnimationFrame{};   //animation frames of character animation
    int MaxAnimationFrame{6}; //number maximum of animation frames
    float UpdateTime{1.f / 12.f}; //update time of the animation
    // 1 : facing right -1 : facing left
    float rightLeft{1.f};   //character pointing to left or right 
    float speed{5.f}; // speed of the character
    float width{};  //width of the character 
    float height{}; //height of the character
    float scale{4.0f};  //scale of the character (orginal scale * scale)
    Vector2 velocity{}; //velocity of movment
private:
    bool alive{true};   //alive if true | dead if false
};

#endif