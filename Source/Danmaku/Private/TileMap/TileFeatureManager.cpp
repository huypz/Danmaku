// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileFeatureManager.h"

#include "TileMap/TileCell.h"
#include "TileMap/TileFeature.h"

UTileFeatureManager::UTileFeatureManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTileFeatureManager::Clear()
{
	for (ATileFeature* Feature : Features)
	{
		Feature->Destroy();
	}
	Features.Reset();
}

void UTileFeatureManager::Apply(TArray<UTileCell*> Cells)
{
	for (UTileCell* Cell : Cells)
	{
		SpawnFeature(Cell, Cell->GetFeatureClass());
	}
}

void UTileFeatureManager::SpawnFeature(UTileCell* Cell, TSubclassOf<ATileFeature> FeatureClass)
{
	if (FeatureClass == nullptr)
	{
		return;
	}

	const FTransform Transform(
	FRotator::ZeroRotator,
	FVector(Cell->Coordinates.X * 100.f + 50.f, Cell->Coordinates.Y * 100.f + 50.f, 0.f),
	FVector::OneVector
	);
	
	ATileFeature* Feature = GetWorld()->SpawnActor<ATileFeature>(FeatureClass, Transform);
	Features.Add(Feature);
}
