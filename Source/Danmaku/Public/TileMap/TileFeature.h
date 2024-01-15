// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileFeature.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

/**
 * 
 */
UCLASS()
class DANMAKU_API ATileFeature : public AActor
{
	GENERATED_BODY()

public:
	ATileFeature();

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;
};
