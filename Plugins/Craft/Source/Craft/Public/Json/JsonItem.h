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
	
	bool CRAFT_API ExchangesToJsonObject(const TArray<FItemData>& Exchanges,
	                                     TSharedRef<FJsonObject> OutJsonObject);

	void CRAFT_API JsonStringToExchanges(const ::FString& JsonString,
	                                     TArray<FItemData>& Exchanges);
	
	void CRAFT_API JsonObjectToExchanges(const TSharedRef<FJsonObject> JsonObject,
	                                     TArray<FItemData>& Exchanges);
}
