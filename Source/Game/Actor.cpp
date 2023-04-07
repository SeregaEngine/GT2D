#include "Input/InputModule.h"
#include "Engine/CollisionManager.h"
#include "Game/Game.h"
#include "Game/Weapon.h"
#include "Game/Actor.h"

void Actor::Init(const Vector2& vPosition, s32 width, s32 height, const Texture* pTexture)
{
    Entity::Init(vPosition, width, height, pTexture);
    m_type = ENTITY_TYPE_ACTOR;

    // Defaults
    m_actorState = ACTOR_STATE_IDLE;
    m_actorTeam = ACTOR_TEAM_DEFAULT;

    m_vSpeed = { g_graphicsModule.UnitsToPixelsX(ACTOR_DEFAULT_UNIT_SPEED_X),
                 g_graphicsModule.UnitsToPixelsY(ACTOR_DEFAULT_UNIT_SPEED_Y) };

    m_health = ACTOR_DEFAULT_HEALTH;
    m_bLookRight = true;

    m_pDeathSound = nullptr;

    m_attackRate = ACTOR_DEFAULT_ATTACK_RATE;
    m_pWeapon = nullptr;

    // Init AI
    m_state.SetActor(this);

    // Init default actor animations
    for (i32f i = 0; i < MAX_ACTOR_ANIMATIONS; ++i)
    {
        m_aActorAnims[i] = &DEFAULT_ACTOR_ANIMS[i];
    }
}

void Actor::Clean()
{
    Entity::Clean();
    RemoveTasks();
}

void Actor::Update(f32 dtTime)
{
    // Handle only animation if actor is dead
    if (HandleDeath())
    {
        HandleAnimation(dtTime);
        return;
    }

    // Handle AI stuff
    HandleAIState();
    HandleAITasks();
    HandleAICommand(dtTime);

    // React via changing state and it's animation
    HandleActorState(dtTime);
    HandleAnimation(dtTime);
}

void Actor::AddHealth(f32 diff)
{
    if (!m_bGodMode)
    {
        m_health += diff;
    }
}

void Actor::PushTask(AITask* pTask)
{
    if (pTask)
    {
        m_lstTask.Push(pTask);
    }
}

void Actor::RemoveTasks()
{
    m_lstTask.Foreach([] (auto pTask) { delete pTask; });
    m_lstTask.Clean();
}

b32 Actor::HandleDeath()
{
    if (m_health > 0)
    {
        return false;
    }

    // If we already handled our death
    if (m_actorState == ACTOR_STATE_DEAD)
    {
        return true;
    }

    // Play sound
    if (m_pDeathSound)
    {
        g_soundModule.PlaySound(m_pDeathSound);
    }

    // Init animation
    m_animFrame = 0;
    m_animElapsed = 0.0f;

    // Set state
    m_actorState = ACTOR_STATE_DEAD;

    return true;
}

void Actor::HandleActorState(f32 dtTime)
{
    switch (m_actorState)
    {
    case ACTOR_STATE_MOVE:
    {
        // Idle if we don't move
        if (!m_vVelocity.x && !m_vVelocity.y)
        {
            m_actorState = ACTOR_STATE_IDLE;
        }
    } break;

    case ACTOR_STATE_ATTACK:
    {
        // Idle if we don't attack too long
        if (m_animElapsed >= m_pAnim->frameDuration)
        {
            m_actorState = ACTOR_STATE_IDLE;
        }
    } break;

    case ACTOR_STATE_ANIMATE_ONCE:
    {
        // If we ended
        if (!m_pAnim || (m_animFrame >= m_pAnim->count - 1 &&
                         m_animElapsed + dtTime >= m_pAnim->frameDuration))
        {
            m_actorState = ACTOR_STATE_AFTER_ANIMATION;
        }
    } break;

    default: {} break;
    }
}

