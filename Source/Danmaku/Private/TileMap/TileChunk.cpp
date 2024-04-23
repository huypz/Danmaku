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

	bNetStartup = true;

	Cells.SetNum(UTileMetrics::ChunkSizeX * UTileMetrics::ChunkSizeY);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	
	InstancedStaticMeshComponent->SetupAttachment(RootComponent);
	InstancedStaticMeshComponent->SetNumCustomDataFloats(9);
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
	const FTransform Transform(
		FRotator::ZeroRotator,
		FVector(Cell->Coordinates.X * 100.f + 50.f, Cell->Coordinates.Y * 100.f + 50.f, 0.f),
		FVector::OneVector
	);
	InstancedStaticMeshComponent->AddInstance(Transform, true);

	// Tile
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		0,
		static_cast<float>(Cell->TileType)
	);
	
	// Quadrant 1
	ETileType TileTypeIndex1 = Cell->TileType;
	int32 MaskTypeIndex1 = MASK_DEFAULT_1;
	if (Cell->GetNeighbor(ETileDirection::North) || Cell->GetNeighbor(ETileDirection::West))
	{
		UTileCell* N = Cell->GetNeighbor(ETileDirection::North);
		UTileCell* W = Cell->GetNeighbor(ETileDirection::West);
		if (!N || (W && N->TileType < W->TileType))
		{
			TileTypeIndex1 = FMath::Max(Cell->TileType, W->TileType);
			MaskTypeIndex1 = Cell->TileType < W->TileType ? MASK_SIDE_LEFT_1 : MASK_DEFAULT_1;
		}
		else if (!W || (N && N->TileType > W->TileType))
		{
			TileTypeIndex1 = FMath::Max(Cell->TileType, N->TileType);
			MaskTypeIndex1 = Cell->TileType < N->TileType ? MASK_SIDE_TOP_1 : MASK_DEFAULT_1;
		}
		else if (Cell->TileType < N->TileType || Cell->TileType < W->TileType)
		{
			TileTypeIndex1 = N->TileType;
			MaskTypeIndex1 = MASK_INNER_1;
		}
		else if (UTileCell* NW = Cell->GetNeighbor(ETileDirection::NorthWest); NW && Cell->TileType < NW->TileType)
		{
			TileTypeIndex1 = NW->TileType;
			MaskTypeIndex1 = MASK_OUTER_1;
		}
		else
		{
			TileTypeIndex1 = Cell->TileType;
			MaskTypeIndex1 = MASK_DEFAULT_1;
		}
	}
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		1,
		static_cast<float>(TileTypeIndex1)
	);
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		2,
		static_cast<float>(MaskTypeIndex1)
	);
	// Quadrant 2
	ETileType TileTypeIndex2 = Cell->TileType;
	int32 MaskTypeIndex2 = MASK_DEFAULT_2;
	if (Cell->GetNeighbor(ETileDirection::North) || Cell->GetNeighbor(ETileDirection::East))
	{
		UTileCell* N = Cell->GetNeighbor(ETileDirection::North);
		UTileCell* E = Cell->GetNeighbor(ETileDirection::East);
		if (!N || (E && N->TileType < E->TileType))
		{
			TileTypeIndex2 = FMath::Max(Cell->TileType, E->TileType);
			MaskTypeIndex2 = Cell->TileType < E->TileType ? MASK_SIDE_RIGHT_2 : MASK_DEFAULT_2;
		}
		else if (!E || (N && N->TileType > E->TileType))
		{
			TileTypeIndex2 = FMath::Max(Cell->TileType, N->TileType);
			MaskTypeIndex2 = Cell->TileType < N->TileType ? MASK_SIDE_TOP_2 : MASK_DEFAULT_2;
		}
		else if (Cell->TileType < N->TileType || Cell->TileType < E->TileType)
		{
			TileTypeIndex2 = N->TileType;
			MaskTypeIndex2 = MASK_INNER_2;
		}
		else if (UTileCell* NE = Cell->GetNeighbor(ETileDirection::NorthEast); NE && Cell->TileType < NE->TileType)
		{
			TileTypeIndex2 = NE->TileType;
			MaskTypeIndex2 = MASK_OUTER_2;
		}
		else
		{
			TileTypeIndex2 = Cell->TileType;
			MaskTypeIndex2 = MASK_DEFAULT_2;
		}
	}
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		3,
		static_cast<float>(TileTypeIndex2)
	);
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		4,
		static_cast<float>(MaskTypeIndex2)
	);
	// Quadrant 3
	ETileType TileTypeIndex3 = Cell->TileType;
	int32 MaskTypeIndex3 = MASK_DEFAULT_3;
	if (Cell->GetNeighbor(ETileDirection::South) || Cell->GetNeighbor(ETileDirection::West))
	{
		UTileCell* S = Cell->GetNeighbor(ETileDirection::South);
		UTileCell* W = Cell->GetNeighbor(ETileDirection::West);
		if (!S || (W && S->TileType < W->TileType))
		{
			TileTypeIndex3 = FMath::Max(Cell->TileType, W->TileType);
			MaskTypeIndex3 = Cell->TileType < W->TileType ? MASK_SIDE_LEFT_3 : MASK_DEFAULT_3;
		}
		else if (!W || (S && S->TileType > W->TileType))
		{
			TileTypeIndex3 = FMath::Max(Cell->TileType, S->TileType);
			MaskTypeIndex3 = Cell->TileType < S->TileType ? MASK_SIDE_BOTTOM_3 : MASK_DEFAULT_3;
		}
		else if (Cell->TileType < W->TileType || Cell->TileType < S->TileType)
		{
			TileTypeIndex3 = W->TileType;
			MaskTypeIndex3 = MASK_INNER_3;
		}
		else if (UTileCell* SW = Cell->GetNeighbor(ETileDirection::SouthWest); SW && Cell->TileType < SW->TileType)
		{
			TileTypeIndex3 = SW->TileType;
			MaskTypeIndex3 = MASK_OUTER_3;
		}
		else
		{
			TileTypeIndex3 = Cell->TileType;
			MaskTypeIndex3 = MASK_DEFAULT_3;
		}
	}
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		5,
		static_cast<float>(TileTypeIndex3)
	);
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		6,
		static_cast<float>(MaskTypeIndex3)
	);
	// Quadrant 4
	ETileType TileTypeIndex4 = Cell->TileType;
	int32 MaskTypeIndex4 = MASK_DEFAULT_4;
	if (Cell->GetNeighbor(ETileDirection::South) || Cell->GetNeighbor(ETileDirection::East))
	{
		UTileCell* S = Cell->GetNeighbor(ETileDirection::South);
		UTileCell* E = Cell->GetNeighbor(ETileDirection::East);
		if (!S || (E && S->TileType < E->TileType))
		{
			TileTypeIndex4 = FMath::Max(Cell->TileType, E->TileType);
			MaskTypeIndex4 = Cell->TileType < E->TileType ? MASK_SIDE_RIGHT_4 : MASK_DEFAULT_4;
		}
		else if (!E || (S && S->TileType > E->TileType))
		{
			TileTypeIndex4 = FMath::Max(Cell->TileType, S->TileType);
			MaskTypeIndex4 = Cell->TileType < S->TileType ? MASK_SIDE_BOTTOM_4 : MASK_DEFAULT_4;
		}
		else if (Cell->TileType < E->TileType || Cell->TileType < S->TileType)
		{
			TileTypeIndex4 = E->TileType;
			MaskTypeIndex4 = MASK_INNER_4;
		}
		else if (UTileCell* SE = Cell->GetNeighbor(ETileDirection::SouthEast); SE && Cell->TileType < SE->TileType)
		{
			TileTypeIndex4 = SE->TileType;
			MaskTypeIndex4 = MASK_OUTER_4;
		}
		else
		{
			TileTypeIndex4 = Cell->TileType;
			MaskTypeIndex4 = MASK_DEFAULT_4;
		}
	}
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		7,
		static_cast<float>(TileTypeIndex4)
	);
	InstancedStaticMeshComponent->SetCustomDataValue(
		Index,
		8,
		static_cast<float>(MaskTypeIndex4)
	);
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
		AddFeature(FTileCoordinates::ToPosition(Cell->Coordinates));
	}
}

void ATileChunk::AddCell(int32 Index, UTileCell* Cell)
{
	Cells[Index] = Cell;
	Cell->Chunk = this;
}

void ATileChunk::AddFeature(const FVector& Position)
{
	FTileHash Hash = UTileMetrics::SampleHashGrid(Position);
	if (Hash.A >= 0.1f)
	{
		return;
	}
	
	ATileFeature* Feature = GetWorld()->SpawnActor<ATileFeature>(
		FVector(Position.X, Position.Y, 50.f),
		FRotator::ZeroRotator
	);
	Feature->SetSpriteSize(1.f + Hash.B * 0.5f);
	
	Features.Add(Feature);
}

void ATileChunk::Refresh()
{
	SetActorTickEnabled(true);
}

void ATileChunk::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Triangulate();
	SetActorTickEnabled(false);
}