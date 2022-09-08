/* TODO
 * - Remember to scale things like speed, boundaries
 */

#include "InputModule.h"
#include "Game.h"

#include "Player.h"

void Player::Update(f32 dtTime)
{
    HandleEvents(dtTime);

    g_debugLogMgr.AddNote(CHANNEL_GAME, PR_NOTE, "Player", "%f %f", m_vPosition.x, m_vPosition.y);
    m_vPosition = GTM::AddVec2(&m_vPosition, &m_vVelocity);
    if (m_vPosition.y < 560)
        m_vPosition.y = 560;
    if (m_vPosition.y >= 720)
        m_vPosition.y = 719;

    if (m_vPosition.x < 0)
        m_vPosition.x = 0;
    if (m_vPosition.x >= 1280)
        m_vPosition.x = 1279;
}

void Player::HandleEvents(f32 dtTime)
{
    SetVelocity(0.0f, 0.0f);

    if (g_inputModule.IsKeyDown(SDLK_ESCAPE))
    {
        g_game.Stop();
    }

    if (g_inputModule.IsKeyDown(SDLK_w))
    {
        m_vVelocity.y -= 0.5f * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_s))
    {
        m_vVelocity.y += 0.5f * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_a))
    {
        m_vVelocity.x -= 0.5f * dtTime;
    }
    if (g_inputModule.IsKeyDown(SDLK_d))
    {
        m_vVelocity.x += 0.5f * dtTime;
    }
}