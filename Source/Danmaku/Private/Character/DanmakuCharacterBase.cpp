// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacterBase.h"

#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"

ADanmakuCharacterBase::ADanmakuCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// Capsule component
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	GetCapsuleComponent()->SetCapsuleRadius(25.f);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);

	// Sprite flipbook component
	GetSprite()->SetWorldScale3D(FVector(1.f, 1.f, 1.f + FMath::Cos(30.f)));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SpriteMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_Sprite.MI_Sprite'"));
	if (SpriteMaterial.Succeeded())
	{
		GetSprite()->SetMaterial(0, SpriteMaterial.Object);
	}
	
	OnCharacterMovementUpdated.AddDynamic(this, &ADanmakuCharacterBase::Animate);
}

void ADanmakuCharacterBase::SetAnimationDirection(FVector Velocity)
{
	FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
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
	SetAnimationDirection(OldVelocity);

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
	
	GetSprite()->SetWorldRotation(FRotator(0.f, GetController()->GetControlRotation().Yaw + 90.f, -60.f));
}
