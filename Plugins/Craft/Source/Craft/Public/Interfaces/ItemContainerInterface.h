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
	bool AddItem(const FPrimaryAssetId& Item, const int32 ItemCount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Container")
	bool DeleteItem(const FPrimaryAssetId& Item, const int32 ItemCount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Container")
	bool GetItemData(const FPrimaryAssetId& Item, FItemData& Data);
	
	virtual const TMap<FPrimaryAssetId, FItemData>& GetItemMap() const = 0;
	virtual TMap<FPrimaryAssetId, FItemData>& GetItemMap_Mutable()
	{
		return const_cast<TMap<FPrimaryAssetId, FItemData>&>(GetItemMap());
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Container")
	void GetItems(TArray<FPrimaryAssetId>& Items);
	
protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta=(BlueprintProtected="True"),
		Category="Container|Notify")
	void NotifyItemChanged(const bool bAdded, const FPrimaryAssetId& Item, const int32& ItemCount);
};
