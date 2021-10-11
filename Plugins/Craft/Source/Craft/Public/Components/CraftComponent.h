// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FCraftQueue.h"
#include "Data/CraftData.h"
#include "Data/CraftTypes.h"
#include "Interfaces/ItemcontainerInterface.h"

#include "CraftComponent.generated.h"

class IItemContainerInterface;

UCLASS(ClassGroup=(Craft), Blueprintable, meta=(BlueprintSpawnableComponent))
class CRAFT_API UCraftComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnFinishCraftItem OnFinishCraftItem;

private:
	TUniquePtr<FCraftQueue> CraftQueue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="True"), Category="Settings|Craft")
	int32 MaxNumberCraft = 1.f;

public:
	// Sets default values for this component's properties
	UCraftComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool Craft(const FCraftData& ItemData,
	           const TScriptInterface<IItemContainerInterface>& ItemContainerInterface);

	UFUNCTION(BlueprintCallable)
	bool CraftTest(const FCraftData& ItemData,
	               const TScriptInterface<IItemContainerInterface>& ItemContainerInterface,
	               FCraftDynamicDelegate InDelegate);

public:
	//~ Begin UActorComponent Interfaces
	virtual void InitializeComponent() override;
	//~ End UActorComponent Interfaces

	//~ Begin UObject Interfaces
	virtual void BeginDestroy() override;
	//~ End UObject Interfaces
};
