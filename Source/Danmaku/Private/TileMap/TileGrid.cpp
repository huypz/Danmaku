// © 2024, Huy Phan. All rights reserved.


#include "TileMap/TileGrid.h"

#include "TileMap/TileCell.h"
#include "TileMap/TileChunk.h"
#include "TileMap/TileMapData.h"


ATileGrid::ATileGrid()
{
	PrimaryActorTick.bCanEverTick = false;

	SetLockLocation(true);

	ChunkCountX = 0;
	ChunkCountY = 0;
	CellCountX = 0;
	CellCountY = 0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

ATileCell* ATileGrid::GetCell(FVector Position)
{
	FVector LocalPosition = GetTransform().InverseTransformPosition(Position);
	FTileCoordinates Coordinates = FTileCoordinates::FromPosition(LocalPosition);
	int32 Index = Coordinates.Y * CellCountX + Coordinates.X;
	return Index < Cells.Num() ? Cells[Index] : nullptr;
}

void ATileGrid::BeginPlay()
{
	Super::BeginPlay();

	CellCountX = ChunkCountX * UTileMetrics::ChunkSizeX;
	CellCountY = ChunkCountY * UTileMetrics::ChunkSizeY;

	CreateChunks();
	CreateCells();
}

void ATileGrid::CreateCell(int32 X, int32 Y, int32 Index)
{
	FVector Position(
		X * UTileMetrics::TileHeight + UTileMetrics::TileHeight / 2,
		Y * UTileMetrics::TileWidth + UTileMetrics::TileWidth / 2,
		0.f
	);
	
	if (UWorld* World = GetWorld())
	{
		if (ATileCell* Cell = World->SpawnActor<ATileCell>(Position, FRotator::ZeroRotator))
		{
			Cell->Coordinates = FTileCoordinates(X, Y);
			Cell->SetActorLabel(FString::Printf(TEXT("Cell (%d, %d)"), X, Y));
			Cells.Add(Cell);
			AddCellToChunk(X, Y, Cell);

			// Set adjacent and diagonal tiles
			if (X > 0)
			{
				Cell->SetNeighbor(ETileDirection::South, Cells[Index - 1]);
			}
			if (Y > 0)
			{
				Cell->SetNeighbor(ETileDirection::West, Cells[Index - CellCountX]);
				if (X > 0)
				{
					Cell->SetNeighbor(ETileDirection::SouthWest, Cells[Index - CellCountX - 1]);
				}
				if (X < CellCountX - 1)
				{
					Cell->SetNeighbor(ETileDirection::NorthWest, Cells[Index - CellCountX + 1]);
				} 
			}
		}
	}
}

void ATileGrid::CreateCells()
{
	int32 i = 0;
	for (int32 y = 0; y < CellCountY; y++)
	{
		for (int32 x = 0; x < CellCountX; x++)
		{
			CreateCell(x, y, i++);
		}
	}
}

void ATileGrid::CreateChunks()
{
	for (int32 y = 0; y < ChunkCountY; y++)
	{
		for (int32 x = 0; x < ChunkCountX; x++)
		{
			FVector Position(
				(x * UTileMetrics::ChunkSizeX * UTileMetrics::TileHeight) + (UTileMetrics::ChunkSizeX * UTileMetrics::TileHeight / 2),
				(y * UTileMetrics::ChunkSizeY * UTileMetrics::TileWidth) + (UTileMetrics::ChunkSizeY * UTileMetrics::TileWidth / 2),
				0.f
			);
			ATileChunk* Chunk = GetWorld()->SpawnActor<ATileChunk>(Position, FRotator::ZeroRotator);
			Chunk->SetActorLabel(FString::Printf(TEXT("Chunk (%d, %d)"), x, y));
			Chunk->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			Chunks.Add(Chunk);
		}
	}
}

void ATileGrid::AddCellToChunk(int32 X, int32 Y, ATileCell* Cell)
{
	int32 ChunkX = X / UTileMetrics::ChunkSizeX;
	int32 ChunkY = Y / UTileMetrics::ChunkSizeY;
	ATileChunk* Chunk = Chunks[ChunkY * ChunkCountX + ChunkX];

	int32 LocalX = X - ChunkX * UTileMetrics::ChunkSizeX;
	int32 LocalY = Y - ChunkY * UTileMetrics::ChunkSizeY;
	Chunk->AddCell(LocalY * UTileMetrics::ChunkSizeX + LocalX, Cell);
}
