// Fill out your copyright notice in the Description page of Project Settings.


#include "FCraftQueue.h"
#include "Data/CraftTypes.h"


FCraftQueue::FCraftQueue(UWorld* World, TFunction<void(const FPrimaryAssetId&)>&& InFinishCraftCallback,
                         const int32 InMaxNumberCraft)
	: CurrentWorld(World), FinishCraftCallback(MoveTemp(InFinishCraftCallback)),
	  MaxNumberCraft(FMath::Max(InMaxNumberCraft, 1))
{
	if (CurrentWorld.IsValid() && IsValid(CurrentWorld.Get()))
	{
		TimerManager = &CurrentWorld->GetTimerManager();
	}
}

FCraftQueue::~FCraftQueue()
{
	ClearAllCraft();
}


void FCraftQueue::AddToQueue(const FCraftData& CraftData)
{
	if (CraftData.IsValid())
	{
		Queue.AddTail(CraftData);
	}
}

void FCraftQueue::AddToQueue(TArrayView<const FCraftData> FCraftDatas)
{
	for (const FCraftData& PrimaryAssetID : FCraftDatas)
	{
		AddToQueue(PrimaryAssetID);
	}
}

void FCraftQueue::ClearAllCraft()
{
	if (CurrentWorld.IsValid() && TimerManager.IsSet())
	{
		for (auto& Pair : RunningCrafts)
		{
			TimerManager.GetValue()->ClearTimer(Pair.Key);
		}

		RunningCrafts.Reset();
	}
}

void FCraftQueue::SetMaxNumberCraft(const int32 NewMaxNumberCraft)
{
	MaxNumberCraft = FMath::Max(1, NewMaxNumberCraft);
}

bool FCraftQueue::Craft(const FCraftData& CraftData)
{
	if (CurrentWorld.IsValid() && TimerManager.IsSet() && CraftData.IsValid())
	{
		const int32 NumberCanCraft = FMath::Max(MaxNumberCraft - RunningCrafts.Num(), 0);
		if (NumberCanCraft > 0)
		{
			FTimerHandle NewTimerHandle;
			TimerManager.GetValue()->SetTimer(NewTimerHandle, std::bind(&FCraftQueue::FinishCraft, this),
			                                  CraftData.TimeOfCreation, false, -1.f);
			if (NewTimerHandle.IsValid())
			{
				RunningCrafts.Add(NewTimerHandle, {CraftData.ItemID, CraftData.Count});

				return true;
			}
		}
		else
		{
			AddToQueue(CraftData);
			return true;
		}
	}

	return false;
}

bool FCraftQueue::Craft(const FCraftData& CraftData, const FCraftDynamicDelegate& InDelegate)
{
	bool bResult = false;
	if (CurrentWorld.IsValid() && TimerManager.IsSet() && CraftData.IsValid())
	{
		const int32 NumberCanCraft = FMath::Max(MaxNumberCraft - RunningCrafts.Num(), 0);
		if (NumberCanCraft > 0)
		{
			FTimerHandle NewTimerHandle;
			TimerManager.GetValue()->SetTimer(NewTimerHandle, std::bind(&FCraftQueue::FinishCraft, this),
											CraftData.TimeOfCreation, false, -1.f);
			if (NewTimerHandle.IsValid())
			{
				RunningCrafts.Add(NewTimerHandle, {CraftData.ItemID, CraftData.Count, InDelegate});

				bResult = true;
			}
		}
		/*else
		{
			AddToQueue(CraftData);
			bResult = true;
		}*/
	}

	InDelegate.ExecuteIfBound(bResult ? ECraftStatus::Processing : ECraftStatus::Failed);

	return bResult;
}

const TMap<FTimerHandle, FRunningCraftData>& FCraftQueue::GetCurrentCrafts() const
{
	return RunningCrafts;
}

void FCraftQueue::FinishCraft()
{
	for (const auto& CurrentCraft : RunningCrafts)
	{
		if (TimerManager.GetValue()->GetTimerRemaining(CurrentCraft.Key) <= 0.f)
		{
			FinishCraftCallback(CurrentCraft.Value.ItemId);
			CurrentCraft.Value.DynamicDelegate.ExecuteIfBound(ECraftStatus::Success);

			RunningCrafts.Remove(CurrentCraft.Key);
			RunningCrafts.CompactStable();

			break;
		}
	}
	/*if (const auto* Head = Queue.GetHead())
	{
		const FCraftData& NewCraftData = Head->GetValue();
		Craft({NewCraftData});
		Queue.RemoveNode(Queue.GetHead());
	}*/
}
