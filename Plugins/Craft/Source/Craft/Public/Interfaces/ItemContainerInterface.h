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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Container")
	bool AddItemData(const FItemData& ItemData);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Container")
	bool DeleteItemData(const FItemData& ItemData);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Container")
	void GetItemDataArray(TArray<FItemData>& ItemDataArray);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(BlueprintProtected="True"),
		Category="Container|Notify")
	void NotifyItemChanged(const bool bAdded, const FPrimaryAssetId& Item, const int32& ItemCount);
};
