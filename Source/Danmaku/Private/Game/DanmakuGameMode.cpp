// Copyright Huy Phan. All Rights Reserved.


#include "Game/DanmakuGameMode.h"

#include "EngineUtils.h"
#include "Character/DanmakuCharacter.h"
#include "Game/DanmakuGameState.h"
#include "GameFramework/GameSession.h"
#include "Player/DanmakuPlayerController.h"
#include "TileMap/TileGrid.h"
#include "UI/DanmakuHUD.h"

ADanmakuGameMode::ADanmakuGameMode()
{
	DefaultPawnClass = ADanmakuCharacter::StaticClass();
	GameStateClass = ADanmakuGameState::StaticClass();
	HUDClass = ADanmakuHUD::StaticClass();
	PlayerControllerClass = ADanmakuPlayerController::StaticClass();
}

bool ADanmakuGameMode::ReadyToStartMatch_Implementation()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (ADanmakuPlayerController* PC = Cast<ADanmakuPlayerController>(Iterator->Get()))
		{
			if (!PC->bClientFinishedProceduralGeneration)
			{
				return false;
			}
		}
	}

	if (bDelayedStart)
	{
		return false;
	}

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

void ADanmakuGameMode::InitGameState()
{
	Super::InitGameState();

	for (ATileGrid* Grid : TActorRange<ATileGrid>(GetWorld()))
	{
		TileGrid = Grid;
	}

	if (!TileGrid)
	{
		return;
	}

	TileGrid->Generate();
}
