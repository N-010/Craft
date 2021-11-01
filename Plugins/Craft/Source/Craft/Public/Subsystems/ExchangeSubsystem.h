// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemData.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "ExchangeSubsystem.generated.h"

class IItemContainerInterface;
struct FExchangesData;

/**
 * 
 */
UCLASS()
class CRAFT_API UExchangeSubsystem : public USubsystemBlueprintLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Craft")
	static void GetExchanges(const FPrimaryAssetId& ItemId, TArray<FItemData>& Exchanges);

	UFUNCTION(BlueprintCallable, Category="Craft")
	static bool CanExchangeOnItem(const TScriptInterface<IItemContainerInterface>& ItemContainerInterface,
	                  const FPrimaryAssetId& ItemId);
	
	UFUNCTION(BlueprintCallable, Category="Craft")
	static bool RemoveExchangesFromInventory(const TScriptInterface<IItemContainerInterface>& ItemContainerInterface,
	                  const FPrimaryAssetId& ItemId);
	
	UFUNCTION(BlueprintCallable, Category="Craft")
	static int32 AvailableNumberOfItemsForCraft(const TScriptInterface<IItemContainerInterface>& ItemContainerInterface,
	                  const FPrimaryAssetId& ItemId);
};
