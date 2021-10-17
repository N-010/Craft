// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CraftAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CRAFT_API UCraftAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static const FPrimaryAssetType ArmorRecipe;
	static const FPrimaryAssetType WeaponRecipe;
	static const FPrimaryAssetType MedicineRecipe;
	static const FPrimaryAssetType ShopItem;
	
public:
	virtual void StartInitialLoading() override;
};
