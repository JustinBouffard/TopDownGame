#include "raylib.h"
#include "BaseCharacter.h"
#include "Player.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D running_texture);  
    virtual void tick(float DeltaTime) override;
    Texture getEnemyTexture() const {return texture;}
    void setTarget(Player* player){target = player;};
    virtual Vector2 getScreenPos() override;
private:
    Player* target;
    float damagePerSec{18.f};
    float radius{25.f};
};