void Actor::HandleAITasks()
{
    auto it = m_lstTask.Begin();
    if (!it)
    {
        return;
    }

    // Handle first task, don't delete it
    it->data->Handle();

    // Handle other tasks and if they're done - delete them
    for (++it; it; )
    {
        it->data->Handle();
        if (it->data->GetStatus() != AITASK_INPROCESS)
        {
            AITask* pRemove = it->data;
            ++it;
            m_lstTask.Remove(pRemove);
            delete pRemove;
        }
        else
        {
            ++it;
        }
    }
}

void Actor::HandleAICommand(f32 dtTime)
{
    // Zero velocity
    m_vVelocity.Zero();

    // Handle command list
    while (!m_lstCommand.IsEmpty())
    {
        s32 cmd = m_lstCommand.Front();
        switch (cmd)
        {
        case AICMD_IDLE:       CommandIdle(); break;
        case AICMD_TURN_LEFT:  CommandTurnLeft(); break;
        case AICMD_TURN_RIGHT: CommandTurnRight(); break;
        case AICMD_ATTACK:     CommandAttack(); break;

        case AICMD_MOVE_UP:
        case AICMD_MOVE_LEFT:
        case AICMD_MOVE_DOWN:
        case AICMD_MOVE_RIGHT: CommandMove(cmd, dtTime); break;

        default: break;
        }
        m_lstCommand.Pop();
    }

    // Update position
    Vector2 vNewPosition = m_vPosition + m_vVelocity;
    if (m_bCollidable && !g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
    {
        // Try move only through x-axis
        vNewPosition.y -= m_vVelocity.y;
        if (!g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
        {
            // Try to move only through y-axis
            vNewPosition.x -= m_vVelocity.x;
            vNewPosition.y += m_vVelocity.y;
            if (!g_collisionMgr.IsOnGround(vNewPosition, m_hitBox))
            {
                // So we'll not move...
                vNewPosition.y -= m_vVelocity.y;
            }
        }
    }

    m_vPosition = vNewPosition;
}

void Actor::CommandMove(s32 cmd, f32 dtTime)
{
    switch (cmd)
    {
    case AICMD_MOVE_UP:    m_vVelocity.y -= m_vSpeed.y * dtTime; break;
    case AICMD_MOVE_LEFT:  m_vVelocity.x -= m_vSpeed.x * dtTime; break;
    case AICMD_MOVE_DOWN:  m_vVelocity.y += m_vSpeed.y * dtTime; break;
    case AICMD_MOVE_RIGHT: m_vVelocity.x += m_vSpeed.x * dtTime; break;

    default: break;
    }

    if (m_actorState == ACTOR_STATE_IDLE || m_actorState == ACTOR_STATE_AFTER_ANIMATION)
    {
        m_actorState = ACTOR_STATE_MOVE;
    }
}

void Actor::CommandAttack()
{
    // @NOTE: We use animations to detect on which state of attack we are

    b32 bHit = false;

    // If we already attacking
    if (m_actorState == ACTOR_STATE_ATTACK)
    {
        if (m_animElapsed >= m_attackRate)
        {
            m_animElapsed = 0.0f;
            ++m_animFrame;
            if (m_animFrame >= m_pAnim->count)
            {
                m_animFrame = 0;
            }

            bHit = true;
        }
    }
    else
    {
        m_pAnim = m_pWeapon ? m_pWeapon->GetAnimation() : m_aActorAnims[ACTOR_ANIMATION_IDLE];
        m_animFrame = 0;
        m_animElapsed = 0.0f;

        bHit = true;
        m_actorState = ACTOR_STATE_ATTACK;
    }

    // Play sound
    if (bHit && m_pWeapon)
    {
        m_pWeapon->PlaySound();

        // Get point for the hit registration
        Vector2 vPoint = m_vPosition;
        vPoint.x += m_bLookRight ? m_pWeapon->GetHitBox().x2 : m_pWeapon->GetHitBox().x1;

        // Get collided actors with this hit
        TList<Entity*> lstActor;
        g_collisionMgr.CheckCollision(
            vPoint,
            m_pWeapon->GetHitBox(),
            [] (auto pEntity, auto pAttackerUserdata) -> b32
            {
                Actor* pActor = (Actor*)pEntity;
                Actor* pAttacker = (Actor*)pAttackerUserdata;
                return
                    pEntity->GetType() == ENTITY_TYPE_ACTOR &&
                    (pActor->m_actorTeam == ACTOR_TEAM_DEFAULT || pActor->m_actorTeam != pAttacker->m_actorTeam);
            },
            this,
            lstActor,
            this
        );

        // Remove health from collided actors
        for (auto it = lstActor.Begin(); it; ++it)
        {
            static_cast<Actor*>(it->data)->AddHealth(-m_pWeapon->GetDamage());
        }
    }
}

void Actor::HandleAnimation(f32 dtTime)
{
    // Check if default animations aren't initialized
    if (!m_aActorAnims[ACTOR_ANIMATION_IDLE])
    {
        return;
    }

    // Set default animation if we don't have
    if (!m_pAnim)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE];
        m_animFrame = 0;
        m_animElapsed = 0.0f;
        if (!m_bLookRight)
        {
            m_flip = SDL_FLIP_HORIZONTAL;
        }
        return;
    }

    // Update timer
    m_animElapsed += dtTime;

    switch (m_actorState)
    {
    case ACTOR_STATE_IDLE:            AnimateIdle(); break;
    case ACTOR_STATE_AFTER_ANIMATION: AnimateAfterAnimation(); return;
    case ACTOR_STATE_MOVE:            AnimateMove(); break;
    case ACTOR_STATE_ATTACK:          AnimateAttack(); return;
    case ACTOR_STATE_INCAR:           AnimateInCar(); break;

    case ACTOR_STATE_DEAD:
    {
        if (AnimateDead())
        {
            return;
        }
    } break;

    default:
    {
        m_flip = m_bLookRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    } break;
    }

    // Update frame
    if (m_animElapsed > m_pAnim->frameDuration)
    {
        m_animElapsed = 0;
        ++m_animFrame;
    }

    // Loop animation and reset new animations with smaller count
    if (m_animFrame >= m_pAnim->count)
    {
        m_animFrame = 0;
    }
}

