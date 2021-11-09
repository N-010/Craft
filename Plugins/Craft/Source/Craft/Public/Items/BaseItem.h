// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS(Abstract, BlueprintType)
class CRAFT_API ABaseItem : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FPrimaryAssetId ItemId;
};
