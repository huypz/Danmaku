// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
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

	float CameraRotation;

protected:
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;
	
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialParameterCollection> MPC;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> AttackAction;

	void Move(const FInputActionValue& InputActionValue);
	
	void Rotate(const FInputActionValue& InputActionValue);

	void Attack(const FInputActionValue& InputActionValue);
	
	UFUNCTION(Server, Reliable)
	void ServerClientFinishedProcGen();

	UFUNCTION(Server, Reliable)
	void ServerRequestProcGenData();

	UFUNCTION(Client, Reliable)
	void ClientReceiveProcGenData();

	virtual void PostNetInit() override;

	virtual void PostInitializeComponents() override;
};
