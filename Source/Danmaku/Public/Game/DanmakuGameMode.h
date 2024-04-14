// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "DanmakuGameMode.generated.h"

class ATileGrid;

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ADanmakuGameMode();

private:
	UPROPERTY()
	TObjectPtr<ATileGrid> TileGrid;

	virtual bool ReadyToStartMatch_Implementation() override;

	virtual void HandleMatchIsWaitingToStart() override;
	
	virtual void InitGameState() override;

};
