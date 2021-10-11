// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/CraftBaseItem.h"

#include "Craft.h"
#include "AssetRegistry/Private/AssetRegistry.h"
#include "Engine/AssetManager.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PrimaryDataAssets/PrimaryAssetRecipe.h"

FName ACraftBaseItem::StaticMeshComponentName = TEXT("StaticMeshCompnent");


// Sets default values
ACraftBaseItem::ACraftBaseItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  bIsForceLoad(false)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	StaticMeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>(ThisClass::StaticMeshComponentName);
	if (StaticMeshComponent)
	{
		RootComponent = StaticMeshComponent;

		StaticMeshComponent->AlwaysLoadOnClient = true;
		StaticMeshComponent->AlwaysLoadOnServer = true;
		StaticMeshComponent->bOwnerNoSee = false;
		StaticMeshComponent->bCastDynamicShadow = true;
		StaticMeshComponent->bAffectDynamicIndirectLighting = true;
		StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
		StaticMeshComponent->SetGenerateOverlapEvents(false);
		StaticMeshComponent->SetCanEverAffectNavigation(false);
	}
}

void ACraftBaseItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AssignMesh();
}

void ACraftBaseItem::SetItemInfoFromAssetID(const FPrimaryAssetId AssetId)
{
	if (AssetId.IsValid())
	{
		const TSoftObjectPtr<UObject> SoftObjectPtr =
			UKismetSystemLibrary::GetSoftObjectReferenceFromPrimaryAssetId(AssetId);
		if (SoftObjectPtr.IsValid())
		{
			const TSoftObjectPtr<UPrimaryAssetRecipe> PrimaryAssetRecipeSoftObjectPtr(SoftObjectPtr.ToSoftObjectPath());
			SetItemInfoFromSoftObjectPath(PrimaryAssetRecipeSoftObjectPtr);
		}
	}
}

void ACraftBaseItem::AssignMesh()
{
	UAssetManager* AssetManager = UAssetManager::GetIfValid();

	if (IsValid(AssetManager))
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
			TEXT("AssetRegistry"));
		if (!AssetRegistryModule.Get().IsLoadingAssets())
		{
			if (OnFilesLoadedHandle.IsSet())
			{
				AssetRegistryModule.Get().OnFilesLoaded().Remove(OnFilesLoadedHandle.GetValue());
				OnFilesLoadedHandle.Reset();
			}

			if (RecipeComponentItem.IsValid())
			{
				const TSharedPtr<FStreamableHandle> LoadHandle = AssetManager->LoadPrimaryAsset(
					RecipeComponentItem, {"Mesh"});
				if (LoadHandle.IsValid())
				{
					if (!LoadHandle->HasLoadCompleted())
					{
						LoadHandle->BindCompleteDelegate(
							FStreamableDelegate::CreateUObject(this, &ThisClass::OnSetMesh));
						return;
					}
				}
#if WITH_EDITOR
				else
				{
					if (!bIsForceLoad && FCraftModule::ForceLoadAsset(RecipeComponentItem, TEXT("/Game/Recipes/")) > 0)
					{
						bIsForceLoad = true;
						AssignMesh();
					}
				}
#endif //WITH_EDITOR
			}
		}
		else
		{
			if (!AssetRegistryModule.Get().OnFilesLoaded().IsBoundToObject(this))
			{
				OnFilesLoadedHandle = AssetRegistryModule.Get().OnFilesLoaded().
				                                          AddUObject(this, &ThisClass::AssignMesh);
			}
		}
	}

	OnSetMesh();

	return;
}

void ACraftBaseItem::SetItemInfoFromSoftObjectPath(const TSoftObjectPtr<UPrimaryAssetRecipe> SoftObjectPath)
{
	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if (IsValid(AssetManager) && SoftObjectPath.IsValid())
	{
		RecipeComponentItem = AssetManager->GetPrimaryAssetIdForPath(SoftObjectPath.ToSoftObjectPath());
		AssignMesh();
	}
}

// Called when the game starts or when spawned
void ACraftBaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACraftBaseItem::OnSetMesh()
{
	UStaticMesh* StaticMesh = nullptr;
	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if (AssetManager->IsValid() && RecipeComponentItem.IsValid() && IsValid(StaticMeshComponent))
	{
		UPrimaryAssetRecipe* PrimaryAssetRecipe = Cast<UPrimaryAssetRecipe>(
			AssetManager->GetPrimaryAssetObject(RecipeComponentItem));

		StaticMesh = IsValid(PrimaryAssetRecipe) && PrimaryAssetRecipe->StaticMesh.IsValid()
			             ? PrimaryAssetRecipe->StaticMesh.Get()
			             : nullptr;
	}

	StaticMeshComponent->SetStaticMesh(StaticMesh);
}
