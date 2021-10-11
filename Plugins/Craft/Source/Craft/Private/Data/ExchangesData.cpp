// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ExchangesData.h"

FExchangesData::FExchangesData(const FPrimaryAssetId& InItemID, const FItemData& InItemData)
	: ItemID(InItemID), ItemData(InItemData)
{
}

FORCEINLINE bool FExchangesData::IsValid() const
{
	return ItemID.IsValid() && ItemData.IsValid();
}
