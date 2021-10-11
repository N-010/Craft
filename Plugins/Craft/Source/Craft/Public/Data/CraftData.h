// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CraftData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CRAFT_API FCraftData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPrimaryAssetId ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeOfCreation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	FCraftData();
	explicit FCraftData(const FPrimaryAssetId& InItemID, const float InTimeOfCreation = 1.f, const int32 InCount = 1);
	FCraftData(const FCraftData& InCraftData);
	FCraftData(FCraftData&& InCraftData);
	
	FCraftData& operator=(const FCraftData& Other);
	FCraftData& operator=(FCraftData&& Other);

	bool IsValid() const;
};
