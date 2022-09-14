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
private:
    void DefineFunctions(lua_State* L);
    void DefineSymbols(lua_State* L);

    static void LuaNote(s32 priority, const char* fmt, ...);
    static b32 LuaExpect(lua_State* L, const char* funName, s32 expect);
    b32 CheckLua(lua_State* L, s32 res);

    /* Log */
    static s32 _GT_LOG(lua_State* L);

    /* Graphics */
    static s32 _defineTexture(lua_State* L);

    /* Sound */
    static s32 _defineSound(lua_State* L);
    static s32 _playSound(lua_State* L);

    /* Music */
    static s32 _defineMusic(lua_State* L);
    static s32 _playMusic(lua_State* L);

    /* World */
    static s32 _setBackground(lua_State* L);
    static s32 _setParallax(lua_State* L);
    static s32 _addPlayer(lua_State* L);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_