#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex); //class constructor
    void Render(Vector2 playerPos);
    Rectangle getCollisionRec(Vector2 playerPos);
private:
    Texture2D texture{};    //texture of the prop
    Vector2 worldPos{}; //position in the world
    float scale{4.f};   //scale of the prop (original scale * 4)
};