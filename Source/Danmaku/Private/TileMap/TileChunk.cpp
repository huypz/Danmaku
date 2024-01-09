// © 2024, Huy Phan. All rights reserved.


#include "TileMap/TileChunk.h"

#include "TileMap/TileCell.h"
#include "TileMap/TileMapData.h"


ATileChunk::ATileChunk()
{
	PrimaryActorTick.bCanEverTick = true;

	SetLockLocation(true);

	Cells.SetNum(UTileMetrics::ChunkSizeX * UTileMetrics::ChunkSizeY);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATileChunk::Triangulate()
{
	for (ATileCell* Cell : Cells)
	{
		Cell->Triangulate();
	}
}

void ATileChunk::AddCell(int32 Index, ATileCell* Cell)
{
	Cells[Index] = Cell;
	Cell->Chunk = this;
	Cell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
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
