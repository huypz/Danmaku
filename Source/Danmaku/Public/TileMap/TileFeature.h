// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/DanmakuActorInterface.h"
#include "GameFramework/Actor.h"
#include "TileFeature.generated.h"

class UBoxComponent;
class UCapsuleComponent;
class UPaperSpriteComponent;

/**
 * 
 */
UCLASS()
class DANMAKU_API ATileFeature : public AActor, public IDanmakuActorInterface
{
	GENERATED_BODY()

public:
	ATileFeature();

private:
	
};
