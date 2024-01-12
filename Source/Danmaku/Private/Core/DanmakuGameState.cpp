// © 2024, Huy Phan. All rights reserved.


#include "Core/DanmakuGameState.h"

#include "Core/DanmakuPlayerController.h"

void ADanmakuGameState::StartBeginPlay()
{
	ADanmakuPlayerController* PC = Cast<ADanmakuPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PC && PC->bClientFinishProceduralGeneration && bReplicatedHasBegunPlay && GetLocalRole() != ENetRole::ROLE_Authority)
	{
		GetWorldSettings()->NotifyBeginPlay();
		GetWorldSettings()->NotifyMatchStarted();
	}
}

void ADanmakuGameState::OnRep_ReplicatedHasBegunPlay()
{
	Super::OnRep_ReplicatedHasBegunPlay();

	StartBeginPlay();
}
