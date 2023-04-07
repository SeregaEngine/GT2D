#include "Game.h"
#include "Actor.h"
#include "GTUnit.h"
#include "Dialog.h"

#define DIALOG_TEXT_MARGIN_LEFT ((f32)m_width / 20.0f)
#define DIALOG_TEXT_MARGIN_TOP  ((f32)m_height / 15.0f)
#define DIALOG_LINE_WIDTH       ((f32)m_width - DIALOG_TEXT_MARGIN_LEFT * 2.0f)
#define DIALOG_LINE_HEIGHT      (((f32)m_height - DIALOG_TEXT_MARGIN_TOP * 3.0f) / (f32)DIALOG_STRING_HEIGHT)

void Dialog::Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_type = ENTITY_TYPE_DIALOG;
    m_bCollidable = false;

    m_renderMode = RENDER_MODE_FOREGROUND;
    m_zIndex = 0;

    m_pAttached = nullptr;
    m_time = 0.0f;
    m_bRunning = false;
    m_text[0] = 0;
}

void Dialog::Update(f32 dtTime)
{
    // Return if we're not running
    if (!m_bRunning)
    {
        return;
    }

    // Check time and attached entity
    if (m_time <= 0.0f || !g_game.GetWorld().HasEntity(m_pAttached))
    {
        m_bRunning = false;
        g_game.GetWorld().RemoveEntity(this);
        return;
    }

    // Handle time
    m_time -= dtTime;
}

void Dialog::Draw()
{
    if (!m_bRunning)
    {
        return;
    }

    // Update position
    HandlePosition();

    // Draw dialog box
    SDL_Rect dest = {
        (s32)m_vPosition.x, (s32)m_vPosition.y,
        m_width, m_height
    };
    g_graphicsModule.DrawFrame(m_renderMode, m_zIndex, false, dest, m_pTexture, 0, 0, 0.0f, m_flip);

    // Draw text
    dest.x += (s32)DIALOG_TEXT_MARGIN_LEFT;
    dest.y += (s32)DIALOG_TEXT_MARGIN_TOP;
    dest.w = (s32)DIALOG_LINE_WIDTH;
    dest.h = (s32)DIALOG_LINE_HEIGHT;

    i32f tempIndex = DIALOG_STRING_WIDTH;
    g_graphicsModule.SetDrawColor(0x00, 0x00, 0x00, 0xFF);
    for (i32f i = 0; i < DIALOG_STRING_HEIGHT; ++i)
    {
        // Null terminate string line
        char temp = m_text[tempIndex];
        m_text[tempIndex] = 0;

        // Draw this string line
        g_graphicsModule.DrawText(
            m_renderMode, m_zIndex + 1, false,
              dest, &m_text[tempIndex - DIALOG_STRING_WIDTH],
              GraphicsModule::s_pGameFont
        );

        // Recover string
        m_text[tempIndex] = temp;

        // Go to next line
        tempIndex += DIALOG_STRING_WIDTH;
        dest.y += dest.h;
    }
}

void Dialog::SetText(const char* text)
{
    // Copy text
    for (i32f i = 0; i < DIALOG_STRING_HEIGHT; ++i)
    {
        i32f j = 0;
        while (j < DIALOG_STRING_WIDTH)
        {
            i32f len = WordLength(text);
            if (len > DIALOG_STRING_WIDTH - j) // Linefeed, we have no room for this word
            {
                break;
            }
            else if (len <= 0) // Get next word, we have spaces here
            {
                // Try get next word
                text = NextWord(text);
                if (!*text)
                {
                    break;
                }
                
                // If we need space between words
                if (j > 0)
                {
                    m_text[i * DIALOG_STRING_WIDTH + j] = ' ';
                    ++j;
                }
                continue;
            }
            else // We have enough room for this word
            {
                memcpy(&m_text[i * DIALOG_STRING_WIDTH + j], text, len);
                j += len;
                text += len;
            }
        }

        memset(&m_text[i * DIALOG_STRING_WIDTH + j], ' ', DIALOG_STRING_WIDTH - j);
    }

    // Null-terminate
    m_text[DIALOG_STRSIZE] = 0;
}

void Dialog::HandlePosition()
{
    s32 cameraX, _;
    g_graphicsModule.GetCamera().GetPosition(cameraX, _);

    // X
    if (m_pAttached->m_bLookRight)
    {
        // Try right
        m_vPosition.x = m_pAttached->m_vPosition.x + m_pAttached->m_hitBox.x2;
        if (m_vPosition.x - cameraX > g_graphicsModule.GetScreenWidth() - m_width)
        {
            // Turn left
            m_vPosition.x = m_pAttached->m_vPosition.x + m_pAttached->m_hitBox.x1 - m_width;
            m_flip = SDL_FLIP_HORIZONTAL;
        }
        else
        {
            // Stay right
            m_flip = SDL_FLIP_NONE;
        }
    }
    else
    {
        // Try left
        m_vPosition.x = m_pAttached->m_vPosition.x + m_pAttached->m_hitBox.x1 - m_width;
        if (m_vPosition.x - cameraX < m_width - 1)
        {
            // Turn right
            m_vPosition.x = m_pAttached->m_vPosition.x + m_pAttached->m_hitBox.x2;
            m_flip = SDL_FLIP_NONE;
        }
        else
        {
            // Stay left
            m_flip = SDL_FLIP_HORIZONTAL;
        }
    }

    // Y
    m_vPosition.y = m_pAttached->m_vPosition.y + m_pAttached->m_hitBox.y1 - m_height;
}

i32f Dialog::WordLength(const char* text)
{
    i32f i = 0;
    for ( ; text[i] && text[i] != ' '; ++i)
        {}
    return i;
}

const char* Dialog::NextWord(const char* text)
{
    for (; *text && *text == ' '; ++text)
        {}
    return text;
}
