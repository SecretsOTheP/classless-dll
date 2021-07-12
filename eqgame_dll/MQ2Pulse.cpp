/*****************************************************************************
MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
******************************************************************************/
#if !defined(CINTERFACE)
//#error /DCINTERFACE
#endif

#define DBG_SPEW

//#define DEBUG_TRY 1
#include "MQ2Main.h"
#include "FloatingTextManager.h"
extern FloatingTextManager* g_pFtm;
BOOL TurnNotDone=FALSE;

void Heartbeat()
{
    int GameState=GetGameState();
    if (GameState!=-1)
    {
        if ((DWORD)GameState!=gGameState)
        {
			SetMapGameState(GameState);
#ifdef DPSPLUGIN
			SetEdgeDPSGameState(GameState);
#endif
            gGameState=GameState;
        }
    }
    UpdateMQ2SpawnSort();
}

bool isFtmPluginInit = false;
bool addedTestText = false;
extern IDirect3DDevice9* g_pDevice;
#ifndef ISXEQ_LEGACY
// *************************************************************************** 
// Function:    ProcessGameEvents 
// Description: Our ProcessGameEvents Hook
// *************************************************************************** 
BOOL Trampoline_ProcessGameEvents(VOID); 
BOOL Detour_ProcessGameEvents(VOID) 
{ 
	if(!isFtmPluginInit)
		InitializeFloatingTextPlugin();

    Heartbeat();
#ifdef ISXEQ
    if (!pISInterface->ScriptEngineActive()) 
        pISInterface->LavishScriptPulse();
#endif
    return Trampoline_ProcessGameEvents();
}

DETOUR_TRAMPOLINE_EMPTY(BOOL Trampoline_ProcessGameEvents(VOID)); 
class CEverQuestHook {
public:
    VOID EnterZone_Trampoline(PVOID pVoid);
    VOID EnterZone_Detour(PVOID pVoid)
    {
        EnterZone_Trampoline(pVoid);
        gZoning = TRUE;
        WereWeZoning = TRUE;
    }

    VOID SetGameState_Trampoline(DWORD GameState);
    VOID SetGameState_Detour(DWORD GameState)
    {
//        DebugSpew("SetGameState_Detour(%d)",GameState);

		SetMapGameState(GameState);
#ifdef DPSPLUGIN
		SetEdgeDPSGameState(GameState);
#endif
        SetGameState_Trampoline(GameState);
    }
};

DETOUR_TRAMPOLINE_EMPTY(VOID CEverQuestHook::EnterZone_Trampoline(PVOID));
DETOUR_TRAMPOLINE_EMPTY(VOID CEverQuestHook::SetGameState_Trampoline(DWORD));

void InitializeMQ2Pulse()
{
    EzDetour(ProcessGameEvents,Detour_ProcessGameEvents,Trampoline_ProcessGameEvents);
    EzDetour(CEverQuest__EnterZone,&CEverQuestHook::EnterZone_Detour,&CEverQuestHook::EnterZone_Trampoline);
    EzDetour(CEverQuest__SetGameState,&CEverQuestHook::SetGameState_Detour,&CEverQuestHook::SetGameState_Trampoline);
}

void ShutdownMQ2Pulse()
{
    RemoveDetour((DWORD)ProcessGameEvents);
    RemoveDetour(CEverQuest__EnterZone);
    RemoveDetour(CEverQuest__SetGameState);
}
#endif
