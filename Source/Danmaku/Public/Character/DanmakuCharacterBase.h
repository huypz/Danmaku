// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
#include "Actor/DanmakuActorInterface.h"
#include "DanmakuCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UPaperFlipbook;

UENUM()
enum class EAnimationDirection : uint8
{
	Up,
	Down,
	Left,
	Right,
};

USTRUCT()
struct DANMAKU_API FAnimationFlipbooks
{
	GENERATED_BODY()

	// Idle

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> IdleUp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> IdleDown;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> IdleLeft;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> IdleRight;

	// Move

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> MoveUp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> MoveDown;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> MoveLeft;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> MoveRight;

	// Attack

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> AttackUp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> AttackDown;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> AttackLeft;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> AttackRight;
};

/**
 * 
 */
UCLASS(Abstract)
class DANMAKU_API ADanmakuCharacterBase : public APaperCharacter, public IDanmakuActorInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ADanmakuCharacterBase();

	void SetSpriteSize(float Value);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	
protected:
	UPROPERTY(EditAnywhere)
	FAnimationFlipbooks AnimationFlipbooks;

	EAnimationDirection AnimationDirection;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void PostInitializeComponents() override;

	virtual void UpdateRotation_Implementation(FVector CameraLocation, float Rotation) override;

	void SetAnimationDirection(FVector Velocity, float CameraRotation);
	
	UFUNCTION()
	void Animate(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> Material;
	
	FVector Directionality;
	
	void InitAbilityActorInfo();
};
