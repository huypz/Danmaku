// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

class ATileCell;
class ATileChunk;

/**
 * 
 */
UCLASS()
class DANMAKU_API ATileGrid : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 ChunkCountX;

	UPROPERTY(EditAnywhere)
	int32 ChunkCountY;
	
	ATileGrid();

	void Generate();

	ATileCell* GetCell(FVector Position);

private:
	int32 CellCountX;

	int32 CellCountY;

	UPROPERTY()
	TArray<ATileCell*> Cells;

	UPROPERTY()
	TArray<ATileChunk*> Chunks;

	void CreateCell(int32 X, int32 Y, int32 Index);

	void CreateCells();

	void CreateChunks();

	void AddCellToChunk(int32 X, int32 Y, ATileCell* Cell);
};
