#pragma once
extern PVOID boatPawns;
extern PVOID TargetBoat;
namespace CheatManipulation
{
	namespace Details
	{

		cActor* ClosestHoagie = nullptr;
		cActor* ClosestBoat = nullptr;
		cActor* ClosestPlayer = nullptr;
	}

	bool HoagieExploits();

	bool BoatExploits();
	void NoSpread();
	void GliderHax();
	void NoReload();
	void RapidFire();
	void ResetFirstPerson();
	void SetFirstPerson();
	void InvisiblePlayer();
	void PlayerTeleport();
}
#define PointRed(base, offset) (*(PVOID *)(((PBYTE)base + offset)))
PVOID LocalPlayerPawn = nullptr;
DWORD CurrentWeapon = 0x05A0;
VOID(*ReloadOriginal)(PVOID, PVOID) = nullptr;
float Norm = 0.0f;
PVOID(*GetWeaponStats)(PVOID) = nullptr;

bool CheatManipulation::HoagieExploits()
{
	if (!Details::ClosestHoagie) return false;
	if (!Details::ClosestHoagie->SceneComponent) return false;
	if (!Details::ClosestHoagie->HoagieVehicleConfigs) return false;

	if (Settings::Menu::Other_HoagieBooster)
	{
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostCooldown = 0.0f;
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostDuration = 1.0f;
	}
	else
	{
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostCooldown = 5.0f;
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostDuration = 0.5f;
	}

	if (Settings::Menu::Other_HoagieSpeed)
	{
		Details::ClosestHoagie->HoagieVehicleConfigs->StrafeForce = (2650 * Settings::Menu::Other_HoagieSpeedMultiplier);
		Details::ClosestHoagie->HoagieVehicleConfigs->MaxStrafeSpeedKmh = (70 * Settings::Menu::Other_HoagieSpeedMultiplier); 
		Details::ClosestHoagie->HoagieVehicleConfigs->LiftForce = (1500 * Settings::Menu::Other_HoagieSpeedMultiplier); 
		Details::ClosestHoagie->HoagieVehicleConfigs->MaxLiftSpeedKmh = (35 * Settings::Menu::Other_HoagieSpeedMultiplier); 
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostForce = (15000 * Settings::Menu::Other_HoagieSpeedMultiplier);
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostMaxSpeedKmh = (150 * Settings::Menu::Other_HoagieSpeedMultiplier);
	}
	else
	{
		Details::ClosestHoagie->HoagieVehicleConfigs->StrafeForce = 2650;
		Details::ClosestHoagie->HoagieVehicleConfigs->MaxStrafeSpeedKmh = 70;
		Details::ClosestHoagie->HoagieVehicleConfigs->LiftForce = 1500;
		Details::ClosestHoagie->HoagieVehicleConfigs->MaxLiftSpeedKmh = 35;
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostForce = 15000;
		Details::ClosestHoagie->HoagieVehicleConfigs->BoostMaxSpeedKmh = 150;
	}

	return true;
}

bool CheatManipulation::BoatExploits()
{
	if (!Details::ClosestBoat) return false;
	if (!Details::ClosestBoat->SceneComponent) return false;
	if (!Details::ClosestBoat->MeatballVehicleConfigs) return false;

	if (Settings::Menu::Other_BoatSpeed)
	{
		Details::ClosestBoat->MeatballVehicleConfigs->BoostMinPushForce = (1200.0f * Settings::Menu::Other_BoatSpeedMultiplier);
		Details::ClosestBoat->MeatballVehicleConfigs->BoostTopSpeedForceMultiplier = (1.3f * Settings::Menu::Other_BoatSpeedMultiplier);
		Details::ClosestBoat->MeatballVehicleConfigs->BoostTopSpeedMultiplier = (1.3f * Settings::Menu::Other_BoatSpeedMultiplier);
		Details::ClosestBoat->MeatballVehicleConfigs->LandTopSpeedMultiplier = (1.0f * Settings::Menu::Other_BoatSpeedMultiplier);
		Details::ClosestBoat->MeatballVehicleConfigs->LandPushForceMultiplier = (3.0f * Settings::Menu::Other_BoatSpeedMultiplier);
		Details::ClosestBoat->MeatballVehicleConfigs->BoostSteeringMultiplier = 1.0f;
		Details::ClosestBoat->MeatballVehicleConfigs->LandSteeringMultiplier = 1.0f;
		Details::ClosestBoat->MeatballVehicleConfigs->LandMinSpeedSteeringAngle = 180.0f;
		Details::ClosestBoat->MeatballVehicleConfigs->LandMaxSpeedSteeringAngle = 180.0f;
	}
	else
	{
		Details::ClosestBoat->MeatballVehicleConfigs->BoostMinPushForce = 1200;
		Details::ClosestBoat->MeatballVehicleConfigs->BoostTopSpeedForceMultiplier = 1.29;
		Details::ClosestBoat->MeatballVehicleConfigs->BoostTopSpeedMultiplier = 1.29;
		Details::ClosestBoat->MeatballVehicleConfigs->LandTopSpeedMultiplier = 0.1;
		Details::ClosestBoat->MeatballVehicleConfigs->LandPushForceMultiplier = 3;
		Details::ClosestBoat->MeatballVehicleConfigs->BoostSteeringMultiplier = 0.2;
		Details::ClosestBoat->MeatballVehicleConfigs->LandSteeringMultiplier = 1;
		Details::ClosestBoat->MeatballVehicleConfigs->LandMinSpeedSteeringAngle = 180;
		Details::ClosestBoat->MeatballVehicleConfigs->LandMaxSpeedSteeringAngle = 25;
	}


	if (Settings::Menu::Other_BoatTeleport && DiscordHelper::GetAsyncKeyState(VK_F7))
	{
		if (!Hook_ProcessEvent::Details::bIsHooked) return false;
		if (!Details::ClosestPlayer) return false;
		if (!Details::ClosestPlayer->SceneComponent) return false;

		Vector3 vTeleportPos = Details::ClosestPlayer->SceneComponent->RelativeLocation;
		vTeleportPos.z += 50.0f;

		SpoofCall(Hook_ProcessEvent::HkProcessEvent, (PVOID)Details::ClosestBoat, (PVOID)Settings::BaseOffsets::LaunchCharacter, (PVOID)&vTeleportPos, (PVOID)0);
	}


	return true;
}

