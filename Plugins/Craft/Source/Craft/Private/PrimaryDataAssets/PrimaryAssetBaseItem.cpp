// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryDataAssets/PrimaryAssetBaseItem.h"

UPrimaryAssetBaseItem::UPrimaryAssetBaseItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FPrimaryAssetId UPrimaryAssetBaseItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}
