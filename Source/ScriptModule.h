#ifndef SCRIPTMODULE_H_
#define SCRIPTMODULE_H_

/* ====== INCLUDES ====== */
extern "C"
{
#include "lua.h"
}

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class ScriptModule final : public EngineModule
{
    lua_State* m_pLoader;
    lua_State* m_pMission;
public:
    ScriptModule() : EngineModule("ScriptModule", CHANNEL_SCRIPT) {}

    b32 StartUp();
    void ShutDown();

    b32 LoadMission();
    void UnloadMission();
    void UpdateMission(f32 dtTime);
private:
    void DefineFunctions(lua_State* L);
    void DefineSymbols(lua_State* L);

    static void LuaNote(s32 priority, const char* fmt, ...);
    static b32 LuaExpect(lua_State* L, const char* funName, s32 expect);
    b32 CheckLua(lua_State* L, s32 res);

    /* Log */
    static s32 _GT_LOG(lua_State* L);

    /* Graphics */
    // Textures
    static s32 _defineTexture(lua_State* L);

    // Camera
    static s32 _attachCamera(lua_State* L);
    static s32 _detachCamera(lua_State* L);
    static s32 _setCameraPosition(lua_State* L);
    static s32 _setLevelSize(lua_State* L);

    /* Sound */
    static s32 _defineSound(lua_State* L);
    static s32 _playSound(lua_State* L);

    /* Music */
    static s32 _defineMusic(lua_State* L);
    static s32 _playMusic(lua_State* L);

    /* Input */
    static s32 _isKeyDown(lua_State* L);
    static s32 _isMouseDown(lua_State* L);
    static s32 _getMousePosition(lua_State* L);

    /* Game */
    static s32 _stopGame(lua_State* L);

    /* World */
    // Background
    static s32 _setBackground(lua_State* L);
    static s32 _setParallax(lua_State* L);

    // Entity
    static s32 _addEntity(lua_State* L);
    static s32 _updateEntity(lua_State* L);

    // Actor
    static s32 _addActor(lua_State* L);
    static s32 _sendActorCmd(lua_State* L);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_