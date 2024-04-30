// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DanmakuCharacterBase.h"
#include "DanmakuCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTileMapEditorHUD;

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuCharacter : public ADanmakuCharacterBase
{
	GENERATED_BODY()

public:
	ADanmakuCharacter();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	

protected:
	virtual void UpdateRotation_Implementation(FVector CameraLocation, float Rotation) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	/*
	 * HUD
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTileMapEditorHUD> TileMapEditorHUDClass;

	UPROPERTY()
	TObjectPtr<UTileMapEditorHUD> TileMapEditorHUD;
};
