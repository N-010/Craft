// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryAssetItemWithExchanges.h"
#include "Data/ItemData.h"
#include "PrimaryAssetRecipe.generated.h"

class URecipeTimeCalculate;

/**
 * 
 */
UCLASS(Blueprintable)
class CRAFT_API UPrimaryAssetRecipe : public UPrimaryAssetItemWithExchanges
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft", meta=(AssetBundles="Craft"))
	TSoftClassPtr<AActor> CraftingItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft")
	TSubclassOf<URecipeTimeCalculate> CustomTimeCreationClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, AssetRegistrySearchable, Category="Craft")
	float TimeCreation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Craft")
	TMap<FPrimaryAssetId, FItemData> ItemsForCrafting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh", meta=(AssetBundles="Mesh"))
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh", meta=(AssetBundles="Mesh"))
	TSoftObjectPtr<UStaticMesh> StaticMesh;

public:
	UPrimaryAssetRecipe();

	float GetTimerCreation() const;
};