void CheatManipulation::PlayerTeleport()
{
	if (!Settings::Menu::Other_PlayerTP) return;
	if (!EngineHelper::Instance::LocalController) return;
	if (!Settings::Local::LocalPawn) return;
	if (!CheatManipulation::Details::ClosestPlayer) return;
	if (!CheatManipulation::Details::ClosestPlayer->SceneComponent) return;
	if (!DiscordHelper::GetAsyncKeyState(VK_SHIFT)) return;

	FRotator vLocalRotation;

	Vector3 vTeleportPos = Details::ClosestPlayer->SceneComponent->RelativeLocation;
	vTeleportPos.x -= 8.00;
	//vTeleportPos.y += 8.00;
	vTeleportPos.z += 19.00;
	SpoofCall(Hook_ProcessEvent::HkProcessEvent, (PVOID)Settings::Local::LocalPawn, (PVOID)Settings::BaseOffsets::teleport, (PVOID)&vTeleportPos, (PVOID)&vLocalRotation);
}

static void Rapid(float time)
{
	uint64_t CurrentWeapon = 0;
	float i = 0;
	uint32_t LastFireTime_Offs = 0x08A4;
	uint32_t CurrentWeapon_Offs = 0x05A0;

	if (!Settings::Local::LocalPawn)
	{
		return;
	}

	CurrentWeapon = *(uint64_t*)(Settings::Local::LocalPawn + CurrentWeapon_Offs);

	if (!CurrentWeapon)
	{
		return;
	}

	i = *(float*)(CurrentWeapon + LastFireTime_Offs);

	*(float*)(CurrentWeapon + LastFireTime_Offs) = i - time;

	return;
}

static void set_last_first_shot_accuracy(float time)
{
	uint8_t curweap = 0;
	uint64_t v10 = 0;
	int v11;
	int v25;

	if (!Settings::Local::LocalPawn) return;

	curweap = *(uint8_t*)((uintptr_t)Settings::Local::LocalPawn + 0x5A0);
	if (curweap) return;

	v10 = *(uint64_t*)(curweap + 0xE6E);
	if (!v10) printf("\nv10 is incorrect."); return;

	v11 = *(int*)(curweap + 0xE6F);
	if (!v11) printf("\nv11 is incorrect.");  return;

	v25 = v11 ^ curweap + ((4 * v10) + 0xE5E);
	if (!v25) printf("\nv25 is incorrect."); return;

	*(float*)v25 = time;
}

/*
static void InstantReload(float ReloadTime)
{
	if (Norm != ReloadTime)
	{
		auto localPlayerWeapon = PointRed(LocalPlayerPawn, CurrentWeapon);
		if (localPlayerWeapon) {
			auto stats = GetWeaponStats(localPlayerWeapon);
			if (stats) {
				*reinterpret_cast<float*>(reinterpret_cast<PBYTE>(stats) + Settings::Local::LocalPawn->ReloadTime) = Norm;
				Norm = ReloadTime;
			}
		}
	}
}


void CheatManipulation::NoReload()
{
	if (Settings::Menu::InstantReload) return;

	InstantReload(0.0);
}

*/

void ClientSetCameraMode(PVOID PlayerController, char bNewCamMode)
{
	uintptr_t vTable = *(uintptr_t*)PlayerController;
	if (!vTable) return;

	uintptr_t func = *(uintptr_t*)(vTable + 0x900);
	if (!func) return;

	auto ClientSetCameraMode = reinterpret_cast<void(__fastcall*)(uintptr_t PlayerController, char bNewCamMode)>(func);

	SpoofCall(ClientSetCameraMode, (uintptr_t)PlayerController, (char)bNewCamMode);
}

void set_current_spread(float spread)
{
	uint8_t curweap = 0;
	uint64_t v10 = 0;
	int v11;
	int v25;

	if (!Settings::Local::LocalPawn) return;

	curweap = *(uint8_t*)((uintptr_t)Settings::Local::LocalPawn + 0x5A0);
	if (curweap) return;

	v10 = *(uint64_t*)(curweap + 0xE6E);
	if (!v10) printf("\nv10 is incorrect."); return;

	v11 = *(int*)(curweap + 0xE6F);
	if (!v11) printf("\nv11 is incorrect.");  return;

	v25 = v11 ^ curweap + ((4 * v10) + 0xE5E);
	if (!v25) printf("\nv25 is incorrect."); return;

	*(float*)v25 = spread;
}

void CheatManipulation::NoSpread()
{
	if (Settings::Menu::NoSpread) return;
	{
	set_last_first_shot_accuracy(0.0);
	}
}

void CheatManipulation::SetFirstPerson()
{
	if (Settings::Menu::FirstPerson) return;

	ClientSetCameraMode(EngineHelper::Instance::UWorld->GameInstance->LocalPlayers[0]->PlayerController, 1);
}