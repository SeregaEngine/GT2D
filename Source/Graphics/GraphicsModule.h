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
#include "RenderElement.h"

/* ====== DEFINES ====== */
#define UNIT_SCREEN_WIDTH 128
#define UNIT_SCREEN_HEIGHT 72

/* TODO(sean) Move this to GraphicsDefine.lua */
#define TW_LOCATION UNIT_SCREEN_WIDTH
#define TH_LOCATION UNIT_SCREEN_HEIGHT

#define TW_PARALLAX (UNIT_SCREEN_WIDTH * 2)
#define TH_PARALLAX UNIT_SCREEN_HEIGHT

/* ====== GLOBALS ====== */

/* ====== STRUCTURES ====== */
class GraphicsModule final : public EngineModule
{
public:
    static TTF_Font* s_pConsoleFont;
private:
    s32 m_screenWidth;
    s32 m_screenHeight;

    Camera m_camera;
    s32 m_cameraX, m_cameraY;

    SDL_Color m_drawColor;
    SDL_Renderer* m_pRenderer;
    GT_Texture* m_aTextures;

    TList<RenderElement*> m_queueBackground;
    TList<RenderElement*> m_queueDynamic;
    TList<RenderElement*> m_queueForeground;
    TList<RenderElement*> m_queueDebug;
public:
    GraphicsModule() : EngineModule("GraphicsModule", CHANNEL_GRAPHICS) {}

    b32 StartUp(SDL_Renderer* pRenderer, s32 width, s32 height);
    void ShutDown();

    void PrepareToRender() { m_camera.GetPosition(m_cameraX, m_cameraY); }
    void Render();

    void ClearScreen()
        { SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xFF); SDL_RenderClear(m_pRenderer); }
    void FlipScreen() { SDL_RenderPresent(m_pRenderer); }

    const GT_Texture* DefineTexture(const char* fileName, s32 spriteWidth, s32 spriteHeight); // null on error
    void UndefineTextures();

    void DrawFrame(s32 renderMode, s32 zIndex, b32 bHUD, SDL_Rect* dstRect, 
                   const GT_Texture* pTexture, s32 row, s32 col,
                   f32 angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawText(const SDL_Rect* dst, TTF_Font* pFont, const char* text, SDL_Color color);

    // TODO(sean) -> SetDrawColor(), don't change SDL's draw color
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        { m_drawColor = { r, g, b, a }; SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a); }
    void DrawRect(const SDL_Rect* dst) { SDL_RenderDrawRect(m_pRenderer, dst); }
    void FillRect(const SDL_Rect* dst) { SDL_RenderFillRect(m_pRenderer, dst); }

    s32 GetScreenWidth() const { return m_screenWidth; }
    s32 GetScreenHeight() const { return m_screenHeight; }
    Camera& GetCamera() { return m_camera; }
private:
    void RenderQueue(const TList<RenderElement*>& queue) const;
    void CleanQueues();
    void CleanQueue(TList<RenderElement*>& queue);
};

extern GraphicsModule g_graphicsModule;

#endif // GRAPHICSMODULE_H_