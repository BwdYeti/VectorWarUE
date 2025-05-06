// Copyright 2020 BwdYeti.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Helper.generated.h"

/**
 * 
 */
UCLASS()
class VECTORWARUE_API UHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Converts an int32 to a string of hex characters */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities|Text")
	static FString IntToHex(int32 Value);

	/** Converts an int64 to a string of hex characters */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utilities|Text")
	static FString LongToHex(int64 Value);
};
