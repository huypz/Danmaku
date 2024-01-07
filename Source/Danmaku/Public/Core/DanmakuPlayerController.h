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
	float CameraYaw;
	
	ADanmakuPlayerController();

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

private:
	TObjectPtr<UInputMappingContext> DefaultContext;
	
	TObjectPtr<UInputAction> MoveAction;
	
	TObjectPtr<UInputAction> RotateAction;
	
	void Move(const FInputActionValue& Value);
	
	void Rotate(const FInputActionValue& Value);
};
