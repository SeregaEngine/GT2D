#ifndef SCRIPTMODULE_H_
#define SCRIPTMODULE_H_

/* ====== INCLUDES ====== */
extern "C"
{
#include "lua.h"
}

#include "EngineModule.h"

/* ====== STRUCTURES ====== */
class Actor;

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

    void CallFunction(const char* functionName, void* userdata);
    void CallFunction(const char* functionName);
    void Interpret(const char* text);
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

    // Draw
    // TODO(sean) Make it work after implementing render queue
    static s32 _setDrawColor(lua_State* L);
    static s32 _drawRect(lua_State* L);
    static s32 _fillRect(lua_State* L);

    // Camera
    static s32 _attachCamera(lua_State* L);
    static s32 _detachCamera(lua_State* L);
    static s32 _setCameraPosition(lua_State* L);
    static s32 _setCameraBounds(lua_State* L);

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

    // Console
    static s32 _isConsoleShown(lua_State* L);
    static s32 _cls(lua_State* L);

    /* AI */
    static s32 _defineState(lua_State* L);

    /* Animation */
    static s32 _defineAnimation(lua_State* L);

    /* Game */
    static s32 _stopGame(lua_State* L);

    /* World */
    // World's stuff
    static s32 _switchLocation(lua_State* L);

    static s32 _setBackground(lua_State* L);
    static s32 _setParallax(lua_State* L);
    static s32 _setGroundBounds(lua_State* L);

    // Entity
    static s32 _addEntity(lua_State* L);
    static s32 _updateEntity(lua_State* L);

    // Actor
    static s32 _addActor(lua_State* L);

    static s32 _setActorHealth(lua_State* L);
    static s32 _getActorHealth(lua_State* L);
    static s32 _toggleActorGodMode(lua_State* L);

    static s32 _setActorState(lua_State* L);
    static s32 _setActorTask(lua_State* L);
    static s32 _sendActorCmd(lua_State* L);

    static s32 _checkActorTask(lua_State* L);
    static s32 _getActorCurrentTask(lua_State* L);

    static s32 _setActorWeapon(lua_State* L);

    // Weapon
    static s32 _defineWeapon(lua_State* L);

    // Trigger
    static s32 _addTrigger(lua_State* L);
};

extern ScriptModule g_scriptModule;

#endif // SCRIPTMODULE_H_