// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CraftComponent.h"

#include "Engine/AssetManager.h"
#include "Interfaces/ItemcontainerInterface.h"
#include "Subsystems/ExchangeSubsystem.h"

// Sets default values for this component's properties
UCraftComponent::UCraftComponent()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bWantsInitializeComponent = true;

	// ...
}

// Called when the game starts
void UCraftComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

bool UCraftComponent::Craft(const FCraftData& ItemData,
                            const TScriptInterface<IItemContainerInterface>& ItemContainerInterface)
{
	if (ItemData.IsValid() && IsValid(ItemContainerInterface.GetObject()) && CraftQueue.IsValid())
	{
		if (UExchangeSubsystem::CanExchangeOnItem(ItemContainerInterface, ItemData.ItemID))
		{
			if (CraftQueue->Craft(ItemData))
			{
				return UExchangeSubsystem::RemoveExchangesFromInventory(ItemContainerInterface, ItemData.ItemID);
			}
		}
	}

	return false;
}

bool UCraftComponent::CraftTest(const FCraftData& ItemData,
                                const TScriptInterface<IItemContainerInterface>& ItemContainerInterface,
                                FCraftDynamicDelegate InDelegate)
{
	bool bResult = false;
	UObject* InventoryObject = ItemContainerInterface.GetObject();
	if (IsValid(InventoryObject) && ItemData.IsValid())
	{
		const int32 AvailableNumber = UExchangeSubsystem::AvailableNumberOfItemsForCraft(
			ItemContainerInterface, ItemData.ItemID);
		if (AvailableNumber > 0 && ItemData.Count <= AvailableNumber)
		{
			if (CraftQueue->Craft(ItemData, InDelegate))
			{
				bResult = UExchangeSubsystem::RemoveExchangesFromInventory(ItemContainerInterface, ItemData.ItemID);
			}
		}
	}

	return bResult;
}

void UCraftComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if (!CraftQueue.IsValid())
	{
		TFunction<void(const FPrimaryAssetId&)> OnFinish = [this](const FPrimaryAssetId& CraftItem)
		{
			if (OnFinishCraftItem.IsBound())
			{
				OnFinishCraftItem.Broadcast(CraftItem);
			}
		};
		CraftQueue = MakeUnique<FCraftQueue>(
			GetWorld(), std::bind(OnFinish, std::placeholders::_1), MaxNumberCraft);
	}
}

void UCraftComponent::BeginDestroy()
{
	if (CraftQueue.IsValid())
	{
		CraftQueue.Reset();
	}

	Super::BeginDestroy();
}
