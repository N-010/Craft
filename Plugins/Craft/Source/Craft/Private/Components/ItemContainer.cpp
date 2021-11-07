// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemContainer.h"

#include "Net/UnrealNetwork.h"
#include "PrimaryDataAssets/PrimaryAssetRecipe.h"


// Sets default values for this component's properties
UItemContainer::UItemContainer()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}

bool UItemContainer::AddItemData_Implementation(const FItemData& ItemData)
{
	bool bSuccess = false;
	if (ItemData.IsValid())
	{
		FItemData NewItem{ItemData};
		if (const FItemData* FoundItem = ItemArray.FindItem(ItemData))
		{
			NewItem += FoundItem;
			bSuccess = ItemArray.ChangeItem(*FoundItem, NewItem);
		}
		else
		{
			bSuccess = ItemArray.AddItem(NewItem);
		}
	}

	return bSuccess;
}

bool UItemContainer::DeleteItemData_Implementation(const FItemData& ItemData)
{
	return ItemArray.RemoveItem(ItemData);
}

void UItemContainer::GetItemDataArray_Implementation(TArray<FItemData>& ItemDataArray)
{
	ItemDataArray = ItemArray.GetItems();
}

void UItemContainer::NotifyItemChanged_Implementation(const bool bAdded, const FPrimaryAssetId& Item,
                                                      const int32& ItemCount)
{
	if (OnItemChanged.IsBound())
	{
		OnItemChanged.Broadcast(bAdded, Item, ItemCount);
	}
}

void UItemContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ItemArray);
}
