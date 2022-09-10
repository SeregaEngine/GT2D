#ifndef GRAPHICSMODULE_H_
#define GRAPHICSMODULE_H_

/* ====== INCLUDES ====== */
#include "SDL.h"

#include "Types.h"
#include "GTMath.h"
#include "EngineModule.h"
#include "Camera.h"

/* ====== DEFINES ====== */

/* === Lua domain === */

// Default sizes of sprites
#define TW_LOCATION 128
#define TH_LOCATION 72

#define TW_ACTOR 16
#define TH_ACTOR 16

#define TW_PARALLAX 256
#define TH_PARALLAX 72

// Texture ids
enum eTextureID
{
    TID_MISSION1 = 0,
    TID_MISSION1_PARALLAX,
    TID_GARAGE,
    TID_PLAYER
};

// Texture file names
#define TFN_MISSION1 "Textures/Locations/Mission1-1.png"
#define TFN_MISSION1_PARALLAX "Textures/Locations/Mission1-1_Parallax.png"
#define TFN_GARAGE "Textures/Locations/Garage.png"
#define TFN_PLAYER "Textures/Actors/Player.png"

/* ====== GLOBALS ====== */
extern f32 g_unitX; // Pixels per unit
extern f32 g_unitY;

/* ====== STRUCTURES ====== */
struct GT_Texture;

class GraphicsModule final : public EngineModule
{
    s32 m_screenWidth;
    s32 m_screenHeight;

    Camera m_camera;
    SDL_Renderer* m_pRenderer;
    GT_Texture* m_aTextures;
public:
    GraphicsModule() : EngineModule("GraphicsModule", CHANNEL_GRAPHICS) {}

    b32 StartUp(SDL_Renderer* pRenderer, s32 width, s32 height);
    void ShutDown();

    s32 GetScreenWidth() const { return m_screenWidth; }
    s32 GetScreenHeight() const { return m_screenHeight; }
    Camera& GetCamera() { return m_camera; }

    void ClearScreen()
        { SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xFF); SDL_RenderClear(m_pRenderer); }
    void FlipScreen() { SDL_RenderPresent(m_pRenderer); }

    GT_Texture* LoadTexture(s32 id, const char* fileName, s32 spriteWidth, s32 spriteHeight); // null on error
    void UnloadTexture(GT_Texture* pTexture);

    void Draw(const GT_Texture* pTexture, s32 row, s32 col,
              SDL_Rect* dstRect, f32 angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    /*
    void PlotPixel32(u32* videoBuffer, s32 pitch32, s32 x, s32 y, s32 a, s32 r, s32 g, s32 b) const
        { videoBuffer[y*pitch32 + x] = _RGB32BIT(a, r, g, b); }

    void DrawLine8(u8* videoBuffer, s32 pitch, s32 color, s32 fromX, s32 fromY, s32 toX, s32 toY) const;
    void DrawPoly2(const Poly2* poly, u8* videoBuffer, s32 pitch) const;

    void DrawTriangle(u8* videoBuffer, s32 pitch, s32 color, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3) const;
    void DrawTopTriangle(u8* videoBuffer, s32 pitch, s32 color, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3) const;
    void DrawBottomTriangle(u8* videoBuffer, s32 pitch, s32 color, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3) const;

    void DrawQuad2(u8* videoBuffer, s32 pitch, s32 color, s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3, s32 x4, s32 y4) const;
    */
private:
    b32 ClipLine(s32& fromX, s32& fromY, s32& toX, s32& toY) const;
};

extern GraphicsModule g_graphicsModule;

#endif // GRAPHICSMODULE_H_