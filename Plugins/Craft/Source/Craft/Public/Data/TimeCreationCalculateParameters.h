// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeCreationCalculateParameters.generated.h"

class UCraftComponent;
/**
 * 
 */
USTRUCT(BlueprintType)
struct CRAFT_API FTimeCreationCalculateParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCraftComponent> CraftComponent;
};
