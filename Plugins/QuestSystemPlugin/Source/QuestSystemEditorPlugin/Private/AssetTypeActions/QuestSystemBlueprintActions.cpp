// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeActions/QuestSystemBlueprintActions.h"

#include "Blueprints/QuestSystemBlueprint.h"
#include "Editors/QuestSystemBlueprintEditor.h"
#include "Factories/QuestSystemFactory.h"

#define LOCTEXT_NAMESPACE "FQuestSystemBlueprintActions"

FQuestSystemBlueprintActions::FQuestSystemBlueprintActions(uint32 Categories)
	: Super(), MyAssetCategory(Categories)
{
}

uint32 FQuestSystemBlueprintActions::GetCategories()
{
	return MyAssetCategory;
}

FText FQuestSystemBlueprintActions::GetName() const
{
	return LOCTEXT("QuestSystemBlueprintActionsName", "Quest System");
}

FColor FQuestSystemBlueprintActions::GetTypeColor() const
{
	return FLinearColor(242.324715f, 201.797565f, 0.f).ToRGBE();
}

UClass* FQuestSystemBlueprintActions::GetSupportedClass() const
{
	return UQuestSystemBlueprint::StaticClass();
}

void FQuestSystemBlueprintActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UQuestSystemBlueprint* QuestSystemBlueprint = Cast<UQuestSystemBlueprint>(*ObjIt))
		{
			if (QuestSystemBlueprint->bIsNewlyCreated /*&& FSMBlueprintEditorUtils::GetTopLevelStateMachineGraph(StateMachineBP) == nullptr*/)
			{
				UQuestSystemFactory::CreateGraphsForNewBlueprint(QuestSystemBlueprint);
			}

			
			TSharedRef<FQuestSystemBlueprintEditor> BlueprintEditor(new FQuestSystemBlueprintEditor());
			BlueprintEditor->Initialize(Mode, EditWithinLevelEditor, QuestSystemBlueprint);
		}
	}
}

#undef LOCTEXT_NAMESPACE