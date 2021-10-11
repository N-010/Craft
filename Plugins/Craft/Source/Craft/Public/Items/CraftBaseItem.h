// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CraftBaseItem.generated.h"

class UPrimaryAssetRecipe;

UCLASS(Abstract, BlueprintType, Blueprintable)
class CRAFT_API ACraftBaseItem : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

	bool bIsForceLoad;

	TOptional<FDelegateHandle> OnFilesLoadedHandle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FPrimaryAssetId RecipeComponentItem;

public:
	static FName StaticMeshComponentName;

public:
	// Sets default values for this actor's properties
	ACraftBaseItem(const FObjectInitializer& ObjectInitializer);

	//~ Begin Actor Interfaces
	virtual void OnConstruction(const FTransform& Transform) override;
	//~ End Actor Interfaces

	UFUNCTION(BlueprintCallable, Category="Item")
	void SetItemInfoFromAssetID(const FPrimaryAssetId AssetId);

	UFUNCTION(BlueprintCallable, Category="Item")
	void SetItemInfoFromSoftObjectPath(const TSoftObjectPtr<UPrimaryAssetRecipe> SoftObjectPath);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnSetMesh();

	void AssignMesh();
};
