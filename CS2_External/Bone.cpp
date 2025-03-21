#include "Bone.h"

bool CBone::UpdateAllBoneData(const DWORD64& EntityPawnAddress)
{
	if (EntityPawnAddress == 0) {
		std::cout << "[DEBUG] Bone -> PawnAddress is null." << std::endl;
		return false;
	}
	this->EntityPawnAddress = EntityPawnAddress;

	DWORD64 GameSceneNode = 0;
	DWORD64 BoneArrayAddress = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnAddress + Offset::Pawn.GameSceneNode, GameSceneNode)) {
		std::cout << "[DEBUG] Bone -> GameSceneNode unreadable." << std::endl;
		return false;
	}
	if (!ProcessMgr.ReadMemory<DWORD64>(GameSceneNode + Offset::Pawn.BoneArray, BoneArrayAddress)) {
		std::cout << "[DEBUG] Bone -> BoneArray unreadable." << std::endl;
		return false;
	}

	BoneJointData BoneArray[30]{};
	if (!ProcessMgr.ReadMemory(BoneArrayAddress, BoneArray, 30 * sizeof(BoneJointData))) {
		std::cout << "[DEBUG] Bone -> BoneArray unreadable." << BoneArrayAddress << std::endl;
		return false;
	}

	for (int i = 0; i < 30; i++)
	{
		Vec2 ScreenPos;
		bool IsVisible = false;

		if (gGame.View.WorldToScreen(BoneArray[i].Pos, ScreenPos))
			IsVisible = true;

		this->BonePosList.push_back({ BoneArray[i].Pos ,ScreenPos,IsVisible });
	}

	return this->BonePosList.size() > 0;
}