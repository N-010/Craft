// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Data/TimeCreationCalculateParameters.h"
#include "RecipeTimeCalculate.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class CRAFT_API URecipeTimeCalculate : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Calculate")
	float Execute(const struct FTimeCreationCalculateParameters& CalculateParameters);
};
