// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CraftTypes.h"
/**
 * 
 */
struct CRAFT_API FRunningCraftData
{
	FPrimaryAssetId ItemId;
	int32 ItemCount;
	FCraftDynamicDelegate DynamicDelegate;

public:
	FRunningCraftData(const FPrimaryAssetId& InItemID, const int32 InItemCount,
	                  const FCraftDynamicDelegate& InDynamicDelegate);
	
	FRunningCraftData(const FPrimaryAssetId& InItemID, const int32 InItemCount);

	FORCEINLINE bool IsValid() const;
};
