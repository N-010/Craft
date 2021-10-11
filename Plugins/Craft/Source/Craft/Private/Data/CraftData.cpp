// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CraftData.h"


FCraftData::FCraftData()
	:ItemID(FPrimaryAssetId(NAME_None, NAME_None)), TimeOfCreation(-1.f), Count(0)
{
}

FCraftData::FCraftData(const FPrimaryAssetId& InItemID, const float InTimeOfCreation /*= 1.f*/, const int32 InCount /*= 1*/)
	: ItemID(InItemID), TimeOfCreation(InTimeOfCreation), Count(InCount)
{
}

FCraftData::FCraftData(const FCraftData& InCraftData)
	: ItemID(InCraftData.ItemID), TimeOfCreation(InCraftData.TimeOfCreation), Count(InCraftData.Count)
{
}

FCraftData::FCraftData(FCraftData&& InCraftData)
	: ItemID(MoveTemp(InCraftData.ItemID)), TimeOfCreation(MoveTemp(InCraftData.TimeOfCreation)), Count(MoveTemp(InCraftData.Count))
{
}

FCraftData& FCraftData::operator=(const FCraftData& Other)
{
	if (this != &Other)
	{
		ItemID = Other.ItemID;
		TimeOfCreation = Other.TimeOfCreation;
		Count = Other.Count;
	}

	return *this;
}

FCraftData& FCraftData::operator=(FCraftData&& Other)
{
	if (this != &Other)
	{
		ItemID = MoveTemp(Other.ItemID);
		TimeOfCreation = MoveTemp(Other.TimeOfCreation);
		Count = MoveTemp(Other.Count);
	}

	return *this;
}

bool FCraftData::IsValid() const
{
	return ItemID.IsValid() && TimeOfCreation >= 0.f && Count > 0;
}
