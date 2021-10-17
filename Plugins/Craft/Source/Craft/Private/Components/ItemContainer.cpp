// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemContainer.h"
#include "PrimaryDataAssets/PrimaryAssetRecipe.h"


// Sets default values for this component's properties
UItemContainer::UItemContainer()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UItemContainer::AddItem_Implementation(const FPrimaryAssetId& Item, const int32 ItemCount)
{
	bool bResult = false;
	if (Item.IsValid() && ItemCount > 0)
	{
		FItemData OldItemData;
		GetItemData_Implementation(Item, OldItemData);
		const int32 OldItemCount = OldItemData.Count;

		FItemData NewItemData = OldItemData;
		NewItemData.UpdateItemData({ItemCount}, MAX_int32);

		if (NewItemData != OldItemData)
		{
			GetItemMap_Mutable().Add(Item, NewItemData);

			bResult = true;

			NotifyItemChanged_Implementation(true, Item, NewItemData.Count - OldItemCount);
		}
	}


	return bResult;
}

bool UItemContainer::DeleteItem_Implementation(const FPrimaryAssetId& Item, const int32 ItemCount)
{
	bool bResult = false;
	if (Item.IsValid())
	{
		FItemData ResourceInfo;
		GetItemData_Implementation(Item, ResourceInfo);
		if (ResourceInfo.IsValid())
		{
			const int32 OldItemCount = ResourceInfo.Count;
			if (ItemCount < 0)
			{
				ResourceInfo.Count = 0;
			}
			else
			{
				ResourceInfo.Count = FMath::Max(ResourceInfo.Count - ItemCount, 0);
			}

			if (ResourceInfo.IsValid())
			{
				GetItemMap_Mutable().Add(Item, ResourceInfo);
			}
			else
			{
				GetItemMap_Mutable().Remove(Item);
			}

			bResult = true;

			NotifyItemChanged_Implementation(false, Item, OldItemCount - ResourceInfo.Count);
		}
	}

	return bResult;
}

bool UItemContainer::GetItemData_Implementation(const FPrimaryAssetId& Item, FItemData& Data)
{
	bool bResult = false;
	Data = FItemData(0);
	if (Item.IsValid())
	{
		if (const FItemData* FoundData = GetItemMap().Find(Item))
		{
			Data = *FoundData;
			bResult = true;
		}
	}


	return bResult;
}

void UItemContainer::GetItems_Implementation(TArray<FPrimaryAssetId>& PrimaryAssetIds)
{
	PrimaryAssetIds.Reserve(GetItemMap().Num());
	for (const auto& Item : GetItemMap())
	{
		PrimaryAssetIds.Add(Item.Key);
	}
}

const TMap<FPrimaryAssetId, FItemData>& UItemContainer::GetItemMap() const
{
	return Items;
}

void UItemContainer::NotifyItemChanged_Implementation(const bool bAdded, const FPrimaryAssetId& Item,
                                                      const int32& ItemCount)
{
	if (OnItemChanged.IsBound())
	{
		OnItemChanged.Broadcast(bAdded, Item, ItemCount);
	}
}