// Copyright Huy Phan. All Rights Reserved.


#include "Character/Enemy/Pirate.h"

#include "PaperFlipbook.h"

APirate::APirate()
{
	// Idle
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateIdleLeft.PirateIdleLeft'"));
	if (IdleUp.Succeeded())
	{
		AnimationFlipbooks.IdleUp = IdleUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateIdleRight.PirateIdleRight'"));
	if (IdleDown.Succeeded())
	{
		AnimationFlipbooks.IdleDown = IdleDown.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateIdleLeft.PirateIdleLeft'"));
	if (IdleLeft.Succeeded())
	{
		AnimationFlipbooks.IdleLeft = IdleLeft.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> IdleRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateIdleRight.PirateIdleRight'"));
	if (IdleRight.Succeeded())
	{
		AnimationFlipbooks.IdleRight = IdleRight.Object;
	}
	
	// Move
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveUp(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateMoveLeft.PirateMoveLeft'"));
	if (MoveUp.Succeeded())
	{
		AnimationFlipbooks.MoveUp = MoveUp.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveDown(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateMoveRight.PirateMoveRight'"));
	if (MoveDown.Succeeded())
	{
		AnimationFlipbooks.MoveDown = MoveDown.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveLeft(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateMoveLeft.PirateMoveLeft'"));
	if (MoveLeft.Succeeded())
	{
		AnimationFlipbooks.MoveLeft = MoveLeft.Object;
	}
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> MoveRight(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Characters/Pirate/PirateMoveRight.PirateMoveRight'"));
	if (MoveRight.Succeeded())
	{
		AnimationFlipbooks.MoveRight = MoveRight.Object;
	}
}
