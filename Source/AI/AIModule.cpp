/* ====== INCLUDES ====== */
#include "ScriptModule.h"
#include "Actor.h"
#include "Game.h"

#include "AIModule.h"

/* ====== VARIABLES ====== */
AIModule g_AIModule;

/* ====== METHODS ====== */
b32 AIModule::StartUp()
{
    AddNote(PR_NOTE, "Module start up");

    return true;
}

void AIModule::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}

void AIModule::HandleState(Actor* pActor)
{
    const char* functionName = pActor->GetState().functionName;

    if (functionName[0])
        g_scriptModule.CallState(g_game.GetScript(), functionName, pActor);
}
