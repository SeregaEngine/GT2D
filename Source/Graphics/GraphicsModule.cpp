/* ====== TODO ======
 * - At some point we could have need in texture ID to prevent texture copies in memory
 * - Translate all drawing stuff to SDL textures
 */

/* ====== INCLUDES ====== */
#include <stdio.h>

#include "SDL_image.h"

#include "GTMath.h"
#include "GTUnit.h"

#include "GraphicsModule.h"

/* ====== DEFINES ====== */
#define MAX_TEXTURES 256

/* ====== STRUCTURES ====== */
struct GT_Texture
{
    SDL_Texture* pTexture;
    s32 textureWidth, textureHeight;
    s32 spriteWidth, spriteHeight;
};

/* ====== VARIABLES ====== */
GraphicsModule g_graphicsModule;

TTF_Font* GraphicsModule::s_pConsoleFont = nullptr;

/* ====== METHODS ====== */
b32 GraphicsModule::StartUp(SDL_Renderer* pRenderer, s32 width, s32 height)
{
    // Defaults
    m_screenWidth = width;
    m_screenHeight = height;

    m_camera.GetPosition(m_cameraX, m_cameraY);

    // Set global unitX/Y
    GTU::SetUnitXY(m_screenWidth / (f32)UNIT_SCREEN_WIDTH, m_screenHeight / (f32)UNIT_SCREEN_HEIGHT);

    // Renderer stuff
    m_drawColor = { 0x00, 0x00, 0x00, 0xFF };
    m_pRenderer = pRenderer;

    // Allocate textures
    m_aTextures = new GT_Texture[MAX_TEXTURES];
    for (i32f i = 0; i < MAX_TEXTURES; ++i)
        m_aTextures[i].pTexture = nullptr;

    // Open console font
    s_pConsoleFont = TTF_OpenFont("Fonts/Cascadia.ttf", 28);

    AddNote(PR_NOTE, "Module started");

    return true;
}

void GraphicsModule::ShutDown()
{
    // Close font
    if (s_pConsoleFont)
    {
        TTF_CloseFont(s_pConsoleFont);
        s_pConsoleFont = nullptr;
    }

    // Free textures
    for (i32f i = 0; i < MAX_TEXTURES; ++i)
        SDL_DestroyTexture(m_aTextures[i].pTexture);
    delete[] m_aTextures;

    // Free render queues
    CleanQueues();

    AddNote(PR_NOTE, "Module shut down");
}

void GraphicsModule::Render()
{
    RenderQueue(m_queueBackground);
    RenderQueue(m_queueDynamic);
    RenderQueue(m_queueForeground);
    RenderQueue(m_queueDebug);
    CleanQueues();
}

const GT_Texture* GraphicsModule::DefineTexture(const char* fileName, s32 spriteWidth, s32 spriteHeight)
{
    // Try to find free slot
    GT_Texture* pFree = nullptr;
    for (i32f i = 0; i < MAX_TEXTURES; ++i)
    {
        if (!m_aTextures[i].pTexture)
        {
            pFree = &m_aTextures[i];
            break;
        }
    }

    // There're not slots
    if (!pFree)
    {
        AddNote(PR_WARNING, "There're no free slot for texture: %s", fileName);
        return nullptr;
    }

    // Load surface
    SDL_Surface* pSurface = IMG_Load(fileName);
    if (!pSurface)
    {
        AddNote(PR_WARNING, "Can't load surface from file: %s", fileName);
        return nullptr;
    }

    // Set texture info
    pFree->textureWidth = pSurface->w;
    pFree->textureHeight = pSurface->h;
    pFree->spriteWidth = spriteWidth;
    pFree->spriteHeight = spriteHeight;

    // Create texture
    pFree->pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
    SDL_FreeSurface(pSurface);
    if (!pFree->pTexture)
    {
        AddNote(PR_WARNING, "Can't create texture from surface: %s", fileName);
        return nullptr;
    }

    return pFree;
}

void GraphicsModule::UndefineTextures()
{
    for (i32f i = 0; i < MAX_TEXTURES; ++i)
    {
        SDL_DestroyTexture(m_aTextures[i].pTexture);
        m_aTextures[i].pTexture = nullptr;
    }
}

void GraphicsModule::DrawFrame(s32 renderMode, s32 zIndex, b32 bHUD, SDL_Rect* dstRect, const GT_Texture* pTexture, s32 row, s32 col, f32 angle, SDL_RendererFlip flip)
{
    if (!pTexture)
    {
        AddNote(PR_WARNING, "Draw() called with null texture");
        return;
    }

    // Get camera position
    s32 cameraX, cameraY;
    m_camera.GetPosition(cameraX, cameraY);

    // Correct destination rectangle
    dstRect->x -= cameraX;
    dstRect->y -= cameraY;

    // Check if we shouldn't draw it
    if (dstRect->x + dstRect->w <= 0 || dstRect->y + dstRect->h <= 0 ||
        dstRect->x >= cameraX + m_screenWidth || dstRect->y >= cameraY + m_screenHeight)
        return;

    // Find sprite
    SDL_Rect srcRect = { pTexture->spriteWidth * col, pTexture->spriteHeight * row,
                         pTexture->spriteWidth, pTexture->spriteHeight };

    // Blit
    SDL_RenderCopyEx(m_pRenderer, pTexture->pTexture, &srcRect, dstRect, angle, nullptr, flip);
}

void GraphicsModule::DrawText(const SDL_Rect* dst, TTF_Font* pFont, const char* text, SDL_Color color)
{
    // Create text surface and convert to texture
    SDL_Surface* pSurface = TTF_RenderText_Blended(pFont, text, color);
    if (!pSurface)
    {
        AddNote(PR_WARNING, "DrawText(): Can't create surface: %s", TTF_GetError());
        return;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
    if (!pTexture)
    {
        SDL_FreeSurface(pSurface);
        AddNote(PR_WARNING, "DrawText(): Can't create texture from surface: %s", SDL_GetError());
        return;
    }

    // Blit to screen
    SDL_RenderCopy(m_pRenderer, pTexture, nullptr, dst);

    // Free memory
    SDL_FreeSurface(pSurface);
    SDL_DestroyTexture(pTexture);
}

void GraphicsModule::RenderQueue(const TList<RenderElement*>& queue) const
{
    auto end = queue.CEnd();
    for (auto it = queue.CBegin(); it != end; ++it)
        it->data->Render();
}

void GraphicsModule::CleanQueues()
{
    CleanQueue(m_queueBackground);
    CleanQueue(m_queueDynamic);
    CleanQueue(m_queueForeground);
    CleanQueue(m_queueDebug);
}

void GraphicsModule::CleanQueue(TList<RenderElement*>& queue)
{
    auto end = queue.End();
    for (auto it = queue.Begin(); it != end; ++it)
        delete it->data;
    queue.Clean();
}
