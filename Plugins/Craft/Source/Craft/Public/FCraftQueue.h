// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/CraftData.h"
#include "Data/RunningCraftData.h"

class FCraftDynamicDelegate;
class UPrimaryAssetRecipe;

/**
 * 
 */

class CRAFT_API FCraftQueue final : public FNoncopyable
{

private:
	TDoubleLinkedList<FCraftData> Queue;

	TMap<FTimerHandle, FRunningCraftData> RunningCrafts;

	TWeakObjectPtr<UWorld> CurrentWorld;

	TFunction<void(const FPrimaryAssetId&)> FinishCraftCallback;

	int32 MaxNumberCraft;

	TOptional<FTimerManager*> TimerManager;
	
public:
	FCraftQueue() = delete;
	FCraftQueue(FCraftQueue&& CraftQueue) = delete;

	explicit FCraftQueue(UWorld* World, TFunction<void(const FPrimaryAssetId&)>&& InFinishCraftCallback, const int32 InMaxNumberCraft = 1);
	~FCraftQueue();

public:
	void SetMaxNumberCraft(const int32 NewMaxNumberCraft);

	[[deprecated("Use Craft(const FCraftData& CraftData, const FCraftDynamicDelegate& InDelegate)")]]
	bool Craft(const FCraftData& CraftData);
	bool Craft(const FCraftData& CraftData, const FCraftDynamicDelegate& InDelegate);

	const TMap<FTimerHandle, FRunningCraftData>& GetCurrentCrafts() const;

private:
	void FinishCraft();

	void ClearAllCraft();

	void AddToQueue(const FCraftData& CraftData);
	void AddToQueue(TArrayView<const FCraftData> FCraftDatas);
};
