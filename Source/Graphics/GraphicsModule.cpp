/* TODO
 * - At some point we could have need in texture ID to prevent texture copies in memory
 */

/* ====== INCLUDES ====== */
#include <stdio.h>

#include "SDL_image.h"

#include "GTMath.h"
#include "GTUnit.h"
#include "RenderElement.h"
#include "GTTexture.h"

#include "GraphicsModule.h"

/* ====== DEFINES ====== */
#define MAX_TEXTURES 256

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

void GraphicsModule::PrepareToRender()
{
    // Clear screen
    SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(m_pRenderer);

    // Get camera position
    m_camera.GetPosition(m_cameraX, m_cameraY);
}

void GraphicsModule::Render()
{
    // Render
    RenderQueue(m_queueBackground);
    RenderQueue(m_queueDynamic);
    RenderQueue(m_queueForeground);
    RenderQueue(m_queueDebug);

    // Present
    SDL_RenderPresent(m_pRenderer);

    // Clean
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

void GraphicsModule::DrawFrame(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const GT_Texture* pTexture, s32 row, s32 col, f32 angle, SDL_RendererFlip flip)
{
    if (!pTexture)
    {
        AddNote(PR_WARNING, "DrawFrame() called with null texture");
        return;
    }

    // Check and correct destination rectangle
    SDL_Rect dest = dstRect;
    if (!CheckAndCorrectDest(dest, bHUD))
        return;

    // Push element
    PushRenderElement(renderMode, new RenderElementFrame(zIndex, dest, pTexture, row, col, angle, flip));
}

void GraphicsModule::DrawText(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const char* text, TTF_Font* pFont)
{
    // Check and correct destination rectangle
    SDL_Rect dest = dstRect;
    if (!CheckAndCorrectDest(dest, bHUD))
        return;

    // Push element
    PushRenderElement(renderMode, new RenderElementText(zIndex, dest, text, pFont));
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

b32f GraphicsModule::CheckAndCorrectDest(SDL_Rect& dest, b32 bHUD)
{
    // Make screen coords from world coords
    if (!bHUD)
    {
        dest.x -= m_cameraX;
        dest.y -= m_cameraY;
    }

    // Clip if we can't see it on screen
    if (dest.x + dest.w <= 0 || dest.y + dest.h <= 0 ||
        dest.x >= m_screenWidth || dest.y >= m_screenHeight)
        return false;
    return true;
}

void GraphicsModule::PushRenderElement(s32 renderMode, RenderElement* pElement)
{
    switch (renderMode)
    {
    case RENDER_MODE_BACKGROUND: PushStaticElement(m_queueBackground, pElement); break;
    case RENDER_MODE_DYNAMIC:    PushDynamicElement(m_queueDynamic, pElement); break;
    case RENDER_MODE_FOREGROUND: PushStaticElement(m_queueForeground, pElement); break;
    case RENDER_MODE_DEBUG:      PushStaticElement(m_queueDebug, pElement); break;

    default:
    {
        if (pElement)
            delete pElement;
        AddNote(PR_WARNING, "PushRenderElement: Unknown render mode %d", renderMode);
    } break;

    }
}

void GraphicsModule::PushStaticElement(TList<RenderElement*>& queue, RenderElement* pElement)
{
    auto end = queue.End();
    auto it = queue.Begin();

    // Check if there're nothing in queue
    if (it == end)
    {
        queue.Push(pElement);
        return;
    }

    // Try to find place
    for ( ; it != end; ++it)
    {
        if (pElement->zIndex <= it->data->zIndex)
        {
            queue.PushBefore(it, pElement);
            return;
        }
    }

    // So element's zIndex is the biggest
    queue.PushBack(pElement);
}

void GraphicsModule::PushDynamicElement(TList<RenderElement*>& queue, RenderElement* pElement)
{
    auto end = queue.End();
    auto it = queue.Begin();

    // Check if there're nothing in queue
    if (it == end)
    {
        queue.Push(pElement);
        return;
    }

    // Try to find place
    for ( ; it != end; ++it)
    {
        if (pElement->dest.y <= it->data->dest.y)
        {
            queue.PushBefore(it, pElement);
            return;
        }
    }

    // So element's zIndex is the biggest
    queue.PushBack(pElement);
}
