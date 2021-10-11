// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ExchangeSubsystem.h"

#include "Craft.h"
#include "Data/ExchangesData.h"
#include "Data/ItemData.h"
#include "Interfaces/ItemcontainerInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UExchangeSubsystem::GetExchanges(const FPrimaryAssetId& ItemId, TArray<FExchangesData>& Exchanges)
{
	FCraftModule::GetExchanges(ItemId, Exchanges);
}

bool UExchangeSubsystem::CanExchangeOnItem(const TScriptInterface<IItemContainerInterface>& ResourceInventoryInterface,
                                   const FPrimaryAssetId& ItemId)
{
	if (!IsValid(ResourceInventoryInterface.GetObject()) || !ItemId.IsValid())
	{
		return false;
	}

	TArray<FExchangesData> Exchanges;
	FCraftModule::GetExchanges(ItemId, Exchanges);
	if (Exchanges.Num() <= 0)
	{
		return false;
	}

	for (const auto& Dependency : Exchanges)
	{
		if (!Dependency.IsValid())
		{
			return false;
		}

		FItemData ItemData;
		IItemContainerInterface::Execute_GetItemData(ResourceInventoryInterface.GetObject(),
		                                                     Dependency.ItemID, ItemData);
		if (!ItemData.IsValid() || Dependency.ItemData > ItemData)
		{
			return false;
		}
	}

	return true;
}

bool UExchangeSubsystem::RemoveExchangesFromInventory(
	const TScriptInterface<IItemContainerInterface>& ResourceInventoryInterface, const FPrimaryAssetId& ItemId)
{
	if (IsValid(ResourceInventoryInterface.GetObject()) && ItemId.IsValid() && CanExchangeOnItem(
		ResourceInventoryInterface, ItemId))
	{
		TArray<FExchangesData> Exchanges;
		GetExchanges(ItemId, Exchanges);
		if (Exchanges.Num() > 0)
		{
			// If all items are valid
			if (!Exchanges.FindByPredicate([&](const FExchangesData& Item)
			{
				return !Item.IsValid();
			}))
			{
				for (const auto& Dependency : Exchanges)
				{
					IItemContainerInterface::Execute_DeleteItem(
						ResourceInventoryInterface.GetObject(), Dependency.ItemID, Dependency.ItemData.Count);
				}

				return true;
			}
		}
	}

	return false;
}

int32 UExchangeSubsystem::AvailableNumberOfItemsForCraft(
	const TScriptInterface<IItemContainerInterface>& ResourceInventoryInterface, const FPrimaryAssetId& ItemId)
{
	int32 Number = 0;
	UObject* InventoryObject = ResourceInventoryInterface.GetObject();

	if (IsValid(InventoryObject) && ItemId.IsValid())
	{
		TArray<FExchangesData> Exchanges;
		GetExchanges(ItemId, Exchanges);

		FItemData ItemData;
		float Remainder;
		for (const auto& Dependency : Exchanges)
		{
			if (!Dependency.IsValid())
			{
				return 0;
			}

			ResourceInventoryInterface->Execute_GetItemData(InventoryObject, Dependency.ItemID, ItemData);
			if(!ItemData.IsValid())
			{
				return 0;
			}
			
			const int32 CurrentNumber = UKismetMathLibrary::FMod(ItemData.Count, Dependency.ItemData.Count, Remainder);
			if(CurrentNumber <= 0)
			{
				return 0;
			}

			Number = Number <= 0 ? CurrentNumber : FMath::Min(CurrentNumber, Number);			
		}
	}

	return Number;
}
