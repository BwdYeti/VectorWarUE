// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VectorWarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AVectorWarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Get the player inputs as bit flags in an int32 that VectorWar can understand */
	int32 GetVectorWarInput();
	
};
