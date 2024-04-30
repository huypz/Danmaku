// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileFeature.h"

ATileFeature::ATileFeature()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}
}
