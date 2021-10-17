// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftAssetManager.h"


const FPrimaryAssetType UCraftAssetManager::ArmorRecipe = FName(TEXT("ArmorRecipe"));
const FPrimaryAssetType UCraftAssetManager::WeaponRecipe = FName(TEXT("WeaponRecipe"));
const FPrimaryAssetType UCraftAssetManager::MedicineRecipe = FName(TEXT("MedicineRecipe"));
const FPrimaryAssetType UCraftAssetManager::ShopItem = FName(TEXT("ShopItem"));

void UCraftAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
