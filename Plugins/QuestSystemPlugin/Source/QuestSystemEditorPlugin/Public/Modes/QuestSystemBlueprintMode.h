// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditorModes.h"

class FQuestSystemBlueprintEditor;

// This is the list of IDs for SM Editor modes
struct FQuestSystemBlueprintModes
{
	// App Name
	static const FName QuestSystemEditorName;

	// Mode constants
	static const FName QuestSystemBlueprintMode;

	static FText GetLocalizedMode(const FName InMode)
	{
		static TMap< FName, FText > LocModes;

		if (LocModes.Num() == 0)
		{
			LocModes.Add(QuestSystemBlueprintMode, NSLOCTEXT("FQuestSystemBlueprintModes", "QuestSystemBlueprintMode", "Graph"));
		}

		check(InMode != NAME_None);
		const FText* OutDesc = LocModes.Find(InMode);
		check(OutDesc);
		return *OutDesc;
	}

private:
	FQuestSystemBlueprintModes() = delete;
	FQuestSystemBlueprintModes(const FQuestSystemBlueprintModes&) = delete;
	FQuestSystemBlueprintModes(FQuestSystemBlueprintModes&&) = delete;
	
};

class FQuestSystemBlueprintMode : public FBlueprintEditorApplicationMode
{
	using Super = FBlueprintEditorApplicationMode;

public:
	FQuestSystemBlueprintMode(TSharedPtr<class FQuestSystemBlueprintEditor> EditorIn);

	// FApplicationMode interface
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	// End of FApplicationMode interface
private:
	TWeakPtr<FQuestSystemBlueprintEditor> Editor;

	FWorkflowAllowedTabSet EditorTabFactories;
};
