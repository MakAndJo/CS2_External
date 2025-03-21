#include "Entity.h"

bool CEntity::UpdateController(const DWORD64& PlayerControllerAddress)
{
	if (PlayerControllerAddress == 0) {
		//std::cout << "[DEBUG] Player controller address is null." << std::endl;
		return false;
	}
	this->Controller.Address = PlayerControllerAddress;

	if (!this->Controller.GetHealth()) {
		std::cout << "[DEBUG] Controller -> Unable to get health." << std::endl;
		return false;
	}
	if (!this->Controller.GetIsAlive()) {
		std::cout << "[DEBUG] Controller -> Unable to get isAlive." << std::endl;
		return false;
	}
	/*if (!this->Controller.GetTeamID())
		return false;*/
	if (!this->Controller.GetPlayerName()) {
		std::cout << "[DEBUG] Controller -> Unable to get playerName." << std::endl;
		return false;
	}

	this->Pawn.Address = this->Controller.GetPlayerPawnAddress();

	return true;
}

bool CEntity::UpdatePawn(const DWORD64& PlayerPawnAddress)
{
	if (PlayerPawnAddress == 0)
		return false;
	this->Pawn.Address = PlayerPawnAddress;

	if (!this->Pawn.GetCameraPos()) {
		std::cout << "[DEBUG] Pawn -> Unable to get cam pos." << std::endl;
		return false;
	}
	if (!this->Pawn.GetPos()) {
		std::cout << "[DEBUG] Pawn -> Unable to get pos." << std::endl;
		return false;
	}
	if (!this->Pawn.GetViewAngle()) {
		std::cout << "[DEBUG] Pawn -> Unable to get view angle." << std::endl;
		return false;
	}
	if (!this->Pawn.GetWeaponName()) {
		std::cout << "[DEBUG] Pawn -> Unable to get wpn." << std::endl;
		return false;
	}
	if (!this->Pawn.GetAimPunchAngle()) {
		std::cout << "[DEBUG] Pawn -> Unable to get pch_ang." << std::endl;
		return false;
	}
	if (!this->Pawn.GetShotsFired()) {
		std::cout << "[DEBUG] Pawn -> Unable to get sht_fr." << std::endl;
		return false;
	}
	if (!this->Pawn.GetHealth()) {
		std::cout << "[DEBUG] Pawn -> Unable to get htls." << std::endl;
		return false;
	}
	if (!this->Pawn.GetFov()) {
		std::cout << "[DEBUG] Pawn -> Unable to get fov." << std::endl;
		return false;
	}
	if (!this->Pawn.GetSpotted()) {
		std::cout << "[DEBUG] Pawn -> Unable to get spotted." << std::endl;
		return false;
	}
	if (!this->Pawn.GetFFlags()) {
		std::cout << "[DEBUG] Pawn -> Unable to get fflags." << std::endl;
		return false;
	}
	if (!this->Pawn.GetAimPunchCache()) {
		std::cout << "[DEBUG] Pawn -> Unable to get aim puch cah." << std::endl;
		return false;
	}
	if (!this->Pawn.BoneData.UpdateAllBoneData(PlayerPawnAddress)) {
		//std::cout << "[DEBUG] Pawn -> Unable to get bon data." << std::endl;
		return false;
	}

	return true;
}

bool PlayerController::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Entity.Health, this->Health);
}

bool PlayerController::GetIsAlive()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Entity.IsAlive, this->AliveStatus);
}

bool PlayerController::GetPlayerName()
{
	char Buffer[MAX_PATH]{};

	if (!ProcessMgr.ReadMemory(Address + Offset::Entity.iszPlayerName, Buffer, MAX_PATH))
		return false;

	this->PlayerName = Buffer;
	if (this->PlayerName.empty())
		this->PlayerName = "Name_None";

	return true;
}

bool PlayerPawn::GetViewAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::Pawn.angEyeAngles, this->ViewAngle);
}

bool PlayerPawn::GetCameraPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset::Pawn.vecLastClipCameraPos, this->CameraPos);
}

bool PlayerPawn::GetSpotted()
{
	return GetDataAddressWithOffset<DWORD64>(Address, Offset::Pawn.bSpottedByMask, this->bSpottedByMask);
}

bool PlayerPawn::GetWeaponName()
{
	DWORD64 WeaponNameAddress = 0;
	char Buffer[40]{};
	
	WeaponNameAddress = ProcessMgr.TraceAddress(this->Address + Offset::Pawn.pClippingWeapon, { 0x10,0x20 ,0x0 });
	if (WeaponNameAddress == 0)
		return false;

	if (!ProcessMgr.ReadMemory(WeaponNameAddress, Buffer, 40))
		return false;

	WeaponName = std::string(Buffer);
	std::size_t Index = WeaponName.find("_");
	if (Index == std::string::npos || WeaponName.empty())
	{
		WeaponName = "Weapon_None";
	}
	else
	{
		WeaponName = WeaponName.substr(Index + 1, WeaponName.size() - Index - 1);
	}

	return true;
}

bool PlayerPawn::GetShotsFired()
{
	return GetDataAddressWithOffset<DWORD>(Address, Offset::Pawn.iShotsFired, this->ShotsFired);
}

bool PlayerPawn::GetAimPunchAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::Pawn.aimPunchAngle, this->AimPunchAngle);
}

bool PlayerPawn::GetAimPunchCache()
{
	return GetDataAddressWithOffset<C_UTL_VECTOR>(Address, Offset::Pawn.aimPunchCache, this->AimPunchCache);
}

DWORD64 PlayerController::GetPlayerPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset::Entity.PlayerPawn, this->Pawn))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}

bool PlayerPawn::GetPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset::Pawn.Pos, this->Pos);
}

bool PlayerPawn::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Pawn.CurrentHealth, this->Health);
}

bool PlayerPawn::GetFov()
{
	DWORD64 CameraServices = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(Address + Offset::Pawn.CameraServices, CameraServices))
		return false;
	return GetDataAddressWithOffset<int>(CameraServices, Offset::Pawn.iFovStart, this->Fov);
}

bool PlayerPawn::GetFFlags()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Pawn.fFlags, this->fFlags);
}

bool CEntity::IsAlive()
{
	return this->Controller.AliveStatus == 1 && this->Pawn.Health > 0;
}

bool CEntity::IsInScreen()
{
	return gGame.View.WorldToScreen(this->Pawn.Pos, this->Pawn.ScreenPos);
}

CBone CEntity::GetBone() const
{
	if (this->Pawn.Address == 0)
		return CBone{};
	return this->Pawn.BoneData;
}
