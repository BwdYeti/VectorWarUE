// Copyright 2020 BwdYeti.

#include "GameStateInterface.h"
#include "vectorwar.h"
#include "VWGameStateBase.h"

const GameState GetGameState(const AVWGameStateBase* VWGameState)
{
	if (VWGameState != nullptr)
		return VWGameState->GetGameState();

	return GameState{ 0 };
}
const NonGameState GetNonGameState(const AVWGameStateBase* VWGameState)
{
	if (VWGameState != nullptr)
		return VWGameState->GetNonGameState();

	return NonGameState{ 0 };
}

int32 UGameStateInterface::ShipCount(const AVWGameStateBase* VWGameState)
{
	return GetGameState(VWGameState)._num_ships;
}

int32 UGameStateInterface::BulletCount(const AVWGameStateBase* VWGameState)
{
	return ShipCount(VWGameState) * MAX_BULLETS;
}

FTransform UGameStateInterface::ShipTransform(const AVWGameStateBase* VWGameState, int32 Index)
{
	const Ship Ship = GetGameState(VWGameState)._ships[Index];
	FVector Position = FVector((float)Ship.position.x, (float)Ship.position.y, 0);
	FQuat Rotation = FRotator(0, Ship.heading - 90, 0).Quaternion();
	FTransform Result = FTransform(Rotation, Position);
	return Result;
}

int32 UGameStateInterface::ShipScore(const AVWGameStateBase* VWGameState, int32 Index)
{
	const Ship Ship = GetGameState(VWGameState)._ships[Index];
	return Ship.score;
}

bool UGameStateInterface::BulletEnabled(const AVWGameStateBase* VWGameState, int32 Index)
{
	const Bullet Bullet = GetBullet(VWGameState, Index);
	return Bullet.active;
}

FTransform UGameStateInterface::BulletTransform(const AVWGameStateBase* VWGameState, int32 Index)
{
	const Bullet Bullet = GetBullet(VWGameState, Index);
	FVector Position = FVector((float)Bullet.position.x, (float)Bullet.position.y, 0);
	FQuat Rotation = FQuat::Identity;
	FTransform Result = FTransform(Rotation, Position);
	return Result;
}

Bullet UGameStateInterface::GetBullet(const AVWGameStateBase* VWGameState, int32 Index)
{
	const Ship Ship = GetGameState(VWGameState)._ships[Index / MAX_BULLETS];
	return Ship.bullets[Index % MAX_BULLETS];
}

FPlayerConnectionInfo UGameStateInterface::ConnectionInfo(const AVWGameStateBase* VWGameState, int32 Index)
{
	return GetNonGameState(VWGameState).players[Index];
}

float UGameStateInterface::DisconnectTime(const AVWGameStateBase* VWGameState, int32 Index)
{
	return GetNonGameState(VWGameState).GetDisconnectTime(Index);
}

int32 UGameStateInterface::FrameNumber(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).now.framenumber;
}

int32 UGameStateInterface::Checksum(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).now.checksum;
}

int32 UGameStateInterface::PeriodicFrame(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).periodic.framenumber;
}

int32 UGameStateInterface::PeriodicChecksum(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).periodic.checksum;
}

