#ifndef GTTEXTURE_H_
#define GTTEXTURE_H_

/* ====== INCLUDES ====== */
#include "Types.h"

/* ====== STRUCTURES ====== */
struct SDL_Texture;

struct GT_Texture
{
    SDL_Texture* pTexture;
    s32 textureWidth, textureHeight;
    s32 spriteWidth, spriteHeight;
};

#endif // GTTEXTURE_H_