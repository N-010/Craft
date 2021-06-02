// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

/**
 * 
 */
class QUESTSYSTEMEDITORPLUGIN_API FQuestSystemBlueprintActions : public FAssetTypeActions_Blueprint
{
	using Super = FAssetTypeActions_Blueprint;
	
protected:
	uint32 MyAssetCategory;
	
public:
	FQuestSystemBlueprintActions(uint32 Categories);
	virtual uint32 GetCategories() override;

	//~ Begin FAssetTypeActions_Base Interfaces
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects,
	                             TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<
		                             IToolkitHost>()) override;
	//~ End FAssetTypeActions_Base Interfaces
};
