// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/DanmakuPlayerController.h"
#include "UI/TileMapEditorHUD.h"

ADanmakuCharacter::ADanmakuCharacter()
{
	TileMapEditorHUDClass = nullptr;
	TileMapEditorHUD = nullptr;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->bEnableCameraLag = false;
	CameraSpringArm->bEnableCameraRotationLag = false;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->bInheritPitch = false;
	CameraSpringArm->bInheritRoll = false;
	CameraSpringArm->bInheritYaw = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
}

void ADanmakuCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && TileMapEditorHUDClass)
	{
		if (ADanmakuPlayerController* DPC = GetController<ADanmakuPlayerController>())
		{
			TileMapEditorHUD = CreateWidget<UTileMapEditorHUD>(DPC, TileMapEditorHUDClass);
			TileMapEditorHUD->AddToPlayerScreen();
		}
	}
}

void ADanmakuCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TileMapEditorHUD)
	{
		TileMapEditorHUD->RemoveFromParent();
		TileMapEditorHUD = nullptr;
	}
	
	Super::EndPlay(EndPlayReason);
}

void ADanmakuCharacter::UpdateRotation_Implementation(FVector CameraLocation, float Rotation)
{
	Super::UpdateRotation_Implementation(CameraLocation, Rotation);
	
	if (CameraSpringArm)
	{
		CameraSpringArm->SetWorldRotation(FRotator(-90.f, Rotation, 0.f));
	}
}
