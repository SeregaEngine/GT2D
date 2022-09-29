#ifndef DIALOG_H_
#define DIALOG_H_

/* ====== INCLUDES ====== */
#include "Actor.h"

/* ====== DEFINES ====== */
#define DIALOG_STRING_WIDTH 14
#define DIALOG_STRING_HEIGHT 4
#define DIALOG_STRSIZE (DIALOG_STRING_WIDTH * DIALOG_STRING_HEIGHT)
#define DIALOG_BUFSIZE (DIALOG_STRSIZE + 1)

/* ====== STRUCTURES ====== */
class Dialog final : public Entity
{
    Actor* m_pAttached;
    f32 m_time;
    b32 m_bRunning;
    b32 m_bEnded;
    char m_text[DIALOG_BUFSIZE];
public:
    virtual void Init(const Vector2& vPosition, s32 width, s32 height, const GT_Texture* pTexture) override;
    virtual void Update(f32 dtTime) override;
    virtual void Draw() override;

    void Run() { m_bRunning = true; }
    void Attach(Actor* pActor) { m_pAttached = pActor; }
    void SetTime(f32 time) { m_time = time; }
    void SetText(const char* text);

    b32 HasEnded() const { return m_bEnded; }
};

#endif // DIALOG_H_