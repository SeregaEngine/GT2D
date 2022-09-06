#ifndef GRAPHICSMODULE_H_
#define GRAPHICSMODULE_H_

/* ====== INCLUDES ====== */
#include "Types.h"
#include "GTMath.h"
#include "EngineModule.h"

/* ====== DEFINES ====== */

/* ====== STRUCTURES ====== */
class GraphicsModule : public EngineModule
{
    s32 m_screenWidth;
    s32 m_screenHeight;

public:
    GraphicsModule() : EngineModule("GraphicsModule", CHANNEL_GRAPHICS) {}
    virtual ~GraphicsModule() {}

    b32 StartUp(s32 width, s32 height);
    void ShutDown();

    s32 GetScreenWidth() const { return m_screenWidth; }
    s32 GetScreenHeight() const { return m_screenHeight; }

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