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

    if (m_vPosition.x + m_hitBox.x1 < 0.0f)
        m_vPosition.x = 0.0f + m_hitBox.x2;
    else if (m_vPosition.x + m_hitBox.x2 >= 1280.0f)
        m_vPosition.x = 1280.0f + m_hitBox.x1;

    f32 legsY = m_vPosition.y + m_hitBox.y2;
    if (legsY < 560.0f)
        m_vPosition.y = 560.0f + m_hitBox.y1;
    else if (legsY >= 720.0f)
        m_vPosition.y = 720.0f + m_hitBox.y1;
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