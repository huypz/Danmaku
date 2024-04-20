// Copyright Huy Phan. All Rights Reserved.

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
	bool bClientFinishedProceduralGeneration;
	
	ADanmakuPlayerController();

	FMatrix GetCameraProjectionMatrix();

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY()
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY()
	TObjectPtr<UInputAction> RotateAction;

	void Move(const FInputActionValue& InputActionValue);
	
	void Rotate(const FInputActionValue& InputActionValue);

	UFUNCTION(Server, Reliable)
	void ServerClientFinishedProcGen();

	UFUNCTION(Server, Reliable)
	void ServerRequestProcGenData();

	UFUNCTION(Client, Reliable)
	void ClientReceiveProcGenData();

	virtual void PostNetInit() override;

	virtual void PostInitializeComponents() override;
};
