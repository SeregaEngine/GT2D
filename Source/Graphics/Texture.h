#pragma once

#include "Engine/Types.h"

struct SDL_Texture;

struct Texture
{
    SDL_Texture* pTexture;
    s32 textureWidth, textureHeight;
    s32 spriteWidth, spriteHeight;
};
