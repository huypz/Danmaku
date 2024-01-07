// © 2024, Huy Phan. All rights reserved.


#include "Actors/DanmakuPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADanmakuPlayerCharacter::ADanmakuPlayerCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
	
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComponent->TargetArmLength = 1000.f;
	CameraSpringArmComponent->bEnableCameraLag = false;
	CameraSpringArmComponent->bEnableCameraRotationLag = false;
	CameraSpringArmComponent->bDoCollisionTest = false;
	CameraSpringArmComponent->bUsePawnControlRotation = false;
	CameraSpringArmComponent->bInheritPitch = false;
	CameraSpringArmComponent->bInheritRoll = false;
	CameraSpringArmComponent->bInheritYaw = false;
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	CameraSpringArmComponent->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->SetOrthoWidth(1600.f);
	CameraComponent->SetupAttachment(CameraSpringArmComponent, USpringArmComponent::SocketName);
}

void ADanmakuPlayerCharacter::SetCameraRotation(float Rotation)
{
	CameraSpringArmComponent->SetWorldRotation(FRotator(-90.f, Rotation, 0.f));
}
