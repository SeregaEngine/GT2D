/* ====== INCLUDES ====== */
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

#include "GraphicsModule.h"
#include "GTUnit.h"
#include "SoundModule.h"
#include "InputModule.h"
#include "Console.h"
#include "Game.h"
#include "Actor.h"
#include "WaitTask.h"
#include "GotoTask.h"
#include "GotoEntityTask.h"
#include "KillTask.h"
#include "AnimateForTask.h"
#include "WaitAnimationTask.h"
#include "WaitDialogTask.h"
#include "RunDialogTask.h"
#include "FadeInTask.h"
#include "FadeOffTask.h"
#include "PushCommandTask.h"
#include "Weapon.h"
#include "Car.h"
#include "Trigger.h"
#include "Dialog.h"

#include "ScriptModule.h"

/* ====== VARIABLES ====== */
ScriptModule g_scriptModule;

/* ====== METHODS ====== */
b32 ScriptModule::StartUp()
{
    // Init lua
    m_pSaver = luaL_newstate();
    luaL_openlibs(m_pSaver);

    DefineFunctions(m_pSaver);
    DefineSymbols(m_pSaver);

    // Init loader script
    if (!CheckLua(m_pSaver, luaL_dofile(m_pSaver, "Scripts/Saver.lua")))
        return false;

    AddNote(PR_NOTE, "Module started");

    return true;
}

void ScriptModule::ShutDown()
{
    if (m_pSaver)
    {
        lua_close(m_pSaver);
        m_pSaver = nullptr;
    }

    AddNote(PR_NOTE, "Module shut down");
}

void ScriptModule::DefineFunctions(lua_State* L)
{
    /* Log */
    lua_register(L, "GT_LOG", _GT_LOG);

    /* Graphics */
    // Textures
    lua_register(L, "defineTexture", _defineTexture);

    // Draw
    lua_register(L, "setDrawColor", _setDrawColor);
    lua_register(L, "drawFrame", _drawFrame);
    lua_register(L, "drawText", _drawText);
    lua_register(L, "fillRect", _fillRect);
    lua_register(L, "drawRect", _drawRect);

    // Camera
    lua_register(L, "attachCamera", _attachCamera);
    lua_register(L, "detachCamera", _detachCamera);
    lua_register(L, "setCameraPosition", _setCameraPosition);
    lua_register(L, "setCameraBounds", _setCameraBounds);
    lua_register(L, "getCameraPosition", _getCameraPosition);

    /* Sound */
    lua_register(L, "defineSound", _defineSound);
    lua_register(L, "playSound", _playSound);

    /* Music */
    lua_register(L, "defineMusic", _defineMusic);
    lua_register(L, "playMusic", _playMusic);

    /* Input */
    lua_register(L, "isKeyDown", _isKeyDown);
    lua_register(L, "isMouseDown", _isMouseDown);
    lua_register(L, "getMousePosition", _getMousePosition);

    // Console
    lua_register(L, "isConsoleShown", _isConsoleShown);
    lua_register(L, "cls", _cls);

    /* AI */
    lua_register(L, "defineState", _defineState);

    /* Animation */
    lua_register(L, "defineAnimation", _defineAnimation);

    /* Game */
    lua_register(L, "getTicks", _getTicks);
    lua_register(L, "stopGame", _stopGame);
    lua_register(L, "switchMission", _switchMission);
    lua_register(L, "restartMission", _restartMission);

    /* World */
    lua_register(L, "hostSwitchLocation", _hostSwitchLocation);
    lua_register(L, "setGroundBounds", _setGroundBounds);
    lua_register(L, "hasWorldEntity", _hasWorldEntity);

    // Entities
    lua_register(L, "addEntity", _addEntity);
    lua_register(L, "removeEntity", _removeEntity);
    lua_register(L, "updateEntity", _updateEntity);
    lua_register(L, "setEntityPosition", _setEntityPosition);
    lua_register(L, "getEntityPosition", _getEntityPosition);
    lua_register(L, "setEntityVelocity", _setEntityVelocity);
    lua_register(L, "getEntityVelocity", _getEntityVelocity);
    lua_register(L, "setEntityHitBox", _setEntityHitBox);
    lua_register(L, "getEntityHitBox", _getEntityHitBox);
    lua_register(L, "toggleEntityCollidable", _toggleEntityCollidable);
    lua_register(L, "getEntityCollidable", _getEntityCollidable);
    lua_register(L, "setEntityAnimFrame", _setEntityAnimFrame);
    lua_register(L, "getEntityAnimFrame", _getEntityAnimFrame);
    lua_register(L, "setEntityAnimElapsed", _setEntityAnimElapsed);
    lua_register(L, "getEntityAnimElapsed", _getEntityAnimElapsed);
    lua_register(L, "setEntityAnim", _setEntityAnim);
    lua_register(L, "getEntityAnim", _getEntityAnim);
    lua_register(L, "setEntityRenderMode", _setEntityRenderMode);
    lua_register(L, "getEntityRenderMode", _getEntityRenderMode);
    lua_register(L, "setEntityZIndex", _setEntityZIndex);
    lua_register(L, "getEntityZIndex", _getEntityZIndex);
    lua_register(L, "toggleEntityHUD", _toggleEntityHUD);
    lua_register(L, "getEntityHUD", _getEntityHUD);
    lua_register(L, "setEntityTexture", _setEntityTexture);
    lua_register(L, "getEntityTexture", _getEntityTexture);

    // Actor
    lua_register(L, "addActor", _addActor);
    lua_register(L, "setActorTeam", _setActorTeam);
    lua_register(L, "getActorTeam", _getActorTeam);
    lua_register(L, "setActorHealth", _setActorHealth);
    lua_register(L, "getActorHealth", _getActorHealth);
    lua_register(L, "isActorAlive", _isActorAlive);
    lua_register(L, "toggleActorGodMode", _toggleActorGodMode);
    lua_register(L, "isActorLookRight", _isActorLookRight);
    lua_register(L, "turnActorLeft", _turnActorLeft);
    lua_register(L, "turnActorRight", _turnActorRight);
    lua_register(L, "setActorSpeed", _setActorSpeed);
    lua_register(L, "getActorSpeed", _getActorSpeed);
    lua_register(L, "setActorState", _setActorState);
    lua_register(L, "pushActorTask", _pushActorTask);
    lua_register(L, "pushActorCommand", _pushActorCommand);
    lua_register(L, "checkActorCurrentTask", _checkActorCurrentTask);
    lua_register(L, "getActorCurrentTask", _getActorCurrentTask);
    lua_register(L, "setActorDeathSound", _setActorDeathSound);
    lua_register(L, "setActorWeapon", _setActorWeapon);
    lua_register(L, "getActorAttackRate", _getActorAttackRate);
    lua_register(L, "setActorAttackRate", _setActorAttackRate);
    lua_register(L, "setActorAnim", _setActorAnim);
    lua_register(L, "playActorAnimOnce", _playActorAnimOnce);
    lua_register(L, "playActorAnimLooped", _playActorAnimLooped);
    lua_register(L, "stopActorAnim", _stopActorAnim);

    // Weapon
    lua_register(L, "defineWeapon", _defineWeapon);

    // Car
    lua_register(L, "addCar", _addCar);
    lua_register(L, "turnCarLeft", _turnCarLeft);
    lua_register(L, "turnCarRight", _turnCarRight);
    lua_register(L, "setCarMaxSpeed", _setCarMaxSpeed);
    lua_register(L, "setCarAcceleration", _setCarAcceleration);
    lua_register(L, "setCarPlacePosition", _setCarPlacePosition);
    lua_register(L, "putActorInCar", _putActorInCar);
    lua_register(L, "ejectActorFromCar", _ejectActorFromCar);

    // Trigger
    lua_register(L, "addTrigger", _addTrigger);

    // Dialog
    lua_register(L, "addDialog", _addDialog);
    lua_register(L, "runDialog", _runDialog);
    lua_register(L, "attachDialog", _attachDialog);
    lua_register(L, "setDialogTime", _setDialogTime);
    lua_register(L, "setDialogText", _setDialogText);
}

