// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "DanmakuGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UDanmakuGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

public:
	virtual void Activated(FViewport* InViewport, const FWindowActivateEvent& InActivateEvent) override;
};