void Actor::AnimateIdle()
{
    m_pAnim = m_aActorAnims[ACTOR_ANIMATION_IDLE];

    m_flip = m_bLookRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Actor::AnimateAfterAnimation()
{
    m_flip = m_bLookRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Actor::AnimateMove()
{
    if (m_vVelocity.x > 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_HORIZONTAL];

        m_bLookRight = true;
        m_flip = SDL_FLIP_NONE;
    }
    else if (m_vVelocity.x < 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_HORIZONTAL];

        m_bLookRight = false;
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    else if (m_vVelocity.y > 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_BOTTOM];

        m_flip = SDL_FLIP_NONE;
    }
    else if (m_vVelocity.y < 0)
    {
        m_pAnim = m_aActorAnims[ACTOR_ANIMATION_TOP];

        m_flip = SDL_FLIP_NONE;
    }
}

void Actor::AnimateAttack()
{
    // Check if we need flip
    if (m_vVelocity.x > 0)
    {
        m_bLookRight = true;
        m_flip = SDL_FLIP_NONE;
    }
    else if (m_vVelocity.x < 0)
    {
        m_bLookRight = false;
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        m_flip = m_bLookRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    }
}

b32 Actor::AnimateDead()
{
    m_pAnim = m_aActorAnims[ACTOR_ANIMATION_DEAD];

    // Check if we done
    return m_animFrame == m_pAnim->count - 1;
}

void Actor::AnimateInCar()
{
    m_pAnim = m_aActorAnims[ACTOR_ANIMATION_INCAR];
}
