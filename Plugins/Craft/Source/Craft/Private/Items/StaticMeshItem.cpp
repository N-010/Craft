// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/StaticMeshItem.h"

#include "CraftAssetManager.h"
#include "AssetRegistry/Private/AssetRegistry.h"
#include "Engine/AssetManager.h"
#include "Engine/CollisionProfile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PrimaryDataAssets/PrimaryAssetRecipe.h"

FName AStaticMeshItem::StaticMeshComponentName = TEXT("StaticMeshCompnent");


// Sets default values
AStaticMeshItem::AStaticMeshItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

void AStaticMeshItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AssignMesh();
}

void AStaticMeshItem::AssignMesh()
{
	UAssetManager* AssetManager = UAssetManager::GetIfValid();

	if (IsValid(AssetManager) && ItemId.IsValid())
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
				ItemId, {"Mesh"});
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
			else if(IsValid(AssetManager->GetPrimaryAssetObject(ItemId)))
			{
				OnSetMesh();
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


void AStaticMeshItem::OnSetMesh()
{
	UStaticMesh* StaticMesh = nullptr;
	const UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if (AssetManager && AssetManager->IsValid() && ItemId.IsValid() && IsValid(StaticMeshComponent))
	{
		const UObject* PrimaryAssetObject = AssetManager->GetPrimaryAssetObject(ItemId);
		if (!IsValid(PrimaryAssetObject))
		{
			return;
		}

		UStaticMesh* FoundMesh = nullptr;
		for (TPropertyValueIterator<FProperty> It(PrimaryAssetObject->GetClass(), PrimaryAssetObject); It; ++It)
		{
			if (It.Key()->HasMetaData(TEXT("AssetBundles")) && It.Key()->GetMetaData(TEXT("AssetBundles")) ==
				TEXT("Mesh"))
			{
				if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(It.Key()))
				{
					UObject* Object = ObjectProperty->GetObjectPropertyValue(It.Value());
					if(Object)
					{
						FoundMesh = Cast<UStaticMesh>(Object);
						break;
					}
				}
				else
				{
					if (const FSoftObjectProperty* SoftObjectProperty = CastField<FSoftObjectProperty>(It.Key()))
					{
						if(UObject* StaticMeshObject = SoftObjectProperty->LoadObjectPropertyValue(It.Value()))
						{
							FoundMesh = Cast<UStaticMesh>(StaticMeshObject);
							break;
						}
					}
				}
			}
		}

		StaticMeshComponent->SetStaticMesh(FoundMesh);
	}
}
