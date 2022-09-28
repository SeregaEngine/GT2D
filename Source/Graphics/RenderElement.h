#ifndef RENDERELEMENT_H
#define RENDERELEMENT_H

/* ====== INCLUDES ====== */
#include <string.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Types.h"
#include "GraphicsModule.h"
#include "GTTexture.h"

/* ====== STRUCTURES ====== */
struct GT_Texture;

struct RenderElement
{
    s32 zIndex;
    SDL_Rect dest;

    RenderElement(s32 _zIndex, const SDL_Rect& _dest) : zIndex(_zIndex), dest(_dest) {}
    virtual ~RenderElement() {}
    virtual void Render() = 0;
};

struct RenderElementFrame final : public RenderElement
{
    const GT_Texture* pTexture;
    s32 row, col;
    f32 angle;
    SDL_RendererFlip flip;

    RenderElementFrame(s32 _zIndex, const SDL_Rect& _dest, const GT_Texture* _pTexture, s32 _row, s32 _col, f32 _angle, SDL_RendererFlip _flip)
        : RenderElement(_zIndex, _dest), pTexture(_pTexture), row(_row), col(_col), angle(_angle), flip(_flip) {}
    virtual void Render() override
    {
        // Find sprite
        SDL_Rect srcRect = { pTexture->spriteWidth * col, pTexture->spriteHeight * row,
                             pTexture->spriteWidth, pTexture->spriteHeight };

        // Blit
        SDL_RenderCopyEx(g_graphicsModule.GetRenderer(), pTexture->pTexture, &srcRect, &dest, angle, nullptr, flip);
    }
};

struct RenderElementText final : public RenderElement
{
    char* text;
    TTF_Font* pFont;
    SDL_Color color;

public:
    RenderElementText(s32 zIndex, const SDL_Rect& dest, const char* _text, TTF_Font* _pFont)
        : RenderElement(zIndex, dest), pFont(_pFont), color(g_graphicsModule.GetDrawColor())
        { text = new char[strlen(_text) + 1]; memcpy(text, _text, strlen(_text) + 1); }

    ~RenderElementText() { if (text) delete[] text; }

    virtual void Render() override
    {
        // Create text surface and convert to texture
        SDL_Surface* pSurface = TTF_RenderText_Blended(pFont, text, color);
        if (!pSurface)
        {
            g_debugLogMgr.AddNote(CHANNEL_GAME, PR_WARNING, "RenderElementText", "Can't create surface: %s", TTF_GetError());
            return;
        }
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(g_graphicsModule.GetRenderer(), pSurface);
        if (!pTexture)
        {
            SDL_FreeSurface(pSurface);
            g_debugLogMgr.AddNote(CHANNEL_GAME, PR_WARNING, "RenderElementText", "Can't create texture from surface: %s", TTF_GetError());
            return;
        }

        // Copy to screen
        SDL_RenderCopy(g_graphicsModule.GetRenderer(), pTexture, nullptr, &dest);

        // Free memory
        SDL_FreeSurface(pSurface);
        SDL_DestroyTexture(pTexture);
    }
};

/*
struct RenderQueueRect
{
    enum eAction { ACTION_FILL, ACTION_DRAW };

    SDL_Rect dest;
    SDL_Color color;
    s32 action;
};
*/
#endif // RENDERELEMENT_H