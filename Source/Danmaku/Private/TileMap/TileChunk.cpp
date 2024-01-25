// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileChunk.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileFeature.h"
#include "TileMap/TileMetrics.h"


ATileChunk::ATileChunk()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Cells.SetNum(UTileMetrics::ChunkSizeX * UTileMetrics::ChunkSizeY);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	InstancedStaticMeshComponent->SetupAttachment(RootComponent);
	InstancedStaticMeshComponent->SetNumCustomDataFloats(7);
	InstancedStaticMeshComponent->SetCastShadow(false);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (Mesh.Succeeded())
	{
		InstancedStaticMeshComponent->SetStaticMesh(Mesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_Tile.MI_Tile'"));
	if (Material.Succeeded())
	{
		InstancedStaticMeshComponent->SetMaterial(0, Material.Object);
	}
}


void ATileChunk::TriangulateTile(UTileCell* Cell, const int32& Index)
{
	FTransform Transform(
		FRotator::ZeroRotator,
		FVector(Cell->Coordinates.X * 100.f + 50.f, Cell->Coordinates.Y * 100.f + 50.f, 0.f),
		FVector::OneVector
	);
	InstancedStaticMeshComponent->AddInstance(Transform, true);
	
	// TileTypeIndex 0
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		0,
		static_cast<float>(Cell->TileType)
	);
	// TileUTiling 1
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		1,
		1.f
	);
	// TileVTiling 2
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		2,
		1.f
	);
	// TileUOffset 3
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		3,
		0.f
	);
	// TileVOffset 4
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		4,
		0.f
	);
	// MaskTypeIndex 5
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		5,
		0.f
	);
	// MaskUTiling 6
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		6,
		1.f
	);
	// MaskVTiling 7
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		7,
		1.f
	);
}

void ATileChunk::TriangulateBlend(UTileCell* Cell, int32& Index)
{
	for (int32 DirectionIndex = 0; DirectionIndex < 12; DirectionIndex++)
	{
		FTileBlendParams TileBlendParams(Cell->Coordinates.X, Cell->Coordinates.Y, DirectionIndex, Cell);
		if (TileBlendParams.MaskTypeIndex == -1)
		{
			continue;
		}
		
		FTransform Transform(
			FRotator::ZeroRotator,
			TileBlendParams.Position,
			FVector(0.5f, 0.5f, 0.f)
		);
		InstancedStaticMeshComponent->AddInstance(Transform, true);
		Cell->IsBlendDrawn[DirectionIndex] = true;
		
		// TileTypeIndex 0
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			0,
			static_cast<float>(Cell->TileType)
		);
		// TileUTiling 1
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			1,
			0.5f
		);
		// TileVTiling 2
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			2,
			0.5f
		);
		// TileUOffset 3
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			3,
			TileBlendParams.TileUVOffset.X
		);
		// TileVOffset 4
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			4,
			TileBlendParams.TileUVOffset.Y
		);
		// MaskTypeIndex 5
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			5,
			TileBlendParams.MaskTypeIndex
		);
		// MaskRotation 6
		InstancedStaticMeshComponent->SetCustomDataValue(
			Index,
			6,
			TileBlendParams.MaskRotation
		);
		Index++;
	}
}

void ATileChunk::Triangulate()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Chunk refreshed"));
	}
	
	InstancedStaticMeshComponent->ClearInstances();
	for (ATileFeature* Feature : Features)
	{
		Feature->Destroy();
	}
	Features.Reset();

	int32 Index = 0;
	for (UTileCell* Cell : Cells)
	{
		TriangulateTile(Cell, Index++);
		// if (FMath::RandRange(0, 15) == 0)
		// {
		// 	AddFeature(FTileCoordinates::ToPosition(Cell->Coordinates));
		// }
	}
	for (UTileCell* Cell : Cells)
	{
		TriangulateBlend(Cell, Index);
	}
	
	InstancedStaticMeshComponent->SetTranslucentSortPriority(static_cast<int32>(Cells.Top()->TileType));
}

void ATileChunk::AddCell(int32 Index, UTileCell* Cell)
{
	Cells[Index] = Cell;
	Cell->Chunk = this;
}

void ATileChunk::AddFeature(const FVector& Position)
{
	ATileFeature* Feature = GetWorld()->SpawnActor<ATileFeature>(
		FVector(Position.X, Position.Y, 50.f),
		FRotator(0.f, 0.f, -90.f)
	);
	Features.Add(Feature);
}

void ATileChunk::Refresh()
{
	for (UTileCell* Cell : Cells)
	{
		for (bool& bIsBlendDrawn : Cell->IsBlendDrawn)
		{
			bIsBlendDrawn = false;
		}
	}
	SetActorTickEnabled(true);
}

void ATileChunk::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Triangulate();
	SetActorTickEnabled(false);
}