void ScriptModule::DefineSymbols(lua_State* L)
{
    /* Log */
    lua_pushinteger(L, PR_NOTE);
    lua_setglobal(L, "PR_NOTE");
    lua_pushinteger(L, PR_WARNING);
    lua_setglobal(L, "PR_WARNING");
    lua_pushinteger(L, PR_ERROR);
    lua_setglobal(L, "PR_ERROR");

    /* Graphics */
    lua_pushinteger(L, UNIT_SCREEN_WIDTH);
    lua_setglobal(L, "SCREEN_WIDTH");
    lua_pushinteger(L, UNIT_SCREEN_HEIGHT);
    lua_setglobal(L, "SCREEN_HEIGHT");

    lua_pushinteger(L, RENDER_MODE_BACKGROUND);
    lua_setglobal(L, "RENDER_MODE_BACKGROUND");
    lua_pushinteger(L, RENDER_MODE_DYNAMIC);
    lua_setglobal(L, "RENDER_MODE_DYNAMIC");
    lua_pushinteger(L, RENDER_MODE_FOREGROUND);
    lua_setglobal(L, "RENDER_MODE_FOREGROUND");
    lua_pushinteger(L, RENDER_MODE_DEBUG);
    lua_setglobal(L, "RENDER_MODE_DEBUG");

    /* Input */
    // WASD/Arrows
    lua_pushinteger(L, SDLK_w);
    lua_setglobal(L, "GTK_W");
    lua_pushinteger(L, SDLK_a);
    lua_setglobal(L, "GTK_A");
    lua_pushinteger(L, SDLK_s);
    lua_setglobal(L, "GTK_S");
    lua_pushinteger(L, SDLK_d);
    lua_setglobal(L, "GTK_D");

    lua_pushinteger(L, SDLK_UP);
    lua_setglobal(L, "GTK_UP");
    lua_pushinteger(L, SDLK_LEFT);
    lua_setglobal(L, "GTK_LEFT");
    lua_pushinteger(L, SDLK_DOWN);
    lua_setglobal(L, "GTK_DOWN");
    lua_pushinteger(L, SDLK_RIGHT);
    lua_setglobal(L, "GTK_RIGHT");

    // Some special symbols
    lua_pushinteger(L, SDLK_ESCAPE);
    lua_setglobal(L, "GTK_ESCAPE");
    lua_pushinteger(L, SDLK_RETURN);
    lua_setglobal(L, "GTK_RETURN");
    lua_pushinteger(L, SDLK_SPACE);
    lua_setglobal(L, "GTK_SPACE");

    // Mouse
    lua_pushinteger(L, GTM_LEFT);
    lua_setglobal(L, "GTM_LEFT");
    lua_pushinteger(L, GTM_RIGHT);
    lua_setglobal(L, "GTM_RIGHT");
    lua_pushinteger(L, GTM_MIDDLE);
    lua_setglobal(L, "GTM_MIDDLE");

    /* Actor */
    lua_pushinteger(L, ACTOR_ANIMATION_IDLE);
    lua_setglobal(L, "ACTOR_ANIMATION_IDLE");
    lua_pushinteger(L, ACTOR_ANIMATION_HORIZONTAL);
    lua_setglobal(L, "ACTOR_ANIMATION_HORIZONTAL");
    lua_pushinteger(L, ACTOR_ANIMATION_TOP);
    lua_setglobal(L, "ACTOR_ANIMATION_TOP");
    lua_pushinteger(L, ACTOR_ANIMATION_BOTTOM);
    lua_setglobal(L, "ACTOR_ANIMATION_BOTTOM");
    lua_pushinteger(L, ACTOR_ANIMATION_DEAD);
    lua_setglobal(L, "ACTOR_ANIMATION_DEAD");
    lua_pushinteger(L, ACTOR_ANIMATION_INCAR);
    lua_setglobal(L, "ACTOR_ANIMATION_INCAR");
    lua_pushinteger(L, ACTOR_TEAM_DEFAULT);
    lua_setglobal(L, "ACTOR_TEAM_DEFAULT");

    /* AI */
    lua_pushinteger(L, GTC_IDLE);
    lua_setglobal(L, "GTC_IDLE");
    lua_pushinteger(L, GTC_TURN_LEFT);
    lua_setglobal(L, "GTC_TURN_LEFT");
    lua_pushinteger(L, GTC_TURN_RIGHT);
    lua_setglobal(L, "GTC_TURN_RIGHT");
    lua_pushinteger(L, GTC_MOVE_UP);
    lua_setglobal(L, "GTC_MOVE_UP");
    lua_pushinteger(L, GTC_MOVE_LEFT);
    lua_setglobal(L, "GTC_MOVE_LEFT");
    lua_pushinteger(L, GTC_MOVE_DOWN);
    lua_setglobal(L, "GTC_MOVE_DOWN");
    lua_pushinteger(L, GTC_MOVE_RIGHT);
    lua_setglobal(L, "GTC_MOVE_RIGHT");
    lua_pushinteger(L, GTC_ATTACK);
    lua_setglobal(L, "GTC_ATTACK");

    lua_pushinteger(L, GTT_NONE);
    lua_setglobal(L, "GTT_NONE");
    lua_pushinteger(L, GTT_INPROCESS);
    lua_setglobal(L, "GTT_INPROCESS");
    lua_pushinteger(L, GTT_IMPOSSIBLE);
    lua_setglobal(L, "GTT_IMPOSSIBLE");
    lua_pushinteger(L, GTT_DONE);
    lua_setglobal(L, "GTT_DONE");

    lua_pushinteger(L, GTT_WAIT);
    lua_setglobal(L, "GTT_WAIT");
    lua_pushinteger(L, GTT_GOTO);
    lua_setglobal(L, "GTT_GOTO");
    lua_pushinteger(L, GTT_GOTO_ENTITY);
    lua_setglobal(L, "GTT_GOTO_ENTITY");
    lua_pushinteger(L, GTT_KILL);
    lua_setglobal(L, "GTT_KILL");
    lua_pushinteger(L, GTT_ANIMATE_FOR);
    lua_setglobal(L, "GTT_ANIMATE_FOR");
    lua_pushinteger(L, GTT_WAIT_ANIMATION);
    lua_setglobal(L, "GTT_WAIT_ANIMATION");
    lua_pushinteger(L, GTT_WAIT_DIALOG);
    lua_setglobal(L, "GTT_WAIT_DIALOG");
    lua_pushinteger(L, GTT_RUN_DIALOG);
    lua_setglobal(L, "GTT_RUN_DIALOG");
    lua_pushinteger(L, GTT_FADE_IN);
    lua_setglobal(L, "GTT_FADE_IN");
    lua_pushinteger(L, GTT_FADE_OFF);
    lua_setglobal(L, "GTT_FADE_OFF");
    lua_pushinteger(L, GTT_PUSH_COMMAND);
    lua_setglobal(L, "GTT_PUSH_COMMAND");
}

