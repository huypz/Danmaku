// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileFeature.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"

ATileFeature::ATileFeature()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCapsuleHalfHeight(50.f);
	CapsuleComponent->SetCapsuleRadius(20.f);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Block);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetTranslucentSortPriority(INT32_MAX);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite(TEXT("/Script/Paper2D.PaperSprite'/Game/Textures/Environment/Object/T_Tree_Sprite.T_Tree_Sprite'"));
	if (Sprite.Succeeded())
	{
		SpriteComponent->SetSprite(Sprite.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SpriteMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_Sprite.MI_Sprite'"));
	if (SpriteMaterial.Succeeded())
	{
		SpriteComponent->SetMaterial(0, SpriteMaterial.Object);
	}
}

void ATileFeature::SetSpriteSize(float Size)
{
	//SpriteComponent->SetWorldScale3D(FVector(Size, 1.f, Size / FMath::Cos(FMath::DegreesToRadians(45.f))));
}

void ATileFeature::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController())
		{
			if (APawn* LocalPawn = PlayerController->GetPawn())
			{
				FVector CurrentPosition = GetActorLocation();
				SpriteComponent->SetWorldLocation(FVector(CurrentPosition.X, CurrentPosition.Y, LocalPawn->GetActorLocation().Z));
			}
			SpriteComponent->SetWorldRotation(FRotator(0.f, FMath::RoundToFloat(PlayerController->GetControlRotation().Yaw + 90.f), -90.f));
		}
	}
}
