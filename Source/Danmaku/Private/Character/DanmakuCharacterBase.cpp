// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacterBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/DanmakuPlayerController.h"

ADanmakuCharacterBase::ADanmakuCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Directionality = FVector(1.f, 0.f, 0.f);
	
	// Capsule component
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	GetCapsuleComponent()->SetCapsuleRadius(25.f);

	// Sprite flipbook component
	GetSprite()->SetWorldScale3D(FVector(1.f, 1.f, 1.f / FMath::Cos(FMath::DegreesToRadians(45.f))));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SpriteMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_Sprite.MI_Sprite'"));
	if (SpriteMaterial.Succeeded())
	{
		GetSprite()->SetMaterial(0, SpriteMaterial.Object);
	}
	GetSprite()->SetRenderCustomDepth(true);
	GetSprite()->SetCustomDepthStencilValue(1);
	
	OnCharacterMovementUpdated.AddDynamic(this, &ADanmakuCharacterBase::Animate);
}

void ADanmakuCharacterBase::SetAnimationDirection(FVector Velocity, float CameraRotation)
{
	FRotator YawRotation(0.f, CameraRotation, 0.f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	float Forward = FVector::DotProduct(Velocity.GetSafeNormal(), ForwardDirection);
	float Right = FVector::DotProduct(Velocity.GetSafeNormal(), RightDirection);
	
	if (Forward != 0.f || Right != 0.f)
	{
		if (Forward > 0.f && fabs(Right) < 0.5f)
		{
			AnimationDirection = EAnimationDirection::Up;
		}
		else if (Forward < 0.f && fabs(Right) < 0.5f)
		{
			AnimationDirection = EAnimationDirection::Down;
		}
		else if (fabs(Forward) < 0.5f && Right < 0.f)
		{
			AnimationDirection = EAnimationDirection::Left;
		}
		else if (fabs(Forward) < 0.5f && Right > 0.f)
		{
			AnimationDirection = EAnimationDirection::Right;
		}
	}
}

void ADanmakuCharacterBase::Animate(float DeltaSeconds, FVector OldLocation, FVector OldVelocity)
{
	float CameraRotation = 0.f;
	if (UWorld* World = GetWorld())
	{
		if (ADanmakuPlayerController* PlayerController = Cast<ADanmakuPlayerController>(World->GetFirstPlayerController()))
		{
			CameraRotation = PlayerController->GetRotation();
			GetSprite()->SetWorldRotation(FRotator(0.f, CameraRotation + 90.f, -45.f));
			SetAnimationDirection(Directionality, CameraRotation);
		}
	}

	if (OldVelocity.Size() > 0.f)
	{
		Directionality = OldVelocity.GetSafeNormal();
	}
	
	SetAnimationDirection(OldVelocity, CameraRotation);

	if (OldVelocity.Size() > 0.f)
	{
		switch (AnimationDirection)
		{
		case EAnimationDirection::Up:
			GetSprite()->SetFlipbook(AnimationFlipbooks.MoveUp);
			break;
		case EAnimationDirection::Down:
			GetSprite()->SetFlipbook(AnimationFlipbooks.MoveDown);
			break;
		case EAnimationDirection::Left:
			GetSprite()->SetFlipbook(AnimationFlipbooks.MoveLeft);
			break;
		case EAnimationDirection::Right:
			GetSprite()->SetFlipbook(AnimationFlipbooks.MoveRight);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (AnimationDirection)
		{
		case EAnimationDirection::Up:
			GetSprite()->SetFlipbook(AnimationFlipbooks.IdleUp);
			break;
		case EAnimationDirection::Down:
			GetSprite()->SetFlipbook(AnimationFlipbooks.IdleDown);
			break;
		case EAnimationDirection::Left:
			GetSprite()->SetFlipbook(AnimationFlipbooks.IdleLeft);
			break;
		case EAnimationDirection::Right:
			GetSprite()->SetFlipbook(AnimationFlipbooks.IdleRight);
			break;
		default:
			break;
		}
	}
}

void ADanmakuCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}