lua_State* ScriptModule::LoadMission(const char* path, s32 location)
{
    // Create mission lua state
    lua_State* pScript = luaL_newstate();
    luaL_openlibs(pScript);

    // Define all engine stuff
    DefineFunctions(pScript);
    DefineSymbols(pScript);

    // Try to open script
    if (!CheckLua(pScript, luaL_dofile(pScript, path)))
    {
        lua_pop(pScript, 1); // Pop "getMission"
        lua_close(pScript);
        return nullptr;
    }

    // Pop "getMission"
    lua_pop(pScript, 1);

    // Get onEnter()
    lua_getglobal(pScript, "onEnter");
    if (!lua_isfunction(pScript, -1))
    {
        lua_pop(pScript, 1); // Pop "onEnter"
        lua_close(pScript);
        return nullptr;
    }

    // Call onEnter()
    lua_pushinteger(pScript, location);
    if (!CheckLua(pScript, lua_pcall(pScript, 1, 0, 0)))
    {
        lua_close(pScript);
        return nullptr;
    }

    return pScript;
}

void ScriptModule::UnloadMission(lua_State* pScript)
{
    if (pScript)
        lua_close(pScript);
}

void ScriptModule::UpdateMission(lua_State* pScript, f32 dtTime)
{
    lua_getglobal(pScript, "onUpdate");
    lua_pushnumber(pScript, dtTime);

    if (lua_pcall(pScript, 1, 0, 0) != 0)
    {
        LuaNote(PR_ERROR, "UpdateMission(): %s", lua_tostring(pScript, -1));
        lua_pop(pScript, 1);
    }
}

void ScriptModule::RenderMission(lua_State* pScript)
{
    CallFunction(pScript, "onRender");
}

void ScriptModule::CallFunction(lua_State* pScript, const char* functionName, void* userdata)
{
    // Check for null
    if (!functionName)
    {
        AddNote(PR_WARNING, "CallFunction() called with null functionName");
        return;
    }

    // Call function
    lua_getglobal(pScript, functionName);
    lua_pushlightuserdata(pScript, userdata);

    if (lua_pcall(pScript, 1, 0, 0) != 0)
    {
        LuaNote(PR_ERROR, "CallFunction(): Error when function %s called: %s", functionName, lua_tostring(pScript, -1));
        lua_pop(pScript, 1);
    }
}

void ScriptModule::CallFunction(lua_State* pScript, const char* functionName)
{
    // Check for null
    if (!functionName)
    {
        AddNote(PR_WARNING, "CallFunction() called with null functionName");
        return;
    }

    // Call function
    lua_getglobal(pScript, functionName);
    if (lua_pcall(pScript, 0, 0, 0) != 0)
    {
        LuaNote(PR_ERROR, "CallFunction(): Error when function %s called: %s", functionName, lua_tostring(pScript, 1));
        lua_pop(pScript, 1);
    }
}

void ScriptModule::CallTrigger(lua_State* pScript, const char* functionName, Trigger* pTrigger, Entity* pEntity)
{
    // Check for null
    if (!functionName)
    {
        AddNote(PR_WARNING, "CallFunction() called with null functionName");
        return;
    }

    // Call function
    lua_getglobal(pScript, functionName);
    lua_pushlightuserdata(pScript, (void*)pTrigger);
    lua_pushlightuserdata(pScript, (void*)pEntity);
    if (lua_pcall(pScript, 2, 0, 0) != 0)
    {
        LuaNote(PR_ERROR, "CallFunction(): Error when function %s called: %s", functionName, lua_tostring(pScript, 1));
        lua_pop(pScript, 1);
    }
}

void ScriptModule::Interpret(lua_State* pScript, const char* text)
{
    if (0 != luaL_dostring(pScript, text))
    {
        LuaNote(PR_WARNING, lua_tostring(pScript, -1));
        lua_pop(pScript, 1);
    }
}

void ScriptModule::LuaNote(s32 priority, const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    g_debugLogMgr.VAddNote(CHANNEL_SCRIPT, priority, "Lua", fmt, vl);
    va_end(vl);
}

b32 ScriptModule::LuaExpect(lua_State* L, const char* funName, s32 expect)
{
    s32 given;
    if ((given = lua_gettop(L)) == expect)
    {
        return true;
    }
    else
    {
        LuaNote(PR_ERROR, "%s(): Expected %d arguments, but %d given", funName, expect, lua_gettop(L));
        return false;
    }
}

b32 ScriptModule::CheckLua(lua_State* L, s32 res)
{
    if (res != LUA_OK)
    {
        AddNote(PR_WARNING, "CheckLua(): %s", lua_tostring(L, -1));
        lua_pop(L, 1); // Pop error
        return false;
    }

    return true;
}

s32 ScriptModule::_GT_LOG(lua_State* L)
{
    if (!LuaExpect(L, "GT_LOG", 2))
        return -1;

    if (lua_isinteger(L, 1) && lua_isstring(L, 2))
        LuaNote((s32)lua_tointeger(L, 1), lua_tostring(L, 2));

    return 0;
}

s32 ScriptModule::_defineTexture(lua_State* L)
{
    if (!LuaExpect(L, "defineTexture", 3))
        return -1;

    lua_pushlightuserdata(L, (void*)g_graphicsModule.DefineTexture(lua_tostring(L, 1),
                                                                   (s32)lua_tointeger(L, 2),
                                                                   (s32)lua_tointeger(L, 3)));

    return 1;
}

s32 ScriptModule::_setDrawColor(lua_State* L)
{
    if (!LuaExpect(L, "setDrawColor", 4))
        return -1;

    g_graphicsModule.SetDrawColor((u8)lua_tointeger(L, 1), (u8)lua_tointeger(L, 2),
                                (u8)lua_tointeger(L, 3), (u8)lua_tointeger(L, 4));

    return 0;
}

s32 ScriptModule::_drawFrame(lua_State* L)
{
    i32f argsCount = lua_gettop(L);
    if (argsCount != 10 && argsCount != 12)
    {
        LuaNote(PR_ERROR, "drawFrame(): Expected 10 or 12 arguments but %d given", argsCount);
        return -1;
    }

    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };
    if (argsCount == 10)
        g_graphicsModule.DrawFrame((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (b32)lua_toboolean(L, 3), dest, (const GT_Texture*)lua_touserdata(L, 8), (s32)lua_tointeger(L, 9), (s32)lua_tointeger(L, 10));
    else
        g_graphicsModule.DrawFrame((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (b32)lua_toboolean(L, 3), dest, (const GT_Texture*)lua_touserdata(L, 8), (s32)lua_tointeger(L, 9), (s32)lua_tointeger(L, 10), (f32)lua_tonumber(L, 11), (SDL_RendererFlip)lua_tointeger(L, 12));

    return 0;
}

s32 ScriptModule::_drawText(lua_State* L)
{
    if (!LuaExpect(L, "drawText", 8))
        return -1;

    s32 renderMode = (s32)lua_tointeger(L, 1);
    s32 zIndex = (s32)lua_tointeger(L, 2);
    b32 bHUD = (b32)lua_toboolean(L, 3);
    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };
    const char* text = lua_tostring(L, 8);

    g_graphicsModule.DrawText(renderMode, zIndex, bHUD, dest, text);

    return 0;
}

