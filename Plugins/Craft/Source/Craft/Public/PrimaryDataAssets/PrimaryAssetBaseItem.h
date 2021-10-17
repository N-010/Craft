// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PrimaryAssetBaseItem.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class CRAFT_API UPrimaryAssetBaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Asset")
	FPrimaryAssetType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AssetBundles="UI"), Category="UI")
	TSoftObjectPtr<UTexture2D> Icon;

public:
	UPrimaryAssetBaseItem(const FObjectInitializer& ObjectInitializer);

	//~ Begin UObject Interfaces
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
