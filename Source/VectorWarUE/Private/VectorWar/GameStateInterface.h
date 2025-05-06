// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "VectorWar/nongamestate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameStateInterface.generated.h"

// Forward declarations
struct Bullet;
class AVWGameStateBase;

/**
 * 
 */
UCLASS()
class VECTORWARUE_API UGameStateInterface : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Gets the number of ships in the game state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static int32 ShipCount(const AVWGameStateBase* VWGameState);

	/** Gets the total number of bullets allocated by active ships. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static int32 BulletCount(const AVWGameStateBase* VWGameState);

	/**
	 * Gets the Transform of a player's ship.
	 * @param Index						Index of the player
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static FTransform ShipTransform(const AVWGameStateBase* VWGameState, int32 Index);

	/**
	 * Gets a player's score.
	 * @param Index						Index of the player
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static int32 ShipScore(const AVWGameStateBase* VWGameState, int32 Index);

	/**
	 * Gets whether a bullet is enabled.
	 * @param Index						Bullet index
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static bool BulletEnabled(const AVWGameStateBase* VWGameState, int32 Index);

	/**
	 * Gets the Transform of a bullet.
	 * @param Index						Bullet index
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static FTransform BulletTransform(const AVWGameStateBase* VWGameState, int32 Index);

private:

	/**
	 * Gets a Bullet.
	 * @param Index						Bullet index
	 */
	static Bullet GetBullet(const AVWGameStateBase* VWGameState, int32 Index);

public:
	/**
	 * Gets a player's connection info.
	 * @param Index						Index of the player
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static FPlayerConnectionInfo ConnectionInfo(const AVWGameStateBase* VWGameState, int32 Index);

	/**
	 * Gets a player's disconnection state.
	 * @param Index						Index of the player
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameState")
	static float DisconnectTime(const AVWGameStateBase* VWGameState, int32 Index);

	/** Gets the frame number of the game state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GGPO")
	static int32 FrameNumber(const AVWGameStateBase* VWGameState);

	/** Gets the checksum of the game state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GGPO")
	static int32 Checksum(const AVWGameStateBase* VWGameState);

	/** Gets the frame number of the game state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GGPO")
	static int32 PeriodicFrame(const AVWGameStateBase* VWGameState);

	/** Gets the checksum of the game state. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GGPO")
	static int32 PeriodicChecksum(const AVWGameStateBase* VWGameState);
};