s32 ScriptModule::_fillRect(lua_State* L)
{
    if (!LuaExpect(L, "fillRect", 7))
        return -1;

    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };

    g_graphicsModule.FillRect((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (s32)lua_toboolean(L, 3), dest);

    return 0;
}

s32 ScriptModule::_drawRect(lua_State* L)
{
    if (!LuaExpect(L, "drawRect", 7))
        return -1;

    SDL_Rect dest = {
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
        (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 6)),
        (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 7))
    };

    g_graphicsModule.DrawRect((s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (s32)lua_toboolean(L, 3), dest);
    return 0;
}

s32 ScriptModule::_attachCamera(lua_State* L)
{
    if (!LuaExpect(L, "attachCamera", 1))
        return -1;

    g_graphicsModule.GetCamera().Attach( (Entity*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_detachCamera(lua_State* L)
{
    if (!LuaExpect(L, "detachCamera", 0))
        return -1;

    g_graphicsModule.GetCamera().Detach();

    return 0;
}

s32 ScriptModule::_setCameraPosition(lua_State* L)
{
    if (!LuaExpect(L, "setCameraPosition", 2))
        return -1;

    g_graphicsModule.GetCamera().SetPosition((s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                                             (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 2)));

    return 0;
}

s32 ScriptModule::_setCameraBounds(lua_State* L)
{
    if (!LuaExpect(L, "setCameraBounds", 4))
        return -1;

    SRect rect;
    rect.x1 = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 1)) );
    rect.y1 = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) );
    rect.x2 = rect.x1 + (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) ) - 1;
    rect.y2 = rect.y1 + (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) ) - 1;

    g_graphicsModule.GetCamera().SetBounds(rect);

    return 0;
}

s32 ScriptModule::_getCameraPosition(lua_State* L)
{
    if (!LuaExpect(L, "getCameraPosition", 0))
        return -1;

    s32 x, y;
    g_graphicsModule.GetCamera().GetPosition(x, y);

    lua_pushnumber(L, GTU::ScreenToUnitX((f32)x));
    lua_pushnumber(L, GTU::ScreenToUnitY((f32)y));

    return 2;
}

s32 ScriptModule::_hostSwitchLocation(lua_State* L)
{
    if (!LuaExpect(L, "hostSwitchLocation", 1))
        return -1;

    g_game.GetWorld().SwitchLocation(lua_tostring(L, 1));

    return 0;
}

s32 ScriptModule::_setGroundBounds(lua_State* L)
{
    if (!LuaExpect(L, "setGroundBounds", 4))
        return -1;

    SRect rect;
    rect.x1 = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 1)) );
    rect.y1 = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) );
    rect.x2 = rect.x1 + (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) ) - 1;
    rect.y2 = rect.y1 + (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) ) - 1,

    g_game.GetWorld().SetGroundBounds(rect);

    return 0;
}

s32 ScriptModule::_hasWorldEntity(lua_State* L)
{
    if (!LuaExpect(L, "hasWorldEntity", 1))
        return -1;

    lua_pushboolean(L, g_game.GetWorld().HasEntity((Entity*)lua_touserdata(L, 1)));

    return 1;
}

s32 ScriptModule::_defineSound(lua_State* L)
{
    if (!LuaExpect(L, "defineSound", 1))
        return -1;

    lua_pushlightuserdata(L, g_soundModule.DefineWAV(lua_tostring(L, 1)));

    return 1;
}

