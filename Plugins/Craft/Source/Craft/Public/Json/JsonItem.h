// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FItemData;
/**
 * 
 */
namespace FJsonItem
{

	static FName ArrayField{"Exchanges"};
	
	bool CRAFT_API ExchangesToJsonObject(const TMap<FPrimaryAssetId, FItemData>& Exchanges,
	                                      TSharedRef<FJsonObject> OutJsonObject);

	void CRAFT_API JsonStringToExchanges(const ::FString& JsonString,
	                                            TMap<FPrimaryAssetId, FItemData>& Exchanges);
	
	void CRAFT_API JsonObjectToExchanges(const TSharedRef<FJsonObject> JsonObject,
	                                            TMap<FPrimaryAssetId, FItemData>& Exchanges);
}
