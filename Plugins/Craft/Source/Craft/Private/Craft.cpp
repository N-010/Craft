// Copyright Epic Games, Inc. All Rights Reserved.

#include "Craft.h"

#include "Data/ExchangesData.h"
#include "Engine/AssetManager.h"
#include "Engine/AssetManagerSettings.h"
#include "Engine/AssetManagerTypes.h"
#include "Json/JsonItem.h"
#include "Misc/ExpressionParser.h"
#include "PrimaryDataAssets/PrimaryAssetRecipe.h"
#include "UObject/UnrealTypePrivate.h"

#define LOCTEXT_NAMESPACE "FCraftModule"

void FCraftModule::StartupModule()
{
}

void FCraftModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

FORCEINLINE FCraftModule* FCraftModule::Get()
{
	FCraftModule* ThisModule = FModuleManager::LoadModulePtr<FCraftModule>("FCraftModule");
	return ThisModule ? ThisModule : nullptr;
}

int32 FCraftModule::ForceLoadAsset(const FPrimaryAssetId& PrimaryAssetId, const FString& Path)
{
	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if (IsValid(AssetManager) && !Path.IsEmpty())
	{
		const UAssetManagerSettings& AssetManagerSettings = AssetManager->GetSettings();
		for (const FPrimaryAssetTypeInfo& AssetTypeInfo : AssetManagerSettings.PrimaryAssetTypesToScan)
		{
			if (AssetTypeInfo.PrimaryAssetType == PrimaryAssetId.PrimaryAssetType)
			{
				return AssetManager->ScanPathForPrimaryAssets(PrimaryAssetId.PrimaryAssetType,
				                                              Path,
				                                              UPrimaryAssetRecipe::StaticClass(), false);
			}
		}
	}

	return 0;
}

void FCraftModule::GetExchanges(const FPrimaryAssetId& ItemID, TArray<FExchangesData>& OutExchanges)
{
	if (!ItemID.IsValid())
	{
		return;
	}

	const UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if (IsValid(AssetManager))
	{
		FAssetData AssetData;
		AssetManager->GetPrimaryAssetData(ItemID, AssetData);
		if (!AssetData.IsValid())
		{
			return;
		}

		FString ExchangesStr;
		AssetData.GetTagValue(GET_MEMBER_NAME_CHECKED(UPrimaryAssetItemWithExchanges, Exchanges), ExchangesStr);
		if (!ExchangesStr.IsEmpty())
		{
			TMap<FPrimaryAssetId, FItemData> Items;
			FJsonItem::JsonStringToExchanges(ExchangesStr, Items);

			if (Items.Num() > 0)
			{
				OutExchanges.Reserve(Items.Num());
				for (const auto& Item : Items)
				{
					if(!Item.Key.IsValid() || !Item.Value.IsValid())
					{
						OutExchanges.Empty();
						return;
					}
					
					OutExchanges.Add(FExchangesData(Item.Key, Item.Value));
				}
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCraftModule, Craft)