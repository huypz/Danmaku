// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacter.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADanmakuCharacter::ADanmakuCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	GetCapsuleComponent()->SetCapsuleRadius(25.f);
	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeLocation(FVector(0.f, -25.f, 0.f));
	CameraSpringArm->TargetArmLength = 1000.f;
	CameraSpringArm->bEnableCameraLag = false;
	CameraSpringArm->bEnableCameraRotationLag = false;
	CameraSpringArm->bDoCollisionTest = false;
	CameraSpringArm->bUsePawnControlRotation = true;
	CameraSpringArm->bInheritPitch = false;
	CameraSpringArm->bInheritRoll = false;
	CameraSpringArm->bInheritYaw = true;
	CameraSpringArm->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->SetOrthoWidth(2800.f);
	Camera->PostProcessSettings.bOverride_AutoExposureBias = 1;
	Camera->PostProcessSettings.AutoExposureBias = 0.f;
	Camera->PostProcessSettings.bOverride_AutoExposureMinBrightness = 1;
	Camera->PostProcessSettings.AutoExposureMinBrightness = 1.f;
	Camera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = 1;
	Camera->PostProcessSettings.AutoExposureMaxBrightness = 1.f;
	Camera->PostProcessSettings.bOverride_ToneCurveAmount = 1;
	Camera->PostProcessSettings.ToneCurveAmount = 0.f;

	// Idle
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardIdleUp.FB_WizardIdleUp'"));
	if (IdleUp.Succeeded())
	{
		AnimationFlipbooks.IdleUp = IdleUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardIdleDown.FB_WizardIdleDown'"));
	if (IdleDown.Succeeded())
	{
		AnimationFlipbooks.IdleDown = IdleDown.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardIdleLeft.FB_WizardIdleLeft'"));
	if (IdleLeft.Succeeded())
	{
		AnimationFlipbooks.IdleLeft = IdleLeft.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardIdleRight.FB_WizardIdleRight'"));
	if (IdleRight.Succeeded())
	{
		AnimationFlipbooks.IdleRight = IdleRight.Object;
	}
	
	// Move
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardMoveUp.FB_WizardMoveUp'"));
	if (MoveUp.Succeeded())
	{
		AnimationFlipbooks.MoveUp = MoveUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardMoveDown.FB_WizardMoveDown'"));
	if (MoveDown.Succeeded())
	{
		AnimationFlipbooks.MoveDown = MoveDown.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardMoveLeft.FB_WizardMoveLeft'"));
	if (MoveLeft.Succeeded())
	{
		AnimationFlipbooks.MoveLeft = MoveLeft.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/PaperAssets/Character/Wizard/FB_WizardMoveRight.FB_WizardMoveRight'"));
	if (MoveRight.Succeeded())
	{
		AnimationFlipbooks.MoveRight = MoveRight.Object;
	}
}
