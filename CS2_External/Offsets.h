#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"
#include "a2x/offsets.hpp"
#include "a2x/client_dll.hpp"
#include "a2x/buttons.hpp"

// From: https://github.com/a2x/cs2-dumper/blob/main/generated/client.dll.hpp
namespace Offset
{
	inline DWORD EntityList = cs2_dumper::offsets::client_dll::dwEntityList; // ok
	inline DWORD Matrix = cs2_dumper::offsets::client_dll::dwViewMatrix; // ok
	inline DWORD ViewAngle = cs2_dumper::offsets::client_dll::dwViewAngles; // ok
	inline DWORD LocalPlayerController = cs2_dumper::offsets::client_dll::dwLocalPlayerController; // ok
	inline DWORD LocalPlayerPawn = cs2_dumper::offsets::client_dll::dwLocalPlayerPawn; // ok
	inline DWORD GlobalVars = cs2_dumper::offsets::client_dll::dwGlobalVars; // ok

	struct
	{
		DWORD Health = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth; // ok
		//DWORD TeamID = 0x3BF;
		DWORD IsAlive = cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive;
		DWORD PlayerPawn = cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn;
		DWORD iszPlayerName = cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName;
	}Entity;

	struct
	{ // CBaseEntity, CSPlayerPawnBase
		DWORD CameraServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pCameraServices;

		DWORD Pos = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin; // C_BasePlayerPawn::m_vOldOrigin // ok
		DWORD MaxHealth = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iMaxHealth; // C_BaseEntity::m_iMaxHealth
		DWORD CurrentHealth = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth; // C_BaseEntity::m_iHealth
		DWORD GameSceneNode = cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode; // C_BaseEntity::m_pGameSceneNode
		DWORD BoneArray = cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + cs2_dumper::schemas::client_dll::CGameSceneNode::m_vecOrigin; // CSkeletonInstance_::m_modelState + CGameSceneNode_::m_vecOrigin
		DWORD angEyeAngles = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_angEyeAngles;
		DWORD vecLastClipCameraPos = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_vecLastClipCameraPos;
		DWORD pClippingWeapon = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon;			// C_CSWeaponBase*
		DWORD iShotsFired = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iShotsFired;
		DWORD flFlashDuration = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_flFlashDuration;
		DWORD aimPunchAngle = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchAngle;			// C_CSPlayerPawn::m_aimPunchAngle
		DWORD aimPunchCache = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchCache;
		DWORD iIDEntIndex = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex;
		DWORD iTeamNum = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum;
		DWORD iFovStart = cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOVStart;
		DWORD fFlags = cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags;
		DWORD bSpottedByMask = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpottedByMask;	// C_CSPlayerPawn::entitySpottedState + EntitySpottedState_t::bSpottedByMask
	}Pawn;

	struct
	{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x2C;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} GlobalVar;

	namespace Signatures
	{

	}

	bool UpdateOffsets();
}
