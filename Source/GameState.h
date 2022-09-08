#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Types.h"

class GameState
{
public:
    GameState() {}
    virtual ~GameState() {}

    virtual b32 OnEnter() { return true; }
    virtual void OnExit() {}

    virtual void Update(f32 dtTime) {}
    virtual void Render() {}
};

#endif // GAMESTATE_H_