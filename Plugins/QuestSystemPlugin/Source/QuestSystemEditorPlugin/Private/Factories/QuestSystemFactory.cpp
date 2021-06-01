// Fill out your copyright notice in the Description page of Project Settings.


#include "Factories/QuestSystemFactory.h"

#include "BlueprintEditorSettings.h"
#include "QuestInstance.h"
#include "Blueprints/QuestSystemBlueprint.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UQuestSystemFactory"

UQuestSystemFactory::UQuestSystemFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), ParentClass(UQuestInstance::StaticClass())
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UQuestSystemBlueprint::StaticClass();
}

UObject* UQuestSystemFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                               UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(InClass, InParent, InName, Flags, Context, Warn, NAME_None);
}

UObject* UQuestSystemFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                               UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	// Make sure we are trying to factory a gameplay ability blueprint, then create and init one
	check(InClass->IsChildOf(UQuestSystemBlueprint::StaticClass()));

	// If they selected an interface, force the parent class to be UInterface
	if (BlueprintType == BPTYPE_Interface)
	{
		ParentClass = UInterface::StaticClass();
	}

	if ((ParentClass == NULL) || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) || !ParentClass->
		IsChildOf(UQuestInstance::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), (ParentClass != NULL)
			                            ? FText::FromString(ParentClass->GetName())
			                            : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok,
		                     FText::Format(LOCTEXT("CannotCreateQuestSystemBlueprint",
		                                           "Cannot create a Quest System Blueprint based on the class '{ClassName}'."), Args));
		return nullptr;
	}
	else
	{
		UQuestSystemBlueprint* NewBP = CastChecked<UQuestSystemBlueprint>(
			FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BlueprintType,
			                                        UQuestSystemBlueprint::StaticClass(),
			                                        UBlueprintGeneratedClass::StaticClass(), CallingContext));
		if (NewBP)
		{
			CreateGraphForNewBlueprint(NewBP);
		}

		return NewBP;
	}
}

bool UQuestSystemFactory::DoesSupportClass(UClass* Class)
{
	return IsValid(Class) ? Class == UQuestSystemBlueprint::StaticClass() : false;
}

void UQuestSystemFactory::CreateGraphForNewBlueprint(UQuestSystemBlueprint* NewBlueprint)
{
	if (IsValid(NewBlueprint))
	{
		UEdGraph* EventGraph = FindObject<UEdGraph>(NewBlueprint, *(UEdGraphSchema_K2::GN_EventGraph.ToString()));
		if (!IsValid(EventGraph))
		{
#if WITH_EDITORONLY_DATA
			if (NewBlueprint->UbergraphPages.Num())
			{
				FBlueprintEditorUtils::RemoveGraphs(NewBlueprint, NewBlueprint->UbergraphPages);
			}
#endif
			EventGraph = FBlueprintEditorUtils::CreateNewGraph(NewBlueprint, UEdGraphSchema_K2::GN_EventGraph,
			                                                   UEdGraph::StaticClass(),
			                                                   UEdGraphSchema_K2::StaticClass());

			FBlueprintEditorUtils::AddUbergraphPage(NewBlueprint, EventGraph);
			EventGraph->bAllowDeletion = false;

			const UEdGraphSchema* EventGraphSchema = EventGraph->GetSchema();
			EventGraphSchema->CreateDefaultNodesForGraph(*EventGraph);
		}
		
		UBlueprintEditorSettings* Settings = GetMutableDefault<UBlueprintEditorSettings>();
		if(Settings && Settings->bSpawnDefaultBlueprintNodes)
		{
		}
	}
}

#undef LOCTEXT_NAMESPACE
