// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "DanmakuCharacterBase.generated.h"

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
UCLASS()
class DANMAKU_API ADanmakuCharacterBase : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	ADanmakuCharacterBase();
	
protected:
	UPROPERTY(VisibleAnywhere)
	FAnimationFlipbooks AnimationFlipbooks;

	EAnimationDirection AnimationDirection;

	void SetAnimationDirection(FVector Velocity);
	
	UFUNCTION()
	void Animate(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);
};
