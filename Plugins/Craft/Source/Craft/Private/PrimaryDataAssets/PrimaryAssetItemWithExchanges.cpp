// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryDataAssets/PrimaryAssetItemWithExchanges.h"
#include "Json/JsonItem.h"

void UPrimaryAssetItemWithExchanges::GetAssetRegistryTags(TArray<FAssetRegistryTag>& AssetRegistryTags) const
{
	Super::GetAssetRegistryTags(AssetRegistryTags);

	Super::GetAssetRegistryTags(AssetRegistryTags);
	const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (FJsonItem::ExchangesToJsonObject(Exchanges, JsonObject))
	{
		FString OutputString;
		const TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<>::Create(
			&OutputString);
		FJsonSerializer::Serialize(JsonObject, Writer);

		if (!OutputString.IsEmpty())
		{
			AssetRegistryTags.Add(FAssetRegistryTag(
				GET_MEMBER_NAME_CHECKED(ThisClass, Exchanges), OutputString,
				FAssetRegistryTag::TT_Hidden));
		}
	}
}
