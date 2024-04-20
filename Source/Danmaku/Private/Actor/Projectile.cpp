// Copyright Huy Phan. All Rights Reserved.


#include "Actor/Projectile.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/SphereComponent.h"
#include "Player/DanmakuPlayerController.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(RootComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("FlipbookComponent");
	FlipbookComponent->SetupAttachment(RootComponent);
	FlipbookComponent->SetWorldRotation(FRotator(0.f, 0.f, -90.f));

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> Flipbook(TEXT("/Script/Paper2D.PaperFlipbook'/Game/Textures/Projectiles/MagicMissileRed_Flipbook.MagicMissileRed_Flipbook'"));
	if (Flipbook.Succeeded())
	{
		FlipbookComponent->SetFlipbook(Flipbook.Object);
	}
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}
