// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VWBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UVWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static int GetPlayInEditorID();
	
};
