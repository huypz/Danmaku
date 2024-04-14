// Copyright Huy Phan. All Rights Reserved.


#include "Game/DanmakuGameState.h"

#include "Player/DanmakuPlayerController.h"

void ADanmakuGameState::StartBeginPlay()
{
	ADanmakuPlayerController* PlayerController = Cast<ADanmakuPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController &&
		PlayerController->bClientFinishedProceduralGeneration &&
		bReplicatedHasBegunPlay &&
		GetLocalRole() != ENetRole::ROLE_Authority)
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