s32 ScriptModule::_playSound(lua_State* L)
{
    if (!LuaExpect(L, "playSound", 1))
        return -1;

    g_soundModule.PlaySound( (GT_Sound*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_defineMusic(lua_State* L)
{
    if (!LuaExpect(L, "defineMusic", 1))
        return -1;

    lua_pushlightuserdata(L, g_soundModule.DefineMusic(lua_tostring(L, 1)));

    return 1;
}

s32 ScriptModule::_playMusic(lua_State* L)
{
    if (!LuaExpect(L, "playMusic", 1))
        return -1;

    g_soundModule.PlayMusic( (GT_Music*)lua_touserdata(L, 1) );

    return 0;
}

s32 ScriptModule::_isKeyDown(lua_State* L)
{
    if (!LuaExpect(L, "isKeyDown", 1))
        return -1;

    lua_pushboolean(L, g_inputModule.IsKeyDown((SDL_Keycode)lua_tointeger(L, 1)));

    return 1;
}

s32 ScriptModule::_isMouseDown(lua_State* L)
{
    if (!LuaExpect(L, "isMouseDown", 1))
        return -1;

    lua_pushboolean(L, g_inputModule.IsMouseDown((Uint32)lua_tointeger(L, 1)));

    return 1;
}

s32 ScriptModule::_getMousePosition(lua_State* L)
{
    if (!LuaExpect(L, "getMousePosition", 0))
        return -1;

    // Get mouse screen position
    s32 x, y;
    g_inputModule.GetMousePosition(x, y);

    // Return
    lua_pushinteger(L, (lua_Integer)( GTU::ScreenToUnitX((f32)x) ));
    lua_pushinteger(L, (lua_Integer)( GTU::ScreenToUnitY((f32)y) ));

    return 2;
}

s32 ScriptModule::_isConsoleShown(lua_State* L)
{
    lua_pushboolean(L, g_console.IsShown());

    return 1;
}

s32 ScriptModule::_cls(lua_State* L)
{
    g_console.Clear();

    return 0;
}

s32 ScriptModule::_defineState(lua_State* L)
{
    if (!LuaExpect(L, "defineState", 1))
        return -1;

    lua_pushlightuserdata(L, (void*)g_AIModule.DefineState(lua_tostring(L, 1)));

    return 1;
}

s32 ScriptModule::_defineAnimation(lua_State* L)
{
    if (!LuaExpect(L, "defineAnimation", 3))
        return -1;

    GT_Animation anim = { (s32)lua_tointeger(L, 1), (s32)lua_tointeger(L, 2), (f32)lua_tonumber(L, 3) };
    lua_pushlightuserdata(L, (void*)g_animModule.DefineAnimation(anim));

    return 1;
}

s32 ScriptModule::_getTicks(lua_State* L)
{
    if (!LuaExpect(L, "getTicks", 0))
        return -1;

    lua_pushinteger(L, SDL_GetTicks());

    return 1;
}

s32 ScriptModule::_stopGame(lua_State* L)
{
    if (!LuaExpect(L, "stopGame", 0))
        return -1;

    g_game.Stop();

    return 0;
}

s32 ScriptModule::_switchMission(lua_State* L)
{
    if (!LuaExpect(L, "switchMission", 2))
        return -1;

    g_game.ChangeState(new PlayState(lua_tostring(L, 1), (s32)lua_tointeger(L, 2)));

    return 0;
}

s32 ScriptModule::_restartMission(lua_State* L)
{
    if (!LuaExpect(L, "restartMission", 1))
        return -1;

    g_game.ChangeState(new PlayState(static_cast<PlayState*>(
        g_game.GetCurrentState())->GetScriptPath(), (s32)lua_tointeger(L, 1)));

    return 0;
}

s32 ScriptModule::_addEntity(lua_State* L)
{
    if (!LuaExpect(L, "addEntity", 5))
        return -1;

    // Init entity
    Entity* pEntity = new Entity();

    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                          GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width  = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) );
    s32 height = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pEntity->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().PushEntity(pEntity);

    // Return pointer to lua
    lua_pushlightuserdata(L, pEntity);

    return 1;
}

s32 ScriptModule::_removeEntity(lua_State* L)
{
    if (!LuaExpect(L, "removeEntity", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "removeEntity() called with null entity");
        return -1;
    }
    g_game.GetWorld().RemoveEntity(pEntity);

    return 0;
}

s32 ScriptModule::_updateEntity(lua_State* L)
{
    if (!LuaExpect(L, "updateEntity", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        pEntity->Update((f32)lua_tonumber(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "updateEntity(): function called with null entity");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_setEntityPosition(lua_State* L)
{
    if (!LuaExpect(L, "setEntityPosition", 3))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityPosition() called with null entity");
        return -1;
    }
    pEntity->m_vPosition = {
        GTU::UnitToScreenX((f32)lua_tonumber(L, 2)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 3))
    };

    return 0;
}

s32 ScriptModule::_getEntityPosition(lua_State* L)
{
    if (!LuaExpect(L, "getEntityPosition", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushnumber(L, GTU::ScreenToUnitX(pEntity->m_vPosition.x));
        lua_pushnumber(L, GTU::ScreenToUnitY(pEntity->m_vPosition.y));
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityPosition(): function called with null entity");
        lua_pushnumber(L, 0.0f);
        lua_pushnumber(L, 0.0f);
    }

    return 2;
}

s32 ScriptModule::_setEntityVelocity(lua_State* L)
{
    if (!LuaExpect(L, "setEntityVelocity", 3))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityVelocity() called with null entity");
        return -1;
    }
    pEntity->m_vVelocity = {
        GTU::UnitToScreenX((f32)lua_tonumber(L, 2)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 3))
    };

    return 0;
}

s32 ScriptModule::_getEntityVelocity(lua_State* L)
{
    if (!LuaExpect(L, "getEntityVelocity", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushnumber(L, GTU::ScreenToUnitX(pEntity->m_vVelocity.x));
        lua_pushnumber(L, GTU::ScreenToUnitY(pEntity->m_vVelocity.y));
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityVelocity(): function called with null entity");
        lua_pushnumber(L, 0.0f);
        lua_pushnumber(L, 0.0f);
    }

    return 2;
}

s32 ScriptModule::_setEntityHitBox(lua_State* L)
{
    if (!LuaExpect(L, "setEntityHitBox", 5))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityHitBox() called with null entity");
        return -1;
    }
    pEntity->m_hitBox = {
        GTU::UnitToScreenX((f32)lua_tonumber(L, 2)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 3)),
        GTU::UnitToScreenX((f32)lua_tonumber(L, 4)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 5)),
    };

    return 0;
}

s32 ScriptModule::_getEntityHitBox(lua_State* L)
{
    if (!LuaExpect(L, "getEntityHitBox", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "getEntityHitBox(): function called with null entity");
        return -1;
    }

    const FRect& hitBox = pEntity->m_hitBox;
    lua_pushnumber(L, GTU::ScreenToUnitX(hitBox.x1));
    lua_pushnumber(L, GTU::ScreenToUnitY(hitBox.y1));
    lua_pushnumber(L, GTU::ScreenToUnitX(hitBox.x2));
    lua_pushnumber(L, GTU::ScreenToUnitY(hitBox.y2));

    return 4;
}

