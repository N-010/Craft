// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSystemEditorPlugin.h"

#include "AssetToolsModule.h"
#include "Algo/ForEach.h"
#include "AssetTypeActions/QuestSystemBlueprintActions.h"

#define LOCTEXT_NAMESPACE "FQuestSystemEditorPluginModule"

EAssetTypeCategories::Type FQuestSystemEditorPluginModule::QuestSystemCategory;
FName FQuestSystemEditorPluginModule::AssetToolsName = TEXT("AssetTools");


void FQuestSystemEditorPluginModule::StartupModule()
{
	IAssetTools& AssetTools = GetAssetTools();
	QuestSystemCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("QuestSystem")), LOCTEXT("QuestSystemCategory", "Quest System"));
	RegisterAssetTypeAction(&AssetTools, MakeShareable(new FQuestSystemBlueprintActions(QuestSystemCategory)));
}

void FQuestSystemEditorPluginModule::ShutdownModule()
{
	IAssetTools& AssetTools = GetAssetTools();
	UnRegisterAssetTypeActions(&AssetTools);
}

void FQuestSystemEditorPluginModule::RegisterAssetTypeAction(IAssetTools* AssetTools,
	const TSharedRef<IAssetTypeActions>& NewActions)
{
	if(AssetTools)
	{
		AssetTools->RegisterAssetTypeActions(NewActions);
		CreatedAssetTypeActions.Add(NewActions);
	}
}

void FQuestSystemEditorPluginModule::UnRegisterAssetTypeActions(IAssetTools* AssetTools)
{
	if(AssetTools)
	{
		for(int32 Idx = 0; Idx < CreatedAssetTypeActions.Num(); ++Idx)
		{
			AssetTools->UnregisterAssetTypeActions(CreatedAssetTypeActions[Idx].ToSharedRef());
		}
	}
}

FORCEINLINE IAssetTools& FQuestSystemEditorPluginModule::GetAssetTools() const
{
	return FModuleManager::LoadModuleChecked<FAssetToolsModule>(AssetToolsName).Get();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemEditorPluginModule, QuestSystemEditorPlugin)