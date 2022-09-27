#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

/* ====== INCLUDES ====== */
#include <string.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Types.h"

/* ====== DEFINES ====== */
enum eRenderMode
{
    RENDER_BACKGROUND = 0,
    RENDER_DYNAMIC,
    RENDER_FOREGROUND,
    RENDER_DEBUG
};

/* ====== STRUCTURES ====== */
struct GT_Texture;

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
    void operator=(RenderQueueText& queueText)
        { memcpy(this, &queueText, sizeof(*this)); text = queueText.text; queueText.text = nullptr; }
    void CopyText(const char* _text)
        { text = new char[strlen(_text) + 1]; memcpy(text, _text, strlen(_text) + 1); }
private:
    RenderQueueText(const RenderQueueText&) = delete;
};

struct RenderQueueRect
{
    enum eAction { ACTION_FILL, ACTION_DRAW };

    SDL_Rect dest;
    SDL_Color color;
    s32 action;
};

struct RenderQueue
{
    s32 type;
    s32 zIndex; // Background, Foreground, Debug render modes
    union
    {
        struct RenderQueueFrame;
        struct RenderQueueText;
        struct RenderQueueRect;
    };
};

#endif // RENDERQUEUE_H