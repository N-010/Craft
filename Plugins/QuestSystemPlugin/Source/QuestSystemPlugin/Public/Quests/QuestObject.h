// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/LocalMessage.h"
#include "QuestObject.generated.h"

/**
 * 
 */
UCLASS(abstract)
class QUESTSYSTEMPLUGIN_API UQuestObject : public ULocalMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Visual")
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Visual")
	TSoftObjectPtr<UTexture2D> QuestIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UQuestObject*> SubQuests;
};
