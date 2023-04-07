#ifndef GRAPHICSMODULE_H_
#define GRAPHICSMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL.h"
#include "SDL_ttf.h"

#include "Types.h"
#include "GTMath.h"
#include "EngineModule.h"
#include "Camera.h"
#include "TList.h"

/* ====== DEFINES ====== */
#define UNIT_SCREEN_WIDTH 128
#define UNIT_SCREEN_HEIGHT 72

enum eRenderMode
{
    RENDER_MODE_BACKGROUND = 0,
    RENDER_MODE_DYNAMIC,
    RENDER_MODE_FOREGROUND,
    RENDER_MODE_DEBUG
};

/* ====== STRUCTURES ====== */
struct RenderElement;
struct GT_Texture;

class GraphicsModule final : public EngineModule
{
public:
    static TTF_Font* s_pConsoleFont;
    static TTF_Font* s_pGameFont;
private:
    s32 m_screenWidth;
    s32 m_screenHeight;

    Camera m_camera;
    s32 m_cameraX, m_cameraY;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    SDL_Color m_drawColor;
    GT_Texture* m_aTextures;

    TList<RenderElement*> m_queueBackground;
    TList<RenderElement*> m_queueDynamic;
    TList<RenderElement*> m_queueForeground;
    TList<RenderElement*> m_queueDebug;

public:
    GraphicsModule() : EngineModule("GraphicsModule", CHANNEL_GRAPHICS) {}

    b32 StartUp(SDL_Window* pWindow, SDL_Renderer* pRenderer, s32 width, s32 height);
    void ShutDown();

    void PrepareToRender();
    void Render();

    const GT_Texture* DefineTexture(const char* fileName, s32 spriteWidth, s32 spriteHeight); // Null on error
    void UndefineTextures();

    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        { m_drawColor = { r, g, b, a }; }

    void DrawFrame(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, 
                   const GT_Texture* pTexture, s32 row, s32 col,
                   f32 angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawText(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const char* text, TTF_Font* pFont = s_pGameFont);
    void FillRect(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect);
    void DrawRect(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect);

    s32 GetScreenWidth() const { return m_screenWidth; }
    s32 GetScreenHeight() const { return m_screenHeight; }
    Camera& GetCamera() { return m_camera; }
    const SDL_Color& GetDrawColor() const { return m_drawColor; }
    SDL_Renderer* GetRenderer() { return m_pRenderer; }

private:
    void SetWindowIcon();

    void RenderQueue(const TList<RenderElement*>& queue) const;
    void CleanQueues();
    void CleanQueue(TList<RenderElement*>& queue);

    b32 CheckAndCorrectDest(SDL_Rect& dest, b32 bHUD);
    void PushRenderElement(s32 renderMode, RenderElement* pElement);
    void PushStaticElement(TList<RenderElement*>& queue, RenderElement* pElement);
    void PushDynamicElement(TList<RenderElement*>& queue, RenderElement* pElement);
};

inline GraphicsModule g_graphicsModule;

#endif // GRAPHICSMODULE_H_