﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CraftAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CRAFT_API UCraftAssetManager : public UAssetManager
{
	GENERATED_BODY()

	public:
	virtual void StartInitialLoading() override;
};
