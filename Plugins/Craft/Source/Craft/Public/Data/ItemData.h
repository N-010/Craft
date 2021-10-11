// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct CRAFT_API FItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

public:
	FItemData();

	FItemData(int32 InCount);
	FItemData(const FItemData& OtherItem) = default;
	FItemData(FItemData&& OtheItem) noexcept;

	void UpdateItemData(const FItemData& Other, int32 MaxCount);

	bool IsValid() const;

	bool operator==(const FItemData& Other) const;
	bool operator!=(const FItemData& Other) const;
	bool operator<(const FItemData& Other) const;
	bool operator<=(const FItemData& Other) const;
	bool operator>(const FItemData& Other) const;
	bool operator>=(const FItemData& Other) const;

	FItemData& operator =(const FItemData &) = default;
	FItemData& operator =(FItemData &&) = default;
};
