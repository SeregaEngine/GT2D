/* ====== INCLUDES ====== */
#include "ScriptModule.h"

/* ====== VARIABLES ====== */
ScriptModule g_scriptModule;

/* ====== METHODS ====== */
b32 ScriptModule::StartUp()
{
    AddNote(PR_NOTE, "Module started");

    return true;
}

void ScriptModule::ShutDown()
{
    AddNote(PR_NOTE, "Module shut down");
}