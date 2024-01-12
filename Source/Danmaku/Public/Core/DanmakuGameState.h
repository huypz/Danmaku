// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DanmakuGameState.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuGameState : public AGameState
{
	GENERATED_BODY()

public:
	void StartBeginPlay();

protected:
	virtual void OnRep_ReplicatedHasBegunPlay() override;
};