s32 ScriptModule::_toggleEntityCollidable(lua_State* L)
{
    if (!LuaExpect(L, "toggleEntityCollidable", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "toggleEntityCollidable() called with null entity");
        return -1;
    }
    pEntity->m_bCollidable = (b32)lua_toboolean(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityCollidable(lua_State* L)
{
    if (!LuaExpect(L, "getEntityCollidable", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "getEntityCollidable(): function called with null entity");
        return -1;
    }
    lua_pushboolean(L, pEntity->m_bCollidable);

    return 1;
}

s32 ScriptModule::_setEntityAnimFrame(lua_State* L)
{
    if (!LuaExpect(L, "setEntityAnimFrame", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityAnimFrame(): function called with null entity");
        return -1;
    }
    pEntity->m_animFrame = (s32)lua_tointeger(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityAnimFrame(lua_State* L)
{
    if (!LuaExpect(L, "getEntityAnimFrame", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushinteger(L, pEntity->m_animFrame);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityAnimFrame(): function called with null entity");
        lua_pushinteger(L, 0);
    }

    return 1;
}

s32 ScriptModule::_setEntityAnimElapsed(lua_State* L)
{
    if (!LuaExpect(L, "setEntityAnimElapsed", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityAnimElapsed(): function called with null entity");
        return -1;
    }
    pEntity->m_animElapsed = (f32)lua_tonumber(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityAnimElapsed(lua_State* L)
{
    if (!LuaExpect(L, "getEntityAnimElapsed", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushnumber(L, pEntity->m_animElapsed);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityAnimElapsed(): function called with null entity");
        lua_pushnumber(L, 0);
    }

    return 1;
}

s32 ScriptModule::_setEntityAnim(lua_State* L)
{
    if (!LuaExpect(L, "setEntityAnim", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityAnim(): function called with null entity");
        return -1;
    }
    pEntity->m_pAnim = (const GT_Animation*)lua_touserdata(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityAnim(lua_State* L)
{
    if (!LuaExpect(L, "getEntityAnim", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushlightuserdata(L, (void*)pEntity->m_pAnim);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityAnim(): function called with null entity");
        lua_pushlightuserdata(L, nullptr);
    }

    return 1;
}

s32 ScriptModule::_setEntityRenderMode(lua_State* L)
{
    if (!LuaExpect(L, "setEntityRenderMode", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityRenderMode(): function called with null entity");
        return -1;
    }
    pEntity->m_renderMode = (s32)lua_tointeger(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityRenderMode(lua_State* L)
{
    if (!LuaExpect(L, "getEntityRenderMode", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushinteger(L, pEntity->m_renderMode);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityRenderMode(): function called with null entity");
        lua_pushinteger(L, RENDER_MODE_DYNAMIC);
    }

    return 1;
}

s32 ScriptModule::_setEntityZIndex(lua_State* L)
{
    if (!LuaExpect(L, "setEntityZIndex", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityZIndex(): function called with null entity");
        return -1;
    }
    pEntity->m_zIndex = (s32)lua_tointeger(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityZIndex(lua_State* L)
{
    if (!LuaExpect(L, "getEntityZIndex", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushinteger(L, pEntity->m_zIndex);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityZIndex(): function called with null entity");
        lua_pushinteger(L, 0);
    }

    return 1;
}

s32 ScriptModule::_toggleEntityHUD(lua_State* L)
{
    if (!LuaExpect(L, "toggleEntityHUD", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "toggleEntityHUD(): function called with null entity");
        return -1;
    }
    pEntity->m_bHUD = (b32)lua_toboolean(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityHUD(lua_State* L)
{
    if (!LuaExpect(L, "getEntityHUD", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushboolean(L, pEntity->m_bHUD);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityHUD(): function called with null entity");
        lua_pushboolean(L, false);
    }

    return 1;
}

s32 ScriptModule::_setEntityTexture(lua_State* L)
{
    if (!LuaExpect(L, "setEntityTexture", 2))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (!pEntity)
    {
        LuaNote(PR_WARNING, "setEntityTexture(): function called with null entity");
        return -1;
    }
    pEntity->m_pTexture = (const GT_Texture*)lua_touserdata(L, 2);

    return 0;
}

s32 ScriptModule::_getEntityTexture(lua_State* L)
{
    if (!LuaExpect(L, "getEntityTexture", 1))
        return -1;

    Entity* pEntity = (Entity*)lua_touserdata(L, 1);
    if (pEntity)
    {
        lua_pushlightuserdata(L, (void*)pEntity->m_pTexture);
    }
    else
    {
        LuaNote(PR_WARNING, "getEntityTexture(): function called with null entity");
        lua_pushlightuserdata(L, nullptr);
    }

    return 1;
}

s32 ScriptModule::_addActor(lua_State* L)
{
    if (!LuaExpect(L, "addActor", 5))
        return -1;

    // Init actor
    Actor* pActor = new Actor();

    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                          GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width  = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) );
    s32 height = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) );
    GT_Texture* pTexture = (GT_Texture*)lua_touserdata(L, 5);

    pActor->Init(vPosition, width, height, pTexture);

    // Push him to the world
    g_game.GetWorld().PushEntity(pActor);

    // Return pointer to lua
    lua_pushlightuserdata(L, pActor);

    return 1;
}

s32 ScriptModule::_setActorTeam(lua_State* L)
{
    if (!LuaExpect(L, "setActorTeam", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_actorTeam = (s32)lua_tointeger(L, 2);
    }
    else
    {
        LuaNote(PR_WARNING, "setActorTeam() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_getActorTeam(lua_State* L)
{
    if (!LuaExpect(L, "getActorTeam", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        lua_pushinteger(L, pActor->m_actorTeam);
    }
    else
    {
        lua_pushinteger(L, ACTOR_TEAM_DEFAULT);
        LuaNote(PR_WARNING, "getActorTeam() called with null actor");
    }

    return 1;
}

s32 ScriptModule::_setActorHealth(lua_State* L)
{
    if (!LuaExpect(L, "setActorHealth", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_health = (f32)lua_tonumber(L, 2);
    }
    else
    {
        LuaNote(PR_WARNING, "setActorHealth() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_getActorHealth(lua_State* L)
{
    if (!LuaExpect(L, "getActorHealth", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    f32 health;

    if (pActor)
    {
        health = pActor->m_health;
    }
    else
    {
        health = 0;
        LuaNote(PR_WARNING, "getActorHealth() called with null actor");
    }
    lua_pushnumber(L, health);

    return 1;
}

s32 ScriptModule::_isActorAlive(lua_State* L)
{
    if (!LuaExpect(L, "isActorAlive", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        lua_pushboolean(L, pActor->m_actorState != ACTOR_STATE_DEAD);
    }
    else
    {
        LuaNote(PR_WARNING, "isActorAlive() called with null actor");
        lua_pushboolean(L, false);
    }

    return 1;
}

s32 ScriptModule::_toggleActorGodMode(lua_State* L)
{
    if (!LuaExpect(L, "toggleActorGodMode", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_bGodMode = (b32)lua_toboolean(L, 2);
    }
    else
    {
        LuaNote(PR_WARNING, "toggleActorGodMode() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_isActorLookRight(lua_State* L)
{
    if (!LuaExpect(L, "isActorLookRight", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        lua_pushboolean(L, pActor->m_bLookRight);
    }
    else
    {
        LuaNote(PR_WARNING, "isActorLookRight() called with null actor");
        lua_pushboolean(L, true);
    }

    return 1;
}

s32 ScriptModule::_turnActorLeft(lua_State* L)
{
    if (!LuaExpect(L, "turnActorLeft", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_bLookRight = false;
    }
    else
    {
        LuaNote(PR_WARNING, "turnActorLeft() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_turnActorRight(lua_State* L)
{
    if (!LuaExpect(L, "turnActorRight", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_bLookRight = true;
    }
    else
    {
        LuaNote(PR_WARNING, "turnActorRight() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_setActorSpeed(lua_State* L)
{
    if (!LuaExpect(L, "setActorSpeed", 3))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_vSpeed = {
            GTU::UnitToScreenX((f32)lua_tonumber(L, 2)),
            GTU::UnitToScreenY((f32)lua_tonumber(L, 3)),
        };
    }
    else
    {
        LuaNote(PR_WARNING, "setActorSpeed() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_getActorSpeed(lua_State* L)
{
    if (!LuaExpect(L, "getActorSpeed", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        lua_pushnumber(L, GTU::ScreenToUnitX(pActor->m_vSpeed.x));
        lua_pushnumber(L, GTU::ScreenToUnitY(pActor->m_vSpeed.y));
    }
    else
    {
        LuaNote(PR_WARNING, "getActorSpeed() called with null actor");
        lua_pushnumber(L, 0.0f);
        lua_pushnumber(L, 0.0f);
    }

    return 2;
}

s32 ScriptModule::_setActorState(lua_State* L)
{
    if (!LuaExpect(L, "setActorState", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->SetState((GT_State*)lua_touserdata(L, 2));
    }
    else
    {
        LuaNote(PR_WARNING, "setActorState() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_pushActorTask(lua_State* L)
{
    if (lua_gettop(L) < 2)
    {
        LuaNote(PR_WARNING, "pushActorTask(): expected at least 2 arguments but %d given", lua_gettop(L));
        return -1;
    }

    // Check for erros
    Actor* pActor = (Actor*)lua_touserdata(L, 1);
    if (!pActor)
    {
        LuaNote(PR_WARNING, "pushActorTask() called with null actor");
        return -1;
    }

    // Set task
    switch (lua_tointeger(L, 2))
    {

    case GTT_NONE:
    {
        pActor->RemoveTasks();
    } break;

    case GTT_WAIT:
    {
        pActor->PushTask(new WaitTask(pActor, (f32)lua_tointeger(L, 3)));
    } break;

    case GTT_GOTO:
    {
        Vector2 vDestination = { GTU::UnitToScreenX((f32)lua_tonumber(L, 3)),
                                 GTU::UnitToScreenY((f32)lua_tonumber(L, 4))};
        pActor->PushTask(new GotoTask(pActor, vDestination));
    } break;

    case GTT_GOTO_ENTITY:
    {
        pActor->PushTask(new GotoEntityTask(pActor, (Entity*)lua_touserdata(L, 3)));
    } break;

    case GTT_KILL:
    {
        pActor->PushTask(new KillTask(pActor, (Actor*)lua_touserdata(L, 3)));
    } break;

    case GTT_ANIMATE_FOR:
    {
        pActor->PushTask(new AnimateForTask(pActor, (const GT_Animation*)lua_touserdata(L, 3), (f32)lua_tonumber(L, 4)));
    } break;

    case GTT_WAIT_ANIMATION:
    {
        pActor->PushTask(new WaitAnimationTask(pActor, (const GT_Animation*)lua_touserdata(L, 3)));
    } break;

    case GTT_WAIT_DIALOG:
    {
        pActor->PushTask(new WaitDialogTask(pActor, (Dialog*)lua_touserdata(L, 3)));
    } break;

    case GTT_RUN_DIALOG:
    {
        pActor->PushTask(new RunDialogTask(pActor, (Dialog*)lua_touserdata(L, 3)));
    } break;

    case GTT_FADE_IN:
    {
        pActor->PushTask(new FadeInTask(pActor, (f32)lua_tonumber(L, 3)));
    } break;

    case GTT_FADE_OFF:
    {
        pActor->PushTask(new FadeOffTask(pActor, (f32)lua_tonumber(L, 3)));
    } break;

    case GTT_PUSH_COMMAND:
    {
        pActor->PushTask(new PushCommandTask(pActor, (s32)lua_tointeger(L, 3)));
    } break;

    default:
    {
        LuaNote(PR_WARNING, "setActorTask(): undefined task given: %d", lua_tointeger(L, 2));
        return -1;
    } break;

    }

    return 0;
}

s32 ScriptModule::_pushActorCommand(lua_State* L)
{
    if (!LuaExpect(L, "pushActorCommand", 2))
        return -1;

    // Check for errors
    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (!pActor)
    {
        LuaNote(PR_WARNING, "pushActorCommand() called with null actor");
        return -1;
    }

    // Push command
    pActor->PushCommand((s32)lua_tointeger(L, 2));

    return 0;
}

s32 ScriptModule::_checkActorCurrentTask(lua_State* L)
{
    if (!LuaExpect(L, "checkActorCurrentTask", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        const GT_Task* pTask = pActor->GetCurrentTask();
        if (pTask)
            lua_pushinteger(L, pTask->GetStatus());
        else
            lua_pushinteger(L, GTT_NONE);
    }
    else
    {
        LuaNote(PR_WARNING, "checkActorCurrentTask() called with null actor");
        return -1;
    }

    return 1;
}

s32 ScriptModule::_getActorCurrentTask(lua_State* L)
{
    if (!LuaExpect(L, "getActorCurrentTask", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        const GT_Task* pTask = pActor->GetCurrentTask();
        if (pTask)
            lua_pushinteger(L, pTask->GetID());
        else
            lua_pushinteger(L, GTT_NONE);
    }
    else
    {
        LuaNote(PR_WARNING, "getActorCurrentTask() called with null actor");
        return -1;
    }

    return 1;
}

s32 ScriptModule::_setActorDeathSound(lua_State* L)
{
    if (!LuaExpect(L, "setActorDeathSound", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_pDeathSound = (GT_Sound*)lua_touserdata(L, 2);
    }
    else
    {
        LuaNote(PR_WARNING, "setActorDeathSound() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_setActorWeapon(lua_State* L)
{
    if (!LuaExpect(L, "setActorWeapon", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_pWeapon = (const Weapon*)lua_touserdata(L, 2);
    }
    else
    {
        LuaNote(PR_WARNING, "setActorWeapon() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_setActorAttackRate(lua_State* L)
{
    if (!LuaExpect(L, "setActorAttackRate", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_attackRate = (f32)lua_tonumber(L, 2);
    }
    else
    {
        LuaNote(PR_WARNING, "setActorAttackRate() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_getActorAttackRate(lua_State* L)
{
    if (!LuaExpect(L, "getActorAttackRate", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        lua_pushnumber(L, pActor->m_attackRate);
    }
    else
    {
        LuaNote(PR_WARNING, "getActorAttackRate() called with null actor");
        lua_pushnumber(L, 0.0f);
    }

    return 1;
}

s32 ScriptModule::_setActorAnim(lua_State* L)
{
    if (!LuaExpect(L, "setActorAnim", 3))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_aActorAnims[lua_tointeger(L, 2)] = (const GT_Animation*)lua_touserdata(L, 3);
    }
    else
    {
        LuaNote(PR_WARNING, "setActorAnim() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_playActorAnimOnce(lua_State* L)
{
    if (!LuaExpect(L, "playActorAnimOnce", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_pAnim = (const GT_Animation*)lua_touserdata(L, 2);
        pActor->m_animFrame = 0;
        pActor->m_animElapsed = 0.0f;
        pActor->m_actorState = ACTOR_STATE_ANIMATE_ONCE;
    }
    else
    {
        LuaNote(PR_WARNING, "playActorAnimOnce() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_playActorAnimLooped(lua_State* L)
{
    if (!LuaExpect(L, "playActorAnimLooped", 2))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_pAnim = (const GT_Animation*)lua_touserdata(L, 2);
        pActor->m_animFrame = 0;
        pActor->m_animElapsed = 0.0f;
        pActor->m_actorState = ACTOR_STATE_ANIMATE_LOOPED;
    }
    else
    {
        LuaNote(PR_WARNING, "playActorAnimLooped() called with null actor");
        return -1;
    }

    return 0;
}

s32 ScriptModule::_stopActorAnim(lua_State* L)
{
    if (!LuaExpect(L, "stopActorAnim", 1))
        return -1;

    Actor* pActor = static_cast<Actor*>(lua_touserdata(L, 1));
    if (pActor)
    {
        pActor->m_actorState = ACTOR_STATE_IDLE;
    }
    else
    {
        LuaNote(PR_WARNING, "stopActorAnim() called with null actor");
        return -1;
    }

    return 0;
}


s32 ScriptModule::_defineWeapon(lua_State* L)
{
    if (lua_gettop(L) < 5)
    {
        LuaNote(PR_ERROR, "defineWeapon(): expected at least 5 arguments");
        return -1;
    }
    else if (lua_gettop(L) != 5 + lua_tointeger(L, 2))
    {
        LuaNote(PR_ERROR, "defineWeapon(): expected 5 required + soundCount arguments");
        return -1;
    }

    // Init weapon
    const GT_Animation* pAnim = (const GT_Animation*)lua_touserdata(L, 1);
    s32 soundCount = (s32)lua_tointeger(L, 2);

    FRect hitBox;
    hitBox.x1 = -GTU::UnitToScreenX((f32)lua_tonumber(L, 3));
    hitBox.y1 = -GTU::UnitToScreenY((f32)lua_tonumber(L, 4));
    hitBox.x2 = -hitBox.x1;
    hitBox.y2 = -hitBox.y1;

    f32 damage = (f32)lua_tonumber(L, 5);

    // Allocate weapon
    Weapon* pWeapon = new Weapon(pAnim, soundCount, hitBox, damage);

    // Init weapon's soundpack
    GT_Sound** aSounds = pWeapon->GetSoundPack().GetSounds();

    for (i32f i = 0; i < soundCount; ++i)
        aSounds[i] = (GT_Sound*)lua_touserdata(L, i + 6);

    // Push to the world
    g_game.GetWorld().PushWeapon(pWeapon);
    // Return to script
    lua_pushlightuserdata(L, (void*)pWeapon);

    return 1;
}

s32 ScriptModule::_addCar(lua_State* L)
{
    if (!LuaExpect(L, "addCar", 5))
        return -1;

    // Init car
    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)), GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width = (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 3));
    s32 height = (s32)GTU::UnitToScreenY((f32)lua_tonumber(L, 4));
    const GT_Texture* pTexture = (const GT_Texture*)lua_touserdata(L, 5);

    Car* pCar = new Car();
    pCar->Init(vPosition, width, height, pTexture);

    // Push to the world and lua
    g_game.GetWorld().PushEntity(pCar);
    lua_pushlightuserdata(L, pCar);

    return 1;
}

s32 ScriptModule::_turnCarLeft(lua_State* L)
{
    if (!LuaExpect(L, "turnCarLeft", 1))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 1);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "turnCarLeft() called with null car");
        return -1;
    }
    pCar->m_flip = SDL_FLIP_HORIZONTAL;

    return 0;
}

s32 ScriptModule::_turnCarRight(lua_State* L)
{
    if (!LuaExpect(L, "turnCarRight", 1))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 1);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "turnCarRight() called with null car");
        return -1;
    }
    pCar->m_flip = SDL_FLIP_NONE;

    return 0;
}

s32 ScriptModule::_setCarMaxSpeed(lua_State* L)
{
    if (!LuaExpect(L, "setCarMaxSpeed", 3))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 1);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "setCarMaxSpeed() called with null car");
        return -1;
    }
    pCar->m_vMaxSpeed = {
        GTU::UnitToScreenX((f32)lua_tonumber(L, 2)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 3))
    };

    return 0;
}

s32 ScriptModule::_setCarAcceleration(lua_State* L)
{
    if (!LuaExpect(L, "setCarAcceleration", 3))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 1);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "setCarAcceleration() called with null car");
        return -1;
    }
    pCar->m_vAcceleration = {
        GTU::UnitToScreenX((f32)lua_tonumber(L, 2)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 3))
    };

    return 0;
}

s32 ScriptModule::_setCarPlacePosition(lua_State* L)
{
    if (!LuaExpect(L, "setCarPlacePosition", 4))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 1);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "setCarPlacePosition() called with null car");
        return -1;
    }
    pCar->m_aPlacePositions[lua_tointeger(L, 2)] = {
        GTU::UnitToScreenX((f32)lua_tonumber(L, 3)),
        GTU::UnitToScreenY((f32)lua_tonumber(L, 4))
    };

    return 0;
}

s32 ScriptModule::_putActorInCar(lua_State* L)
{
    if (!LuaExpect(L, "putActorInCar", 3))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 2);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "putActorInCar() called with null car");
        return -1;
    }
    pCar->PutActor((Actor*)lua_touserdata(L, 1), (s32)lua_tointeger(L, 3));

    return 0;
}

s32 ScriptModule::_ejectActorFromCar(lua_State* L)
{
    if (!LuaExpect(L, "ejectActorFromCar", 2))
        return -1;

    Car* pCar = (Car*)lua_touserdata(L, 1);
    if (!pCar)
    {
        LuaNote(PR_WARNING, "ejectActorInCar() called with null car");
        return -1;
    }
    pCar->EjectActor((s32)lua_tointeger(L, 2));

    return 0;
}

s32 ScriptModule::_addTrigger(lua_State* L)
{
    if (!LuaExpect(L, "addTrigger", 6))
        return -1;

    // Allocate trigger
    Trigger* pTrigger = new Trigger();

    // Init trigger
    Vector2 vPosition = { GTU::UnitToScreenX((f32)lua_tonumber(L, 1)),
                          GTU::UnitToScreenY((f32)lua_tonumber(L, 2)) };
    s32 width  = (s32)( GTU::UnitToScreenX((f32)lua_tonumber(L, 3)) );
    s32 height = (s32)( GTU::UnitToScreenY((f32)lua_tonumber(L, 4)) );

    pTrigger->Init(vPosition, width, height, nullptr);
    pTrigger->Attach((Entity*)lua_touserdata(L, 5));
    pTrigger->SetFunctionName(lua_tostring(L, 6));

    // Push entity to the world and lua
    g_game.GetWorld().PushEntity(pTrigger);
    lua_pushlightuserdata(L, (void*)pTrigger);

    return 1;
}

s32 ScriptModule::_addDialog(lua_State* L)
{
    if (!LuaExpect(L, "addDialog", 6))
        return -1;

    // Params
    s32 width = (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 1));
    s32 height = (s32)GTU::UnitToScreenX((f32)lua_tonumber(L, 2));
    const char* text = lua_tostring(L, 3);
    f32 time = (f32)lua_tonumber(L, 4) * 1000.0f;
    Actor* pActor = (Actor*)lua_touserdata(L, 5);
    const GT_Texture* pTexture = (const GT_Texture*)lua_touserdata(L, 6);

    // Allocate and init dialog
    Dialog* pDialog = new Dialog();
    pDialog->Init(Vector2(0.0f, 0.0f), width, height, pTexture);
    pDialog->Attach(pActor);
    pDialog->SetTime(time);
    pDialog->SetText(text);

    // Push dialog to world and lua
    g_game.GetWorld().PushEntity(pDialog);
    lua_pushlightuserdata(L, (void*)pDialog);

    return 1;
}

s32 ScriptModule::_runDialog(lua_State* L)
{
    if (!LuaExpect(L, "runDialog", 1))
        return -1;

    Dialog* pDialog = (Dialog*)lua_touserdata(L, 1);
    if (!pDialog)
    {
        LuaNote(PR_WARNING, "runDialog() called with null dialog");
        return -1;
    }
    pDialog->Run();

    return 0;
}

s32 ScriptModule::_attachDialog(lua_State* L)
{
    if (!LuaExpect(L, "attachDialog", 2))
        return -1;

    Dialog* pDialog = (Dialog*)lua_touserdata(L, 1);
    if (!pDialog)
    {
        LuaNote(PR_WARNING, "attachDialog() called with null dialog");
        return -1;
    }
    pDialog->m_pAttached = (Actor*)lua_touserdata(L, 2);

    return 0;
}

s32 ScriptModule::_setDialogTime(lua_State* L)
{
    if (!LuaExpect(L, "setDialogTime", 2))
        return -1;

    Dialog* pDialog = (Dialog*)lua_touserdata(L, 1);
    if (!pDialog)
    {
        LuaNote(PR_WARNING, "setDialogTime() called with null dialog");
        return -1;
    }
    pDialog->m_time = (f32)lua_tonumber(L, 2);

    return 0;
}

s32 ScriptModule::_setDialogText(lua_State* L)
{
    if (!LuaExpect(L, "setDialogText", 2))
        return -1;

    Dialog* pDialog = (Dialog*)lua_touserdata(L, 1);
    if (!pDialog)
    {
        LuaNote(PR_WARNING, "setDialogText() called with null dialog");
        return -1;
    }
    pDialog->SetText(lua_tostring(L, 2));

    return 0;
}
