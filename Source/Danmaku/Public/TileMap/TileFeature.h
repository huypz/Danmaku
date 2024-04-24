// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/DanmakuActorInterface.h"
#include "GameFramework/Actor.h"
#include "TileFeature.generated.h"

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

	void SetSpriteSize(float Size);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;

	virtual void UpdateRotation_Implementation(FVector CameraLocation, float Rotation) override;
};
