// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/DanmakuCharacterBase.h"
#include "DanmakuEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuEnemy : public ADanmakuCharacterBase
{
	GENERATED_BODY()

public:
	ADanmakuEnemy();

protected:
	virtual void BeginPlay() override;
};
