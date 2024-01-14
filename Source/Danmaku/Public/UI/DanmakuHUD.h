// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DanmakuHUD.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
