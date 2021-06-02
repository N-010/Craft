// Fill out your copyright notice in the Description page of Project Settings.


#include "Editors/QuestSystemBlueprintEditor.h"

#include "SBlueprintEditorToolbar.h"
#include "Blueprints/QuestSystemBlueprint.h"
#include "Kismet2/DebuggerCommands.h"
#include "Modes/QuestSystemBlueprintMode.h"

FQuestSystemBlueprintEditor::FQuestSystemBlueprintEditor()
	: Super()
{
}

void FQuestSystemBlueprintEditor::Initialize(const EToolkitMode::Type Mode,
                                             const TSharedPtr<IToolkitHost>& InitToolkitHost,
                                             UQuestSystemBlueprint* InSystem)
{
	if (!IsValid(InSystem))
	{
		return;
	}
	
	QuestSystemBlueprint = MakeWeakObjectPtr(InSystem);
	if (!Toolbar.IsValid())
	{
		Toolbar = MakeShareable(new FBlueprintEditorToolbar(SharedThis(this)));
	}

	// So the play bar matches the level bar.
	GetToolkitCommands()->Append(FPlayWorldCommands::GlobalPlayWorldActions.ToSharedRef());

	CreateDefaultCommands();

	RegisterMenus();

	const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(
		FTabManager::NewPrimaryArea());
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	InitAssetEditor(Mode, InitToolkitHost, FQuestSystemBlueprintModes::QuestSystemEditorName, DummyLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InSystem, false);

	TArray<UBlueprint*> Blueprints;
	Blueprints.Add(InSystem);

	CommonInitialization(Blueprints);

	const TSharedPtr<FQuestSystemBlueprintEditor> Editor(SharedThis(this));

	const TSharedRef<FApplicationMode> BlueprintMode = MakeShareable(new FQuestSystemBlueprintMode(Editor));
	AddApplicationMode(BlueprintMode->GetModeName(), BlueprintMode);

	/*ExtendMenu();
	ExtendToolbar();
	*/
	RegenerateMenusAndToolbars();

	/*// This does the actual layout generation.
	SetCurrentMode(BlueprintMode->GetModeName());

	PostLayoutBlueprintEditorInitialization();

	OnDebugObjectSetHandle = Blueprint->OnSetObjectBeingDebugged().AddRaw(this, &FSMBlueprintEditor::OnDebugObjectSet);*/
}
