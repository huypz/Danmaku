// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
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
};

/**
 * 
 */
UCLASS(Abstract)
class DANMAKU_API ADanmakuCharacterBase : public APaperCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ADanmakuCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	FAnimationFlipbooks AnimationFlipbooks;

	EAnimationDirection AnimationDirection;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void PostInitializeComponents() override;

	void SetAnimationDirection(FVector Velocity, float CameraRotation);
	
	UFUNCTION()
	void Animate(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

private:
	FVector Directionality;
	
	void InitAbilityActorInfo();
};
