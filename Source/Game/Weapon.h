#pragma once

#include <cstdlib>
#include "Animation/AnimationModule.h"
#include "Sound/SoundPack.h"
#include "Math/Math.h"

class Weapon
{
    const Animation* m_pAttackAnim;
    SoundPack m_soundPack;

    FRect m_hitBox; /** Range where hit can be registered */
    f32 m_damage;

public:
    Weapon() :
        m_pAttackAnim(nullptr), m_soundPack(), m_hitBox(0.0f, 0.0f, 0.0f, 0.0f), m_damage(0.0f) {}
    Weapon(const Animation* pAttackAnim, s32 soundCount, FRect hitBox, f32 damage) :
        m_pAttackAnim(pAttackAnim), m_soundPack(soundCount), m_hitBox(hitBox), m_damage(damage) {}

    void Init(const Animation* pAttackAnim, s32 soundCount, FRect hitBox, f32 damage);

    const Animation* GetAnimation() const { return m_pAttackAnim; }
    SoundPack& GetSoundPack() { return m_soundPack; }
    const FRect& GetHitBox() const { return m_hitBox; }
    f32 GetDamage() const { return m_damage; }

    void SetAnimation(const Animation* pAttackAnim) { m_pAttackAnim = pAttackAnim; }
    void SetHitBox(const FRect& hitBox) { m_hitBox = hitBox; }
    void SetDamage(f32 damage) { m_damage = damage; }

    void PlaySound() const;
    void PlaySound(i32f index) const;
};
