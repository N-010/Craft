// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "StaticMeshItem.generated.h"

class UPrimaryAssetRecipe;

UCLASS(Abstract, BlueprintType, Blueprintable)
class CRAFT_API AStaticMeshItem : public ABaseItem 
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	TOptional<FDelegateHandle> OnFilesLoadedHandle;

public:
	static FName StaticMeshComponentName;

public:
	// Sets default values for this actor's properties
	AStaticMeshItem(const FObjectInitializer& ObjectInitializer);

	//~ Begin Actor Interfaces
	virtual void OnConstruction(const FTransform& Transform) override;
	//~ End Actor Interfaces

protected:
	virtual void OnSetMesh();

	void AssignMesh();
};
