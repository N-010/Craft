// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemData.h"
#include "Interfaces/ItemcontainerInterface.h"
#include "ItemContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemChanged, bool, bAdded, const FPrimaryAssetId, Item, const int32,
                                               Count);

class UPrimaryAssetRecipe;

UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class CRAFT_API UItemContainer : public UActorComponent, public IItemContainerInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(Replicated, BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category="Container")
	FItemArray ItemArray;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"), Category="Network")
	bool bReplicateItemArray;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"), Category="Network")
	TEnumAsByte<ELifetimeCondition> ItemReplicationCondition;

public:
	UPROPERTY(BlueprintAssignable)
	FOnItemChanged OnItemChanged;

public:
	UItemContainer();

	//~ Begin IResourceInventoryInterface Interfaces
public:
	virtual bool AddItemData_Implementation(const FItemData& ItemData) override;
	virtual bool DeleteItemData_Implementation(const FItemData& ItemData) override;
	virtual void GetItemDataArray_Implementation(TArray<FItemData>& ItemDataArray) override;

protected:
	virtual void
	NotifyItemChanged_Implementation(const bool bAdded, const FPrimaryAssetId& Item, const int32& ItemCount) override;
	//~ End IResourceInventoryInterface Interfaces

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
};
