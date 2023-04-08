#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "Math/Math.h"
#include "Containers/List.h"
#include "Engine/Types.h"
#include "Engine/EngineModule.h"
#include "Graphics/Camera.h"

static constexpr i32f UNIT_SCREEN_WIDTH = 128;
static constexpr i32f UNIT_SCREEN_HEIGHT = 72;

enum eRenderMode
{
    RENDER_MODE_BACKGROUND = 0,
    RENDER_MODE_DYNAMIC,
    RENDER_MODE_FOREGROUND,
    RENDER_MODE_DEBUG
};

enum eFontID
{
    FONT_REGULAR = 0,
    FONT_LARGE,
    FONT_MONOSPACE
};

struct RenderElement;
struct Texture;

class GraphicsModule final : public EngineModule
{
    s32 m_screenWidth;
    s32 m_screenHeight;

    f32 m_pixelsPerUnitX;
    f32 m_pixelsPerUnitY;
    f32 m_invPixelsPerUnitX;
    f32 m_invPixelsPerUnitY;

    Camera m_camera;
    s32 m_cameraX, m_cameraY;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    TTF_Font* m_pGameFont;
    TTF_Font* m_pMenuFont;
    TTF_Font* m_pConsoleFont;

    SDL_Color m_drawColor;
    Texture* m_aTextures;

    TList<RenderElement*> m_queueBackground;
    TList<RenderElement*> m_queueDynamic;
    TList<RenderElement*> m_queueForeground;
    TList<RenderElement*> m_queueDebug;

public:
    GraphicsModule() : EngineModule("GraphicsModule", CHANNEL_GRAPHICS) {}

    void StartUp(SDL_Window* pWindow, SDL_Renderer* pRenderer, s32 width, s32 height);
    void ShutDown();

    void PrepareToRender();
    void Render();

    /** Null on error */
    const Texture* DefineTexture(const char* fileName, s32 spriteWidth, s32 spriteHeight);
    void UndefineTextures();

    void DrawFrame(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const Texture* pTexture, s32 row, s32 col, f32 angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawText(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const char* text, eFontID font = FONT_REGULAR);
    void FillRect(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect);
    void DrawRect(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect);

    forceinline void UnitsToPixels(f32& x, f32& y) const { x *= m_pixelsPerUnitX; y *= m_pixelsPerUnitY; }
    forceinline f32 UnitsToPixelsX(f32 x) const { return x * m_pixelsPerUnitX; }
    forceinline f32 UnitsToPixelsY(f32 y) const { return y * m_pixelsPerUnitY; }

    forceinline void PixelsToUnits(f32& x, f32& y) const { x *= m_invPixelsPerUnitX; y *= m_invPixelsPerUnitY; }
    forceinline f32 PixelsToUnitsX(f32 x) const { return x * m_invPixelsPerUnitX; }
    forceinline f32 PixelsToUnitsY(f32 y) const { return y * m_invPixelsPerUnitY; }

    forceinline f32 GetPixelsPerUnitX() const { return m_pixelsPerUnitX; }
    forceinline f32 GetPixelsPerUnitY() const { return m_pixelsPerUnitY; }
    forceinline f32 GetInvPixelsPerUnitX() const { return m_invPixelsPerUnitX; }
    forceinline f32 GetInvPixelsPerUnitY() const { return m_invPixelsPerUnitY; }

    forceinline s32 GetScreenWidth() const { return m_screenWidth; }
    forceinline s32 GetScreenHeight() const { return m_screenHeight; }

    forceinline SDL_Renderer* GetRenderer() const { return m_pRenderer; }
    forceinline Camera& GetCamera() { return m_camera; }

    forceinline const SDL_Color& GetDrawColor() const { return m_drawColor; }
    forceinline void SetDrawColor(u8 r, u8 g, u8 b, u8 a) { m_drawColor = { r, g, b, a }; }

private:
    void RenderQueue(const TList<RenderElement*>& queue) const;
    void CleanQueues();
    void CleanQueue(TList<RenderElement*>& queue);

    b32 CheckAndCorrectDest(SDL_Rect& dest, b32 bHUD);
    void PushRenderElement(s32 renderMode, RenderElement* pElement);
    void QueueElement(TList<RenderElement*>& queue, RenderElement* pElement);
};

inline GraphicsModule g_graphicsModule;
