// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

struct FExchangesData;

class FCraftModule : public IModuleInterface
{

	

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	FORCEINLINE static FCraftModule* Get();

	static int32 ForceLoadAsset(const FPrimaryAssetId& PrimaryAssetId, const FString& Path);

	static void GetExchanges(const FPrimaryAssetId& ItemID, TArray<FExchangesData>& OutExchanges);
};
