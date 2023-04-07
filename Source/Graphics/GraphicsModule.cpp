#include <cstdio>
#include "SDL_image.h"
#include "Math/Math.h"
#include "Graphics/RenderElement.h"
#include "Graphics/Texture.h"
#include "Graphics/GraphicsModule.h"

static constexpr i32f MAX_TEXTURES = 256;

void GraphicsModule::StartUp(SDL_Window* pWindow, SDL_Renderer* pRenderer, s32 width, s32 height)
{
    // Defaults
    m_screenWidth = width;
    m_screenHeight = height;

    m_camera.GetPosition(m_cameraX, m_cameraY);

    // Compute unit stuff
    m_pixelsPerUnitX = m_screenWidth / (f32)UNIT_SCREEN_WIDTH;
    m_invPixelsPerUnitX = 1.0f / m_pixelsPerUnitX;

    m_pixelsPerUnitY = m_screenHeight / (f32)UNIT_SCREEN_HEIGHT;
    m_invPixelsPerUnitY = 1.0f / m_pixelsPerUnitY;

    // SDL
    m_pWindow = pWindow;
    m_pRenderer = pRenderer;

    // Color
    m_drawColor = { 0x00, 0x00, 0x00, 0xFF };

    // Allocate textures
    m_aTextures = new Texture[MAX_TEXTURES];
    memset(m_aTextures, 0, sizeof(Texture) * MAX_TEXTURES);

    // Open console font
    m_pConsoleFont = TTF_OpenFont("Fonts/Cascadia.ttf", 48);
    m_pGameFont = TTF_OpenFont("Fonts/VT323-Regular.ttf", 148);

    // Set windows icon
    SetWindowIcon();

    AddNote(PR_NOTE, "Module started");
}

void GraphicsModule::ShutDown()
{
    // Close font
    if (m_pConsoleFont)
    {
        TTF_CloseFont(m_pConsoleFont);
        m_pConsoleFont = nullptr;
    }
    if (m_pGameFont)
    {
        TTF_CloseFont(m_pGameFont);
        m_pGameFont = nullptr;
    }

    // Free textures
    for (i32f i = 0; i < MAX_TEXTURES; ++i)
    {
        SDL_DestroyTexture(m_aTextures[i].pTexture);
    }
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

const Texture* GraphicsModule::DefineTexture(const char* fileName, s32 spriteWidth, s32 spriteHeight)
{
    // Try to find free slot
    Texture* pFree = nullptr;
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

void GraphicsModule::DrawFrame(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const Texture* pTexture, s32 row, s32 col, f32 angle, SDL_RendererFlip flip)
{
    if (!pTexture)
    {
        AddNote(PR_WARNING, "DrawFrame() called with null texture");
        return;
    }

    // Check and correct destination rectangle
    SDL_Rect dest = dstRect;
    if (!CheckAndCorrectDest(dest, bHUD))
    {
        return;
    }

    // Push element
    PushRenderElement(renderMode, new RenderElementFrame(zIndex, dest, pTexture, row, col, angle, flip));
}

void GraphicsModule::DrawText(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect, const char* text, eFontID font)
{
    // Check and correct destination rectangle
    SDL_Rect dest = dstRect;
    if (!CheckAndCorrectDest(dest, bHUD))
    {
        return;
    }

    // Push element
    PushRenderElement(renderMode, new RenderElementText(zIndex, dest, text, font == FONT_GAME ? m_pGameFont : m_pConsoleFont));
}

void GraphicsModule::FillRect(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect)
{
    // Check and correct destination rectangle
    SDL_Rect dest = dstRect;
    if (!CheckAndCorrectDest(dest, bHUD))
    {
        return;
    }

    // Push element
    PushRenderElement(renderMode, new RenderElementRect(zIndex, dest, RenderElementRect::ACTION_FILL));
}

void GraphicsModule::DrawRect(s32 renderMode, s32 zIndex, b32 bHUD, const SDL_Rect& dstRect)
{
    // Check and correct destination rectangle
    SDL_Rect dest = dstRect;
    if (!CheckAndCorrectDest(dest, bHUD))
    {
        return;
    }

    // Push element
    PushRenderElement(renderMode, new RenderElementRect(zIndex, dest, RenderElementRect::ACTION_DRAW));
}

void GraphicsModule::SetWindowIcon()
{
    SDL_Surface* pSurface = IMG_Load("Icon.png");
    SDL_SetWindowIcon(m_pWindow, pSurface);
    SDL_FreeSurface(pSurface);
}

void GraphicsModule::RenderQueue(const TList<RenderElement*>& queue) const
{
    auto end = queue.CEnd();
    for (auto it = queue.CBegin(); it != end; ++it)
    {
        it->data->Render();
    }
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
    {
        delete it->data;
    }
    queue.Clean();
}

b32 GraphicsModule::CheckAndCorrectDest(SDL_Rect& dest, b32 bHUD)
{
    // Make screen coords from world coords
    if (!bHUD)
    {
        dest.x -= m_cameraX;
        dest.y -= m_cameraY;
    }

    // Clip if we can't see it on screen
    return !(
        dest.x + dest.w <= 0 || dest.y + dest.h <= 0 ||
        dest.x > m_screenWidth || dest.y > m_screenHeight
    );
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
        {
            delete pElement;
        }
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
