// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DanmakuPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADanmakuPlayerController();

	float GetRotation();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;

private:
	float RotationInput;
	
	float RotationSpeed;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY()
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY()
	TObjectPtr<UInputAction> RotateAction;
	
	void Move(const FInputActionValue& Value);
	
	void Rotate(const FInputActionValue& Value);
};
