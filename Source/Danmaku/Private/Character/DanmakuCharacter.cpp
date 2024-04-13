// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacter.h"

#include "PaperFlipbook.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADanmakuCharacter::ADanmakuCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

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
	CameraSpringArm->bUsePawnControlRotation = true;
	CameraSpringArm->bInheritPitch = false;
	CameraSpringArm->bInheritRoll = false;
	CameraSpringArm->bInheritYaw = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	
	// Idle
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardIdleUp.WizardIdleUp'"));
	if (IdleUp.Succeeded())
	{
		AnimationFlipbooks.IdleUp = IdleUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardIdleDown.WizardIdleDown'"));
	if (IdleDown.Succeeded())
	{
		AnimationFlipbooks.IdleDown = IdleDown.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardIdleLeft.WizardIdleLeft'"));
	if (IdleLeft.Succeeded())
	{
		AnimationFlipbooks.IdleLeft = IdleLeft.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardIdleRight.WizardIdleRight'"));
	if (IdleRight.Succeeded())
	{
		AnimationFlipbooks.IdleRight = IdleRight.Object;
	}
	
	// Move
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardMoveUp.WizardMoveUp'"));
	if (MoveUp.Succeeded())
	{
		AnimationFlipbooks.MoveUp = MoveUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardMoveDown.WizardMoveDown'"));
	if (MoveDown.Succeeded())
	{
		AnimationFlipbooks.MoveDown = MoveDown.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardMoveLeft.WizardMoveLeft'"));
	if (MoveLeft.Succeeded())
	{
		AnimationFlipbooks.MoveLeft = MoveLeft.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Wizard/WizardMoveRight.WizardMoveRight'"));
	if (MoveRight.Succeeded())
	{
		AnimationFlipbooks.MoveRight = MoveRight.Object;
	}
}
