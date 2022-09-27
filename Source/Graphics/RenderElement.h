#ifndef RENDERELEMENT_H
#define RENDERELEMENT_H

/* ====== INCLUDES ====== */
#include <string.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Types.h"

/* ====== DEFINES ====== */
enum eRenderMode
{
    RENDER_MODE_BACKGROUND = 0,
    RENDER_MODE_DYNAMIC,
    RENDER_MODE_FOREGROUND,
    RENDER_MODE_DEBUG
};

/* ====== STRUCTURES ====== */
struct GT_Texture;

/* TODO(sean)
struct RenderQueueFrame
{
    GT_Texture* pTexture;
    SDL_Rect dest;
    s32 row, col;
    f32 angle;
    SDL_RendererFlip flip;
};

struct RenderQueueText
{
    SDL_Rect dest;
    char* text;
    TTF_Font* pFont;
    SDL_Color color;

public:
    ~RenderQueueText() { if (text) delete[] text; }
    void CopyText(const char* _text)
        { text = new char[strlen(_text) + 1]; memcpy(text, _text, strlen(_text) + 1); }
};

struct RenderQueueRect
{
    enum eAction { ACTION_FILL, ACTION_DRAW };

    SDL_Rect dest;
    SDL_Color color;
    s32 action;
};
*/

struct RenderElement
{
    s32 zIndex;

    virtual void Render() = 0;
};

#endif // RENDERELEMENT_H