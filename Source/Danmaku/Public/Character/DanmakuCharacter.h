// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DanmakuCharacterBase.h"
#include "DanmakuCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuCharacter : public ADanmakuCharacterBase
{
	GENERATED_BODY()

public:
	ADanmakuCharacter();

protected:
	virtual void UpdateRotation_Implementation(FVector CameraLocation, float Rotation) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;
};
