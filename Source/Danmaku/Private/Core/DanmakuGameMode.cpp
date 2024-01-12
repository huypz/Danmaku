// © 2024, Huy Phan. All rights reserved.


#include "Core/DanmakuGameMode.h"

#include "EngineUtils.h"
#include "Actor/DanmakuPlayerCharacter.h"
#include "Core/DanmakuGameState.h"
#include "Core/DanmakuPlayerController.h"
#include "GameFramework/GameSession.h"
#include "TileMap/TileGrid.h"

ADanmakuGameMode::ADanmakuGameMode()
{
	GameStateClass = ADanmakuGameState::StaticClass();
	PlayerControllerClass = ADanmakuPlayerController::StaticClass();
	DefaultPawnClass = ADanmakuPlayerCharacter::StaticClass();
}

void ADanmakuGameMode::InitGameState()
{
	Super::InitGameState();

	for (ATileGrid* Grid : TActorRange<ATileGrid>(GetWorld()))
	{
		TileGrid = Grid;
		break;
	}

	if (!TileGrid)
	{
		return;
	}

	TileGrid->Generate();
}

bool ADanmakuGameMode::ReadyToStartMatch_Implementation()
{
	// Check if clients have finished proc gen: We delay BeginPlay of world Actors until clients have finished proc gen
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (ADanmakuPlayerController* PC = Cast<ADanmakuPlayerController>(Iterator->Get()))
		{
			if (!PC->bClientFinishProceduralGeneration)
			{
				return false;
			}
		}
	}

	// If bDelayed Start is set, wait for a manual match start
	if (bDelayedStart)
	{
		return false;
	}

	// By default start when we have > 0 players
	if (GetMatchState() == MatchState::WaitingToStart)
	{
		if (NumPlayers + NumBots > 0)
		{
			return true;
		}
	}
	return false;
}

void ADanmakuGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	if (GameSession)
	{
		GameSession->HandleMatchIsWaitingToStart();
	}
}
