// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/DanmakuData.h"
#include "PaperCharacter.h"
#include "DanmakuCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuCharacterBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	ADanmakuCharacterBase();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	FAnimationFlipbooks AnimationFlipbooks;

	EAnimationDirection AnimationDirection;

	bool bIsMoving;

	void SetAnimationDirection(FVector Velocity, float CameraYaw);
	
	UFUNCTION()
	void Animate(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);
};
