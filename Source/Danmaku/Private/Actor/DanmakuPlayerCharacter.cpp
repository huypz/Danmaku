// © 2024, Huy Phan. All rights reserved.


#include "Actor/DanmakuPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADanmakuPlayerCharacter::ADanmakuPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->bEnableCameraLag = false;
	CameraSpringArm->bEnableCameraRotationLag = false;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->bUsePawnControlRotation = false;
	CameraSpringArm->bInheritPitch = false;
	CameraSpringArm->bInheritRoll = false;
	CameraSpringArm->bInheritYaw = false;
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->SetOrthoWidth(2400.f);
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

void ADanmakuPlayerCharacter::SetCameraRotation(float Rotation)
{
	CameraSpringArm->SetWorldRotation(FRotator(-90.f, Rotation, 0.f));
}
