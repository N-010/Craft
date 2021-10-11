// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryDataAssets/PrimaryAssetRecipe.h"
#include "Engine/AssetManager.h"

UPrimaryAssetRecipe::UPrimaryAssetRecipe()
	: Super(),
	  TimeCreation(1.f)
{
}

float UPrimaryAssetRecipe::GetTimerCreation() const
{
	return TimeCreation;
}
