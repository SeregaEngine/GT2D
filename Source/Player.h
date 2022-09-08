#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

class Player final: public Entity
{
public:
    virtual void Update(f32 dtTime) override;
private:
    void HandleEvents(f32 dtTime);
    void HandleAnimation(f32 dtTime);
};

#endif // PLAYER_H_