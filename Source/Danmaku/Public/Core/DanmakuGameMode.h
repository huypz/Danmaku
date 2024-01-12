// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
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
	
	virtual void InitGameState() override;

protected:
	virtual bool ReadyToStartMatch_Implementation() override;

	virtual void HandleMatchIsWaitingToStart() override;

private:
	UPROPERTY()
	TObjectPtr<ATileGrid> TileGrid;
};
