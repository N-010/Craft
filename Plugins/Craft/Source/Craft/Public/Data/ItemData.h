// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct CRAFT_API FItemData : public FFastArraySerializerItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPrimaryAssetId ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

public:
	FItemData();

	FItemData(const FPrimaryAssetId& NewItemID, const int32 InCount = 1);
	FItemData(const FItemData& OtherItem) = default;
	FItemData(FItemData&& OtherItem) noexcept;

	void UpdateItemData(const FItemData& Other, int32 MaxCount);

	bool IsValid() const;

	bool operator==(const FItemData& Other) const;
	bool operator!=(const FItemData& Other) const;
	bool operator<(const FItemData& Other) const;
	bool operator<=(const FItemData& Other) const;
	bool operator>(const FItemData& Other) const;
	bool operator>=(const FItemData& Other) const;

	FItemData& operator =(const FItemData&) = default;
	FItemData& operator =(FItemData&&) = default;

	//~ Begin Replication
	void PreReplicatedRemove(const struct FItemArray& InArraySerializer);
	void PostReplicatedAdd(const struct FItemArray& InArraySerializer);
	void PostReplicatedChange(const struct FItemArray& InArraySerializer);
	//~ End Replication
};

USTRUCT(BlueprintType)
struct FItemArray : public FFastArraySerializer
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<FItemData> Items;

public:
	bool AddItem(const FItemData& Item);
	bool RemoveItem(const FItemData& Item, const bool bUseSwap = true);
	bool ChangeItem(const FItemData& OldItem, const FItemData& NewItem);
	const FItemData* GetItemByIndex(const int32& Index);
	const FItemData* FindItem(const FPrimaryAssetId& ItemID);

public:
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);
};

template <>
struct TStructOpsTypeTraits<FItemArray> : public TStructOpsTypeTraitsBase2<FItemArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
