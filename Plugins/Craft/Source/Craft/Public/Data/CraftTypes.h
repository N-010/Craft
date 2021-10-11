// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CraftTypes.generated.h"

UENUM(BlueprintType)
enum class ECraftStatus : uint8
{
	Processing,
	Success,
	Failed,
	Aborted,
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FCraftDynamicDelegate, const ECraftStatus, CraftStatus);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishCraftItem, const FPrimaryAssetId&, CraftItem);

