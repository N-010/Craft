// Fill out your copyright notice in the Description page of Project Settings.


#include "Modes/QuestSystemBlueprintMode.h"

#include "BlueprintEditorTabs.h"
#include "SBlueprintEditorToolbar.h"
#include "Editors/QuestSystemBlueprintEditor.h"

const FName FQuestSystemBlueprintModes::QuestSystemEditorName("QuestSystemEditorApp");
const FName FQuestSystemBlueprintModes::QuestSystemBlueprintMode("GraphName");

FQuestSystemBlueprintMode::FQuestSystemBlueprintMode(TSharedPtr<FQuestSystemBlueprintEditor> EditorIn)
	: Super(EditorIn, FQuestSystemBlueprintModes::QuestSystemBlueprintMode, FQuestSystemBlueprintModes::GetLocalizedMode, false, false)
{
	Editor = EditorIn;

	TabLayout = FTabManager::NewLayout( "Standalone_QuestSystemBlueprintEditMode_Layout_v1" )
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				// Top toolbar
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->SetHideTabWell(true)
				->AddTab(EditorIn->GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				// Main application area
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					// Left side
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					// MyBlueprint View (Graphs & Variables)
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(1.f)
						->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab)
						->SetForegroundTab(FBlueprintEditorTabs::MyBlueprintID)
					)
					// Add more to the left side here
				)
				->Split
				(
					// Middle
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.6f)
					->Split
					(
						// Middle top - graph area
						FTabManager::NewStack()
						->SetSizeCoefficient(0.8f)
						->AddTab("Document", ETabState::ClosedTab)
					)
					->Split
					(
						// Middle bottom - compiler results & find
						FTabManager::NewStack()
						->SetSizeCoefficient(0.2f)
						->AddTab(FBlueprintEditorTabs::CompilerResultsID, ETabState::ClosedTab)
						->AddTab(FBlueprintEditorTabs::FindResultsID, ETabState::ClosedTab)
					)
				)
				->Split
				(
					// Right side
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						// Right top - details view
						FTabManager::NewStack()
						->SetSizeCoefficient(1.f)
						->AddTab(FBlueprintEditorTabs::DetailsID, ETabState::OpenedTab)
					)
					// Add more to right side here.
				)
			)
		);

	ToolbarExtender = MakeShareable(new FExtender);

	if (UToolMenu* Toolbar = EditorIn->RegisterModeToolbarIfUnregistered(GetModeName()))
	{
		EditorIn->GetToolbarBuilder()->AddCompileToolbar(Toolbar);
		EditorIn->GetToolbarBuilder()->AddScriptingToolbar(Toolbar);
		EditorIn->GetToolbarBuilder()->AddBlueprintGlobalOptionsToolbar(Toolbar);
		EditorIn->GetToolbarBuilder()->AddDebuggingToolbar(Toolbar);
	}

}

void FQuestSystemBlueprintMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FBlueprintEditor> BP = Editor.Pin();

	BP->RegisterToolbarTab(InTabManager.ToSharedRef());

	// Mode-specific setup
	BP->PushTabFactories(CoreTabFactories);
	BP->PushTabFactories(BlueprintEditorTabFactories);
	BP->PushTabFactories(EditorTabFactories);

	// Add custom tab factories
}
