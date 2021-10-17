// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemData.h"

FItemData::FItemData()
	: Count(1)
{
}

FItemData::FItemData(const FPrimaryAssetId& NewItemID, const int32 InCount)
	: ItemID(NewItemID), Count(InCount)
{
}

FItemData::FItemData(FItemData&& OtherItem) noexcept
	: ItemID(MoveTemp(OtherItem.ItemID)), Count(MoveTemp(OtherItem.Count))
{
}

void FItemData::UpdateItemData(const FItemData& Other, int32 MaxCount)
{
	if (MaxCount <= 0)
	{
		MaxCount = MAX_int32;
	}

	Count = FMath::Clamp(Count + Other.Count, 1, MaxCount);
}

bool FItemData::IsValid() const
{
	return ItemID.IsValid() && Count > 0;
}

bool FItemData::operator==(const FItemData& Other) const
{
	return ItemID == Other.ItemID && Count == Other.Count;
}

bool FItemData::operator!=(const FItemData& Other) const
{
	return !(*this == Other);
}

bool FItemData::operator<(const FItemData& Other) const
{
	return Count < Other.Count;
}

bool FItemData::operator<=(const FItemData& Other) const
{
	return operator<(Other) || operator==(Other);
}

bool FItemData::operator>(const FItemData& Other) const
{
	return !operator<=(Other);
}

bool FItemData::operator>=(const FItemData& Other) const
{
	return !operator<(Other);
}

//~ Begin Replication

void FItemData::PreReplicatedRemove(const FItemArray& InArraySerializer)
{
}

void FItemData::PostReplicatedAdd(const FItemArray& InArraySerializer)
{
}

void FItemData::PostReplicatedChange(const FItemArray& InArraySerializer)
{
}

//~ End Replication

bool FItemArray::AddItem(const FItemData& Item)
{
	const bool bResult = Items.Add(Item) != INDEX_NONE;
	if (bResult)
	{
		MarkArrayDirty();
	}
	return bResult;
}

bool FItemArray::RemoveItem(const FItemData& Item, const bool bUseSwap)
{
	bool bResult = false;
	bResult = bUseSwap ? Items.RemoveSwap(Item) > 0 : Items.Remove(Item) > 0;
	if (bResult)
	{
		MarkArrayDirty();
	}

	return bResult;
}

bool FItemArray::ChangeItem(const FItemData& OldItem, const FItemData& NewItem)
{
	const size_t Index = Items.Find(OldItem);
	const bool bResult = Index != INDEX_NONE;
	if (bResult)
	{
		Items[Index] = NewItem;
		MarkItemDirty(Items[Index]);
	}

	return bResult;
}

const FItemData* FItemArray::GetItemByIndex(const int32& Index)
{
	const FItemData* FoundItem = nullptr;
	if (Items.IsValidIndex(Index))
	{
		FoundItem = &Items[Index];
	}

	return FoundItem;
}

const FItemData* FItemArray::FindItem(const FPrimaryAssetId& ItemID)
{
	const FItemData* FoundItem = nullptr;
	if (ItemID.IsValid())
	{
		FoundItem = Items.FindByPredicate([&ItemID](const FItemData& Item)
		{
			return Item.ItemID == ItemID;
		});
	}
	return FoundItem;
}

bool FItemArray::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
{
	return FastArrayDeltaSerialize(Items, DeltaParams, *this);
}
