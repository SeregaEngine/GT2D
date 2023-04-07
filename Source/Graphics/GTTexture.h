#pragma once

#include "Engine/Types.h"

struct SDL_Texture;

struct GT_Texture
{
    SDL_Texture* pTexture;
    s32 textureWidth, textureHeight;
    s32 spriteWidth, spriteHeight;
};
