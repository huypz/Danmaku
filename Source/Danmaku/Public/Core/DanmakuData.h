// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "DanmakuData.generated.h"

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
