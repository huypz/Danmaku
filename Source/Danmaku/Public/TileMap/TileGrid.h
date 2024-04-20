// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

class UTileMapEditor;
class ATileChunk;
class UTileCell;

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

	UTileCell* GetCell(const FVector& Position);

private:
	int32 CellCountX;

	int32 CellCountY;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UTileCell*> Cells;

	UPROPERTY(VisibleAnywhere)
	TArray<ATileChunk*> Chunks;

	UPROPERTY()
	TObjectPtr<UTileMapEditor> Editor;

	void CreateCell(int32 X, int32 Y, int32 Index);

	void CreateCells();

	void CreateChunks();

	void AddCellToChunk(int32 X, int32 Y, UTileCell* Cell);
};
