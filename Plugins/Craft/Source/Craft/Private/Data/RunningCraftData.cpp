// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RunningCraftData.h"

FRunningCraftData::FRunningCraftData(const FPrimaryAssetId& InItemID, const int32 InItemCount,
                                     const FCraftDynamicDelegate& InDynamicDelegate)
	: ItemId(InItemID), ItemCount(InItemCount), DynamicDelegate(InDynamicDelegate)
{
}

FRunningCraftData::FRunningCraftData(const FPrimaryAssetId& InItemID, const int32 InItemCount)
	: ItemId(InItemID), ItemCount(InItemCount)

{
}

FORCEINLINE bool FRunningCraftData::IsValid() const
{
	return ItemId.IsValid() && ItemCount > 0;
}
