// Copyright Huy Phan. All Rights Reserved.


#include "Character/DanmakuCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
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
	GetCapsuleComponent()->SetCapsuleRadius(25.f);

	// Sprite flipbook component
	GetSprite()->SetTranslucentSortPriority(INT32_MAX);
	static ConstructorHelpers::FObjectFinder<UMaterial> SpriteMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/M_Sprite.M_Sprite'"));
	if (SpriteMaterial.Succeeded())
	{
		DynamicSpriteMaterial = UMaterialInstanceDynamic::Create(SpriteMaterial.Object, nullptr);
		GetSprite()->SetMaterial(0, DynamicSpriteMaterial);
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
			SetAnimationDirection(Directionality, PlayerController->CameraRotation);
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

	int32 CurrentAnimationFrame = GetSprite()->GetPlaybackPositionInFrames();
	if (UPaperSprite* CurrentSprite = GetSprite()->GetFlipbook()->GetSpriteAtFrame(CurrentAnimationFrame))
	{
		UTexture2D* CurrentTexture = CurrentSprite->GetBakedTexture();
		DynamicSpriteMaterial->SetTextureParameterValue(FName("SpriteTexture"), CurrentTexture);
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

void ADanmakuCharacterBase::UpdateRotation_Implementation(FVector CameraLocation, float Rotation)
{
	IDanmakuActorInterface::UpdateRotation_Implementation(CameraLocation, Rotation);

	float Yaw = FMath::DegreesToRadians(Rotation);
	FVector SortAxis = FVector(FMath::Cos(Yaw), FMath::Sin(Yaw), 0.f);
	FVector DistanceFromCamera = CameraLocation - GetActorLocation();
	int32 SortPriority = FVector::DotProduct(DistanceFromCamera, SortAxis);

	if (UPaperFlipbookComponent* CurrentSprite = GetSprite())
	{
		CurrentSprite->SetTranslucentSortPriority(SortPriority);
		CurrentSprite->SetWorldRotation(FRotator(0.f, Rotation + 90.f, -90.f));
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
