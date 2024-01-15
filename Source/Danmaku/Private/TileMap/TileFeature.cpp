// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileFeature.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"

ATileFeature::ATileFeature()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCapsuleHalfHeight(50.f);
	CapsuleComponent->SetCapsuleRadius(25.f);
	CapsuleComponent->SetWorldRotation(FRotator(0.f, 0.f, -90.f));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Block);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetWorldScale3D(FVector(1.f, 1.f, 1.f + FMath::Cos(30.f)));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite(TEXT("/Script/Paper2D.PaperSprite'/Game/PaperAssets/Environment/S_Tree.S_Tree'"));
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

void ATileFeature::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector CurrentPosition = GetActorLocation();
	SpriteComponent->SetWorldLocation(FVector(CurrentPosition.X, CurrentPosition.Y, 100.f));
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
			SpriteComponent->SetWorldRotation(FRotator(0.f, PlayerController->GetControlRotation().Yaw + 90.f, -60.f));
		}
	}
}
