#ifndef WEAPON_H_
#define WEAPON_H_

/* ====== INCLUDES ====== */
#include <stdlib.h>

#include "AnimationModule.h"
#include "GTSoundPack.h"
#include "GTMath.h"

/* ====== STRUCTURES ====== */
class Weapon
{
    const GT_Animation* m_pAttackAnim;
    GT_SoundPack m_soundPack;

    FRect m_hitBox; // It's like range where hit can be registered
    s32 m_damage;
public:
    Weapon() :
        m_pAttackAnim(nullptr), m_soundPack(), m_hitBox(0.0f, 0.0f, 0.0f, 0.0f), m_damage(0) {}
    Weapon(const GT_Animation* pAttackAnim, s32 soundCount, FRect hitBox, s32 damage) :
        m_pAttackAnim(pAttackAnim), m_soundPack(soundCount), m_hitBox(hitBox), m_damage(damage) {}

    void Init(const GT_Animation* pAttackAnim, s32 soundCount, FRect hitBox, s32 damage)
        { m_pAttackAnim = pAttackAnim; m_soundPack.Allocate(soundCount); m_hitBox = hitBox; m_damage = damage; }

    const GT_Animation* GetAnimation() const { return m_pAttackAnim; }
    GT_SoundPack& GetSoundPack() { return m_soundPack; }
    const FRect& GetHitBox() const { return m_hitBox; }
    s32 GetDamage() const { return m_damage; }

    void SetAnimation(const GT_Animation* pAttackAnim) { m_pAttackAnim = pAttackAnim; }
    void SetHitBox(const FRect& hitBox) { m_hitBox = hitBox; }
    void SetDamage(s32 damage) { m_damage = damage; }

    void PlaySound() const { if (m_soundPack.GetCount() > 0) m_soundPack.Play(rand() % m_soundPack.GetCount()); }
    void PlaySound(i32f index) const { if (m_soundPack.GetCount() > 0) m_soundPack.Play(index); }
};

#endif // WEAPON_H_