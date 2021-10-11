// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/ItemData.h"
#include "ItemcontainerInterface.generated.h"

class UPrimaryAssetRecipe;

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UItemContainerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRAFT_API IItemContainerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Craft|Inventory|Recource")
	bool AddItem(const FPrimaryAssetId& Item, const int32 ItemCount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Craft|Inventory|Recource")
	bool DeleteItem(const FPrimaryAssetId& Item, const int32 ItemCount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Craft|Inventory|Recource")
	bool GetItemData(const FPrimaryAssetId& Item, FItemData& Data);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(BlueprintProtected="True"),
		Category="Craft|Inventory|Notify")
	void NotifyItemChanged(bool bAdded, const FPrimaryAssetId& Item, const int32& ItemCount);
};
