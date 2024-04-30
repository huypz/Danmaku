// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileChunk.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileFeatureManager.h"
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
	
	Features = CreateDefaultSubobject<UTileFeatureManager>(TEXT("TileFeatureManagerComponent"));
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
		static_cast<float>(Cell->GetTileType())
	);
	
	// Quadrant 1
	ETileType TileTypeIndex1 = Cell->GetTileType();
	int32 MaskTypeIndex1 = MASK_DEFAULT_1;
	if (Cell->GetNeighbor(ETileDirection::North) || Cell->GetNeighbor(ETileDirection::West))
	{
		UTileCell* N = Cell->GetNeighbor(ETileDirection::North);
		UTileCell* W = Cell->GetNeighbor(ETileDirection::West);
		if (!N || (W && N->GetTileType() < W->GetTileType()))
		{
			TileTypeIndex1 = FMath::Max(Cell->GetTileType(), W->GetTileType());
			MaskTypeIndex1 = Cell->GetTileType() < W->GetTileType() ? MASK_SIDE_LEFT_1 : MASK_DEFAULT_1;
		}
		else if (!W || (N && N->GetTileType() > W->GetTileType()))
		{
			TileTypeIndex1 = FMath::Max(Cell->GetTileType(), N->GetTileType());
			MaskTypeIndex1 = Cell->GetTileType() < N->GetTileType() ? MASK_SIDE_TOP_1 : MASK_DEFAULT_1;
		}
		else if (Cell->GetTileType() < N->GetTileType() || Cell->GetTileType() < W->GetTileType())
		{
			TileTypeIndex1 = N->GetTileType();
			MaskTypeIndex1 = MASK_INNER_1;
		}
		else if (UTileCell* NW = Cell->GetNeighbor(ETileDirection::NorthWest); NW && Cell->GetTileType() < NW->GetTileType())
		{
			TileTypeIndex1 = NW->GetTileType();
			MaskTypeIndex1 = MASK_OUTER_1;
		}
		else
		{
			TileTypeIndex1 = Cell->GetTileType();
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
	ETileType TileTypeIndex2 = Cell->GetTileType();
	int32 MaskTypeIndex2 = MASK_DEFAULT_2;
	if (Cell->GetNeighbor(ETileDirection::North) || Cell->GetNeighbor(ETileDirection::East))
	{
		UTileCell* N = Cell->GetNeighbor(ETileDirection::North);
		UTileCell* E = Cell->GetNeighbor(ETileDirection::East);
		if (!N || (E && N->GetTileType() < E->GetTileType()))
		{
			TileTypeIndex2 = FMath::Max(Cell->GetTileType(), E->GetTileType());
			MaskTypeIndex2 = Cell->GetTileType() < E->GetTileType() ? MASK_SIDE_RIGHT_2 : MASK_DEFAULT_2;
		}
		else if (!E || (N && N->GetTileType() > E->GetTileType()))
		{
			TileTypeIndex2 = FMath::Max(Cell->GetTileType(), N->GetTileType());
			MaskTypeIndex2 = Cell->GetTileType() < N->GetTileType() ? MASK_SIDE_TOP_2 : MASK_DEFAULT_2;
		}
		else if (Cell->GetTileType() < N->GetTileType() || Cell->GetTileType() < E->GetTileType())
		{
			TileTypeIndex2 = N->GetTileType();
			MaskTypeIndex2 = MASK_INNER_2;
		}
		else if (UTileCell* NE = Cell->GetNeighbor(ETileDirection::NorthEast); NE && Cell->GetTileType() < NE->GetTileType())
		{
			TileTypeIndex2 = NE->GetTileType();
			MaskTypeIndex2 = MASK_OUTER_2;
		}
		else
		{
			TileTypeIndex2 = Cell->GetTileType();
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
	ETileType TileTypeIndex3 = Cell->GetTileType();
	int32 MaskTypeIndex3 = MASK_DEFAULT_3;
	if (Cell->GetNeighbor(ETileDirection::South) || Cell->GetNeighbor(ETileDirection::West))
	{
		UTileCell* S = Cell->GetNeighbor(ETileDirection::South);
		UTileCell* W = Cell->GetNeighbor(ETileDirection::West);
		if (!S || (W && S->GetTileType() < W->GetTileType()))
		{
			TileTypeIndex3 = FMath::Max(Cell->GetTileType(), W->GetTileType());
			MaskTypeIndex3 = Cell->GetTileType() < W->GetTileType() ? MASK_SIDE_LEFT_3 : MASK_DEFAULT_3;
		}
		else if (!W || (S && S->GetTileType() > W->GetTileType()))
		{
			TileTypeIndex3 = FMath::Max(Cell->GetTileType(), S->GetTileType());
			MaskTypeIndex3 = Cell->GetTileType() < S->GetTileType() ? MASK_SIDE_BOTTOM_3 : MASK_DEFAULT_3;
		}
		else if (Cell->GetTileType() < W->GetTileType() || Cell->GetTileType() < S->GetTileType())
		{
			TileTypeIndex3 = W->GetTileType();
			MaskTypeIndex3 = MASK_INNER_3;
		}
		else if (UTileCell* SW = Cell->GetNeighbor(ETileDirection::SouthWest); SW && Cell->GetTileType() < SW->GetTileType())
		{
			TileTypeIndex3 = SW->GetTileType();
			MaskTypeIndex3 = MASK_OUTER_3;
		}
		else
		{
			TileTypeIndex3 = Cell->GetTileType();
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
	ETileType TileTypeIndex4 = Cell->GetTileType();
	int32 MaskTypeIndex4 = MASK_DEFAULT_4;
	if (Cell->GetNeighbor(ETileDirection::South) || Cell->GetNeighbor(ETileDirection::East))
	{
		UTileCell* S = Cell->GetNeighbor(ETileDirection::South);
		UTileCell* E = Cell->GetNeighbor(ETileDirection::East);
		if (!S || (E && S->GetTileType() < E->GetTileType()))
		{
			TileTypeIndex4 = FMath::Max(Cell->GetTileType(), E->GetTileType());
			MaskTypeIndex4 = Cell->GetTileType() < E->GetTileType() ? MASK_SIDE_RIGHT_4 : MASK_DEFAULT_4;
		}
		else if (!E || (S && S->GetTileType() > E->GetTileType()))
		{
			TileTypeIndex4 = FMath::Max(Cell->GetTileType(), S->GetTileType());
			MaskTypeIndex4 = Cell->GetTileType() < S->GetTileType() ? MASK_SIDE_BOTTOM_4 : MASK_DEFAULT_4;
		}
		else if (Cell->GetTileType() < E->GetTileType() || Cell->GetTileType() < S->GetTileType())
		{
			TileTypeIndex4 = E->GetTileType();
			MaskTypeIndex4 = MASK_INNER_4;
		}
		else if (UTileCell* SE = Cell->GetNeighbor(ETileDirection::SouthEast); SE && Cell->GetTileType() < SE->GetTileType())
		{
			TileTypeIndex4 = SE->GetTileType();
			MaskTypeIndex4 = MASK_OUTER_4;
		}
		else
		{
			TileTypeIndex4 = Cell->GetTileType();
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
	Features->Clear();

	int32 Index = 0;
	for (UTileCell* Cell : Cells)
	{
		TriangulateTile(Cell, Index++);
	}
	Features->Apply(Cells);
}

void ATileChunk::AddCell(int32 Index, UTileCell* Cell)
{
	Cells[Index] = Cell;
	Cell->Chunk = this;
}

void ATileChunk::Refresh()
{
	SetActorTickEnabled(true);
}

void ATileChunk::SetMesh(UStaticMesh* Mesh)
{
	InstancedStaticMeshComponent->SetStaticMesh(Mesh);
}

void ATileChunk::SetMaterial(UMaterial* Material)
{
	InstancedStaticMeshComponent->SetMaterial(0, Material);
}

void ATileChunk::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Triangulate();
	SetActorTickEnabled(false);
}
