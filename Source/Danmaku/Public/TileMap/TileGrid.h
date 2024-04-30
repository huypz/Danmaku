// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

class ATileFeature;
class UTileMapEditor;
class ATileChunk;
class UTileCell;
class FBufferArchive;

UCLASS()
class DANMAKU_API ATileGrid : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 ChunkCountX;

	UPROPERTY(EditAnywhere)
	int32 ChunkCountY;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TileChunkClass;
	
	ATileGrid();

	void Generate();

	void Save(FBufferArchive& Writer);

	void Load(FMemoryReader& Reader);

	UTileCell* GetCell(const FVector& Position);

private:
	int32 CellCountX;

	int32 CellCountY;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UTileCell*> Cells;

	UPROPERTY(VisibleAnywhere)
	TArray<ATileChunk*> Chunks;

	void CreateCell(int32 X, int32 Y, int32 Index);

	void CreateCells();

	void CreateChunks();

	void AddCellToChunk(int32 X, int32 Y, UTileCell* Cell);
};
