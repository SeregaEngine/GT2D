#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor.h"

class Player final : public Actor
{
public:
    virtual void Init(const Vec2& vPosition, s32 width, s32 height, GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;
};

#endif // PLAYER_H_