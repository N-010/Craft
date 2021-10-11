// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemData.h"
#include "Interfaces/ItemcontainerInterface.h"
#include "ItemContainer.generated.h"


class UPrimaryAssetRecipe;

UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class CRAFT_API UItemContainer : public UActorComponent, public IItemContainerInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category = "Inventory")
	TMap<FPrimaryAssetId, FItemData> Resources;

public:
	UItemContainer();

	//~ Begin IResourceInventoryInterface Interfaces
public:
	virtual bool AddItem_Implementation(const FPrimaryAssetId& Item, const int32 ItemCount) override;
	virtual bool DeleteItem_Implementation(const FPrimaryAssetId& Item, const int32 ItemCount) override;
	virtual bool GetItemData_Implementation(const FPrimaryAssetId& Item, FItemData& Data) override;
protected:
	virtual void NotifyItemChanged_Implementation(bool bAdded, const FPrimaryAssetId& Item, const int32& ItemCount) override;
	//~ End IResourceInventoryInterface Interfaces
};
