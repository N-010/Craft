// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "ExchangesData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct CRAFT_API FExchangesData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPrimaryAssetId ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemData ItemData;
	
	FExchangesData() = default;
	explicit FExchangesData(const FPrimaryAssetId& InItemID, const FItemData& InItemData);

	FORCEINLINE bool IsValid() const;

};
