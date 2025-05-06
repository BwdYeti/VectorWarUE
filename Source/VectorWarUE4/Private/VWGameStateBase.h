// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "VectorWar/vectorwar.h"
#include "GameFramework/GameStateBase.h"
#include "VWGameStateBase.generated.h"

// Forward declarations
class UGGPONetwork;

#define NETWORK_GRAPH_STEPS 720

UENUM(BlueprintType)
enum class ENetworkGraphType : uint8
{
	PING           UMETA(DisplayName = "Ping"),
	SYNC           UMETA(DisplayName = "Fairness"),
	REMOTE_SYNC    UMETA(DisplayName = "Remote Fairness"),
};

USTRUCT(BlueprintType)
struct FNetworkGraphData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32   Fairness;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32   RemoteFairness;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32   Ping;
};

USTRUCT(BlueprintType)
struct FNetworkGraphPlayer {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FNetworkGraphData> PlayerData;
};

/**
 *
 */
UCLASS()
class AVWGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

    GGPOSession* ggpo = nullptr;

    GameState gs = { 0 };
    NonGameState ngs = { 0 };

private:
	bool bSessionStarted;

	float ElapsedTime;

	TArray<FNetworkGraphPlayer> NetworkGraphData;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * Called from BeginPlay() after creating the game state.
	 * Can be overridden by a blueprint to create actors that represent the game state.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="GGPO")
	void OnSessionStarted();
	virtual void OnSessionStarted_Implementation();

	/** Get the game state frame rate */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game State")
	static int32 GetFrameRate();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GGPO")
	TArray<FVector2D> GetNetworkGraphData(int32 Index, ENetworkGraphType Type, FVector2D GraphSize, int32 MinY, int32 MaxY) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Graph")
	static float GraphValue(int32 Value, FVector2D GraphSize, int32 MinY, int32 MaxY);

    const GameState GetGameState() const;
    const NonGameState GetNonGameState() const;

private:
    TArray<FGGPONetworkStats> UpdateNetworkStats();

    float GetTickDuration(int TicksAhead) const;

	void TickGameState();

	/** Gets the inputs from the local player. */
	int32 GetLocalInputs();

    /*
     * VectorWar_RunFrame --
     *
     * Run a single frame of the game.
     */
    void VectorWar_RunFrame(int32 local_input);
    /*
     * VectorWar_AdvanceFrame --
     *
     * Advances the game state by exactly 1 frame using the inputs specified
     * for player 1 and player 2.
     */
    void VectorWar_AdvanceFrame(int32 inputs[], int32 disconnect_flags);
    /*
     * VectorWar_Idle --
     *
     * Spend our idle time in ggpo so it can use whatever time we have left over
     * for its internal bookkeeping.
     */
    void VectorWar_Idle(int32 time);
    void VectorWar_Exit();

    /*
     * VectorWar_DisconnectPlayer --
     *
     * Disconnects a player from this session.
     */
    void VectorWar_DisconnectPlayer(int32 player);

    /** Gets stats about the network connection. */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game State")
    TArray<FGGPONetworkStats> VectorWar_GetNetworkStats();


	/** Starts a GGPO game session. */
	bool TryStartGGPOPlayerSession(int32 NumPlayers, const UGGPONetwork* NetworkAddresses);
	/** Starts a GGPO spectating game session. */
	bool TryStartGGPOSpectatorSession(const int32 NumPlayers, const UGGPONetwork* NetworkAddresses);

    /*
     * VectorWar_Init --
     *
     * Initialize the vector war game.  This initializes the game state and
     * creates a new network session.
     */
	void VectorWar_Init(uint16 localport, int32 num_players, GGPOPlayer* players, int32 num_spectators);
    /*
     * VectorWar_InitSpectator --
     *
     * Create a new spectator session
     */
	void VectorWar_InitSpectator(uint16 localport, int32 num_players, char* host_ip, uint16 host_port);

private:
    /** Gets a GGPOSessionCallbacks object with its callback functions assigned. */
    GGPOSessionCallbacks CreateCallbacks();

    /*
     * The begin game callback.  We don't need to do anything special here,
     * so just return true.
     */
    bool __cdecl vw_begin_game_callback(const char*);
    /*
     * Save the current state to a buffer and return it to GGPO via the
     * buffer and len parameters.
     */
    bool __cdecl vw_save_game_state_callback(unsigned char** buffer, int32* len, int32* checksum, int32);
    /*
     * Makes our current state match the state passed in by GGPO.
     */
    bool __cdecl vw_load_game_state_callback(unsigned char* buffer, int32 len);
    /*
     * Log the gamestate.  Used by the synctest debugging tool.
     */
    bool __cdecl vw_log_game_state(char* filename, unsigned char* buffer, int32);
    /*
     * Free a save state buffer previously returned in vw_save_game_state_callback.
     */
    void __cdecl vw_free_buffer(void* buffer);
    /*
     * Notification from GGPO we should step foward exactly 1 frame
     * during a rollback.
     */
    bool __cdecl vw_advance_frame_callback(int32);
    /*
     * Notification from GGPO that something has happened.  Update the status
     * text at the bottom of the screen to notify the user.
     */
    bool __cdecl vw_on_event_callback(GGPOEvent* info);

};
