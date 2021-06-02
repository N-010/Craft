// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"

class IAssetTypeActions;
class IAssetTools;

class FQuestSystemEditorPluginModule : public IModuleInterface
{
protected:
	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;

	static FName AssetToolsName;

	static EAssetTypeCategories::Type QuestSystemCategory;

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	void RegisterAssetTypeAction(IAssetTools* AssetTools, const TSharedRef<IAssetTypeActions>& NewActions);

	void UnRegisterAssetTypeActions(IAssetTools* AssetTools);

	FORCEINLINE IAssetTools& GetAssetTools() const;
};
