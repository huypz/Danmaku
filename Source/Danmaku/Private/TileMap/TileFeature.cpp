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
	SpriteComponent->SetRelativeLocation(FVector(0.f, -50.f, 0.f));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> Sprite(TEXT("/Script/Paper2D.PaperSprite'/Game/PaperAssets/Environment/S_Tree.S_Tree'"));
	if (Sprite.Succeeded())
	{
		SpriteComponent->SetSprite(Sprite.Object);
	}
	SpriteComponent->SetTranslucentSortPriority(10000);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> SpriteMaterial(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_Sprite.MI_Sprite'"));
	if (SpriteMaterial.Succeeded())
	{
		SpriteComponent->SetMaterial(0, SpriteMaterial.Object);
	}
}

void ATileFeature::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float Yaw = 0.f;
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController())
		{
			Yaw = PlayerController->GetControlRotation().Yaw;
		}
	}
	SpriteComponent->SetWorldRotation(FRotator(0.f, Yaw + 90.f, -90.f));

	SetActorTickEnabled(false);
}
