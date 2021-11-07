// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/CraftBaseItem.h"

#include "CraftAssetManager.h"
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
	UCraftAssetManager* AssetManager = Cast<UCraftAssetManager>(UAssetManager::GetIfValid());

	if (IsValid(AssetManager) && RecipeComponentItem.IsValid())
	{
		IAssetRegistry& AssetRegistry = AssetManager->GetAssetRegistry();
		if (!AssetRegistry.IsLoadingAssets())
		{
			if (OnFilesLoadedHandle.IsSet())
			{
				AssetRegistry.OnFilesLoaded().Remove(OnFilesLoadedHandle.GetValue());
				OnFilesLoadedHandle.Reset();
			}

			const TSharedPtr<FStreamableHandle> LoadHandle = AssetManager->LoadPrimaryAsset(
				RecipeComponentItem, {"Mesh"});
			if (LoadHandle.IsValid())
			{
				if (!LoadHandle->HasLoadCompleted())
				{
					LoadHandle->BindCompleteDelegate(
						FStreamableDelegate::CreateUObject(this, &ThisClass::OnSetMesh));
				}
				else
				{
					OnSetMesh();
				}
			}
		}
		else
		{
			if (!AssetRegistry.OnFilesLoaded().IsBoundToObject(this))
			{
				/** FTimerManager::SetTimerForNextTick is needed so that the ThisClass::AssignMesh function is called after UAssetManager::OnAssetRegistryFilesLoaded.
				 *	Without it, UAssetManager::LoadPrimaryAsset will return null */
				OnFilesLoadedHandle = AssetRegistry.OnFilesLoaded().AddLambda([&]()
				{
					if (const UWorld* World = GEngine->GetWorldFromContextObject(
						this, EGetWorldErrorMode::LogAndReturnNull))
					{
						World->GetTimerManager().SetTimerForNextTick(this, &ThisClass::AssignMesh);
					}
				});
			}
		}
	}
}

void ACraftBaseItem::SetItemInfoFromSoftObjectPath(const TSoftObjectPtr<UPrimaryAssetRecipe> SoftObjectPath)
{
	const UAssetManager* AssetManager = UAssetManager::GetIfValid();
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
	const UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if (AssetManager->IsValid() && RecipeComponentItem.IsValid() && IsValid(StaticMeshComponent))
	{
		const UPrimaryAssetRecipe* PrimaryAssetRecipe = Cast<UPrimaryAssetRecipe>(
			AssetManager->GetPrimaryAssetObject(RecipeComponentItem));

		StaticMesh = IsValid(PrimaryAssetRecipe) && PrimaryAssetRecipe->StaticMesh.IsValid()
			             ? PrimaryAssetRecipe->StaticMesh.Get()
			             : nullptr;
	}

	StaticMeshComponent->SetStaticMesh(StaticMesh);
}
