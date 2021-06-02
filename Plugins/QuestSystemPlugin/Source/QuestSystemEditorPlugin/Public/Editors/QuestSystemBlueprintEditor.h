#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"

class UQuestSystemBlueprint;

class FQuestSystemBlueprintEditor : public FBlueprintEditor
{
	using Super = FBlueprintEditor;

private:
	TWeakObjectPtr<UQuestSystemBlueprint> QuestSystemBlueprint;

public:
	FQuestSystemBlueprintEditor();

	void Initialize(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UQuestSystemBlueprint* InSystem);
};