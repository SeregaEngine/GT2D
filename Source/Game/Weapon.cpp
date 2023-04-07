#include "Game/Weapon.h"

void Weapon::Init(const Animation* pAttackAnim, s32 soundCount, FRect hitBox, f32 damage)
{
    m_pAttackAnim = pAttackAnim;
    m_soundPack.Allocate(soundCount);
    m_hitBox = hitBox;
    m_damage = damage;
}

void Weapon::PlaySound() const
{
    if (m_soundPack.GetCount() > 0)
    {
        m_soundPack.Play(rand() % m_soundPack.GetCount());
    }
}

void Weapon::PlaySound(i32f index) const
{
    if (m_soundPack.GetCount() > 0)
    {
        m_soundPack.Play(index);
    }
}

