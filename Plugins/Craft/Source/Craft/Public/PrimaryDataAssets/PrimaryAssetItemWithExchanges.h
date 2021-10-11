// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryAssetBaseItem.h"
#include "Data/ItemData.h"
#include "PrimaryAssetItemWithExchanges.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CRAFT_API UPrimaryAssetItemWithExchanges : public UPrimaryAssetBaseItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Exchanges")
	TMap<FPrimaryAssetId, FItemData> Exchanges;

public:
	//~ Begin UObject Interfaces
	virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;
	//~ End UObject Interfaces
};
