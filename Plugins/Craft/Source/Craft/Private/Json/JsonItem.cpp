// Fill out your copyright notice in the Description page of Project Settings.


#include "Json/JsonItem.h"
#include "Data/ItemData.h"

bool FJsonItem::ExchangesToJsonObject(const TMap<FPrimaryAssetId, FItemData>& Exchanges,
                                              TSharedRef<FJsonObject> OutJsonObject)
{
	if (Exchanges.Num() > 0)
	{
		TArray<TSharedPtr<FJsonValue>> JsonValues;
		for (const auto& ItemForCrafting : Exchanges)
		{
			const FPrimaryAssetId& ItemId = ItemForCrafting.Key;
			if (!ItemId.IsValid())
			{
				return false;
			}

			TArray<TSharedPtr<FJsonValue>> ItemDataJsonArray;
			ItemDataJsonArray.Add(MakeShared<FJsonValueString>(ItemId.ToString()));
			ItemDataJsonArray.Add(MakeShared<FJsonValueNumber>(ItemForCrafting.Value.Count));

			JsonValues.Add(MakeShared<FJsonValueArray>(ItemDataJsonArray));
		}

		if (JsonValues.Num() > 0)
		{
			OutJsonObject->SetArrayField(ArrayField.ToString(), JsonValues);
			return true;
		}
	}

	return false;
}

void FJsonItem::JsonStringToExchanges(const FString& JsonString,
                                              TMap<FPrimaryAssetId, FItemData>& Exchanges)
{
	if (!JsonString.IsEmpty())
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
		FJsonSerializer::Deserialize(Reader, JsonObject);

		JsonObjectToExchanges(JsonObject.ToSharedRef(), Exchanges);
	}
}

void FJsonItem::JsonObjectToExchanges(const TSharedRef<FJsonObject> JsonObject,
                                              TMap<FPrimaryAssetId, FItemData>& Exchanges)
{
	const TArray<TSharedPtr<FJsonValue>>& JsonArray = JsonObject->GetArrayField(ArrayField.ToString());
	Exchanges.Reserve(JsonArray.Num());

	
	for (const auto& JsonValue : JsonArray)
	{
		const TArray<TSharedPtr<FJsonValue>>& Fields = JsonValue->AsArray();
		if (Fields.Num() == 2)
		{
			FString ItemIdString(Fields[0]->AsString());
			const int32 Count = static_cast<int32>(Fields[1]->AsNumber());
			FPrimaryAssetId ItemID(ItemIdString);
			if (ItemID.IsValid())
			{
				Exchanges.Add(ItemID, FItemData(Count));
			}
			
		}
	}
}
