// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileGrid.h"

#include "Serialization/BufferArchive.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileChunk.h"
#include "TileMap/TileCoordinates.h"
#include "TileMap/TileDirection.h"


ATileGrid::ATileGrid()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bNetStartup = true;

	ChunkCountX = 0;
	ChunkCountY = 0;
	CellCountX = 0;
	CellCountY = 0;

	UTileMetrics::InitializeHashGrid(0);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATileGrid::Generate()
{
	CellCountX = ChunkCountX * UTileMetrics::ChunkSizeX;
	CellCountY = ChunkCountY * UTileMetrics::ChunkSizeY;

	CreateChunks();
	CreateCells();
}

void ATileGrid::Save(FBufferArchive& Writer)
{
	for (int32 i = 0; i < Cells.Num(); i++)
	{
		Cells[i]->Save(Writer);
	}
}

void ATileGrid::Load(FMemoryReader& Reader)
{
	for (int32 i = 0; i < Cells.Num(); i++)
	{
		Cells[i]->Load(Reader);
	}
	for (int32 i = 0; i < Chunks.Num(); i++)
	{
		Chunks[i]->Refresh();
	}
}

UTileCell* ATileGrid::GetCell(const FVector& Position)
{
	const FTileCoordinates Coordinates = FTileCoordinates::FromPosition(Position);
	const int32 Index = Coordinates.X * CellCountY + Coordinates.Y;
	return Index < Cells.Num() ? Cells[Index] : nullptr;
}

void ATileGrid::CreateCell(int32 X, int32 Y, int32 Index)
{
	UTileCell* Cell = NewObject<UTileCell>(this, *FString::Printf(TEXT("Cell %d %d"), X, Y));
	Cell->Coordinates = FTileCoordinates(X, Y);
	Cells.Add(Cell);
	
	if (Y > 0)
	{
		Cell->SetNeighbor(ETileDirection::North, Cells[Index - 1]);
	}
	if (X > 0)
	{
		Cell->SetNeighbor(ETileDirection::West, Cells[Index - CellCountY]);
		if (Y > 0)
		{
			Cell->SetNeighbor(ETileDirection::NorthWest, Cells[Index - CellCountY - 1]);
		}
		if (Y < CellCountY - 1)
		{
			Cell->SetNeighbor(ETileDirection::SouthWest, Cells[Index - CellCountY + 1]);
		} 
	}

	AddCellToChunk(X, Y, Cell);
}

void ATileGrid::CreateCells()
{
	int32 i = 0;
	for (int32 x = 0; x < CellCountX; x++)
	{
		for (int32 y = 0; y < CellCountY; y++)
		{
			CreateCell(x, y, i++);
		}
	}
}

void ATileGrid::CreateChunks()
{
	for (int32 x = 0; x < ChunkCountX; x++)
	{
		for (int32 y = 0; y < ChunkCountY; y++)
		{
			FVector Position(
				(x * UTileMetrics::ChunkSizeX * UTileMetrics::TileWidth) + (UTileMetrics::ChunkSizeX * UTileMetrics::TileWidth / 2),
				(y * UTileMetrics::ChunkSizeY * UTileMetrics::TileHeight) + (UTileMetrics::ChunkSizeY * UTileMetrics::TileHeight / 2),
				0.f
			);

			ATileChunk* Chunk = GetWorld()->SpawnActor<ATileChunk>(TileChunkClass, Position, FRotator::ZeroRotator);
			Chunk->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			Chunks.Add(Chunk);
		}
	}
}

void ATileGrid::AddCellToChunk(int32 X, int32 Y, UTileCell* Cell)
{
	const int32 ChunkX = X / UTileMetrics::ChunkSizeX;
	const int32 ChunkY = Y / UTileMetrics::ChunkSizeY;
	ATileChunk* Chunk = Chunks[ChunkX * ChunkCountY + ChunkY];

	const int32 LocalX = X - ChunkX * UTileMetrics::ChunkSizeX;
	const int32 LocalY = Y - ChunkY * UTileMetrics::ChunkSizeY;
	Chunk->AddCell(LocalX * UTileMetrics::ChunkSizeY + LocalY, Cell);
}