// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ExchangeSubsystem.h"

#include "Craft.h"
#include "Data/ItemData.h"
#include "Interfaces/ItemcontainerInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UExchangeSubsystem::GetExchanges(const FPrimaryAssetId& ItemId, TArray<FItemData>& Exchanges)
{
	FCraftModule::GetExchanges(ItemId, Exchanges);
}

bool UExchangeSubsystem::CanExchangeOnItem(const TScriptInterface<IItemContainerInterface>& ItemContainerInterface,
                                           const FPrimaryAssetId& ItemId)
{
	if (!IsValid(ItemContainerInterface.GetObject()) || !ItemId.IsValid())
	{
		return false;
	}

	TArray<FItemData> Exchanges;
	FCraftModule::GetExchanges(ItemId, Exchanges);
	if (Exchanges.Num() <= 0)
	{
		return false;
	}

	TArray<FItemData> Items;
	IItemContainerInterface::Execute_GetItemDataArray(ItemContainerInterface.GetObject(), Items);
	if (Items.Num() <= 0)
	{
		return false;
	}

	for (const auto& Exchange : Exchanges)
	{
		if (!Exchange.IsValid())
		{
			return false;
		}

		if (const FItemData* FoundItem = Items.FindByPredicate([&Exchange](const FItemData& Item)
		{
			return Item.IsValid() && Exchange.IsValid() && Item.ItemID == Exchange.ItemID;
		}))
		{
			if (!FoundItem->IsValid() || *FoundItem < Exchange)
			{
				return false;
			}
		}
	}

	return true;
}

bool UExchangeSubsystem::RemoveExchangesFromInventory(
	const TScriptInterface<IItemContainerInterface>& ItemContainerInterface, const FPrimaryAssetId& ItemId)
{
	if (IsValid(ItemContainerInterface.GetObject()) && ItemId.IsValid() && CanExchangeOnItem(
		ItemContainerInterface, ItemId))
	{
		TArray<FItemData> Exchanges;
		GetExchanges(ItemId, Exchanges);
		if (Exchanges.Num() > 0)
		{
			// If all items are valid
			if (!Exchanges.FindByPredicate([&](const FItemData& Item)
			{
				return !Item.IsValid();
			}))
			{
				for (const auto& Exchange : Exchanges)
				{
					IItemContainerInterface::Execute_DeleteItemData(ItemContainerInterface.GetObject(), Exchange);
				}

				return true;
			}
		}
	}

	return false;
}

int32 UExchangeSubsystem::AvailableNumberOfItemsForCraft(
	const TScriptInterface<IItemContainerInterface>& ItemContainerInterface, const FPrimaryAssetId& ItemId)
{
	int32 Number = 0;
	UObject* InventoryObject = ItemContainerInterface.GetObject();

	if (IsValid(InventoryObject) && ItemId.IsValid())
	{
		TArray<FItemData> Exchanges;
		GetExchanges(ItemId, Exchanges);
		if (Exchanges.Num() <= 0)
		{
			return 0;
		}

		TArray<FItemData> Items;
		IItemContainerInterface::Execute_GetItemDataArray(InventoryObject, Items);
		if (Items.Num() <= 0)
		{
			return 0;
		}
		
		float Remainder;
		for (const auto& Exchange : Exchanges)
		{
			if (!Exchange.IsValid())
			{
				return 0;
			}

			if (const FItemData* FoundItem = Items.FindByPredicate([&](const FItemData& Item)
			{
				return Item.IsValid() && Exchange.IsValid() && Item.ItemID == Exchange.ItemID;
			}))
			{
				const int32 CurrentNumber =
					UKismetMathLibrary::FMod(FoundItem->Count, Exchange.Count, Remainder);
				if (CurrentNumber <= 0)
				{
					return 0;
				}

				Number = Number <= 0 ? CurrentNumber : FMath::Min(CurrentNumber, Number);
			}
			else
			{
				return 0;
			}
		}
	}

	return Number;
}
