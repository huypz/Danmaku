// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/DanmakuPlayerController.h"
#include "Player/DanmakuPlayerState.h"

ADanmakuCharacterBase::ADanmakuCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Directionality = FVector::ForwardVector;
	
	// Capsule component
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	GetCapsuleComponent()->SetCapsuleRadius(50.f);

	// Sprite flipbook component
	GetSprite()->SetTranslucentSortPriority(10000);
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SpriteMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_Sprite.MI_Sprite'"));
	if (SpriteMaterial.Succeeded())
	{
		GetSprite()->SetMaterial(0, SpriteMaterial.Object);
	}
	
	OnCharacterMovementUpdated.AddDynamic(this, &ADanmakuCharacterBase::Animate);
}

UAbilitySystemComponent* ADanmakuCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ADanmakuCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
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
	if (UWorld* World = GetWorld())
	{
		if (ADanmakuPlayerController* PlayerController = Cast<ADanmakuPlayerController>(World->GetFirstPlayerController()))
		{
			float CameraRotation = PlayerController->GetControlRotation().Yaw;
			SetAnimationDirection(Directionality, CameraRotation);
		}
	}
	
	if (OldVelocity.Size() > 0.f)
	{
		Directionality = OldVelocity.GetSafeNormal();
	}
	
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

void ADanmakuCharacterBase::InitAbilityActorInfo()
{
	if (ADanmakuPlayerState* DanmakuPlayerState = GetPlayerState<ADanmakuPlayerState>())
	{
		AbilitySystemComponent = DanmakuPlayerState->GetAbilitySystemComponent();
		AttributeSet = DanmakuPlayerState->GetAttributeSet();

		AbilitySystemComponent->InitAbilityActorInfo(DanmakuPlayerState, this);
	}
}

void ADanmakuCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ADanmakuCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}
