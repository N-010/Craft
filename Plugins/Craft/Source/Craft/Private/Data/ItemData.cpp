// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemData.h"

FItemData::FItemData()
	: Count(1)
{
}

FItemData::FItemData(int32 InCount): Count(InCount)
{
}

FItemData::FItemData(FItemData&& OtheItem) noexcept
{
	Count = MoveTemp(OtheItem.Count);
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
	return Count > 0;
}

bool FItemData::operator==(const FItemData& Other) const
{
	return Count == Other.Count;
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
