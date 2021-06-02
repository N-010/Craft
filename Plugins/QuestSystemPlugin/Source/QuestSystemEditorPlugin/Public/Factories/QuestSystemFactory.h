// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "QuestSystemFactory.generated.h"

/**
 * 
 */
UCLASS(HideCategories = (Object), MinimalAPI)
class UQuestSystemFactory : public UFactory
{
	GENERATED_BODY()
public:
	// The type of blueprint that will be created
	UPROPERTY(EditAnywhere, Category=GameplayAbilitiesBlueprintFactory)
	TEnumAsByte<enum EBlueprintType> BlueprintType;

	// The parent class of the created blueprint
	UPROPERTY(EditAnywhere, Category=GameplayAbilitiesBlueprintFactory)
	TSubclassOf<class UQuestInstance> ParentClass;

public:
	UQuestSystemFactory(const FObjectInitializer& ObjectInitializer);

public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	                                  UObject* Context, FFeedbackContext* Warn) override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	                                  UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

	virtual bool DoesSupportClass(UClass* Class) override;

	static void CreateGraphsForNewBlueprint(class UQuestSystemBlueprint* NewBlueprint);
	


};
