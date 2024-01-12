// © 2024, Huy Phan. All rights reserved.


#include "TileMap/TileChunk.h"

#include "Core/DanmakuPlayerController.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileMapData.h"


ATileChunk::ATileChunk()
{
	PrimaryActorTick.bCanEverTick = true;

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

bool ATileChunk::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (const ADanmakuPlayerController* PC = Cast<ADanmakuPlayerController>(RealViewer))
	{
		return PC->bClientFinishProceduralGeneration && Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}
	
	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}
