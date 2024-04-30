// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileCoordinates.h"
#include "TileDirection.h"
#include "TileType.h"
#include "UObject/Object.h"
#include "TileCell.generated.h"


class ATileChunk;
class ATileFeature;
class FBufferArchive;

/**
 * 
 */
UCLASS()
class DANMAKU_API UTileCell : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FTileCoordinates Coordinates;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ATileChunk> Chunk;
	
	UTileCell();

	void Refresh();

	void Save(FBufferArchive& Writer);

	void Load(FMemoryReader& Reader);

	ETileType GetTileType() const;

	void SetTileType(ETileType Value);

	TSubclassOf<ATileFeature> GetFeatureClass() const;

	void SetFeatureClass(TSubclassOf<ATileFeature> NewFeatureClass);

	void SetNeighbor(ETileDirection Direction, UTileCell* TileCell);

	UTileCell* GetNeighbor(ETileDirection Direction);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UTileCell*> Neighbors;

	UPROPERTY(VisibleAnywhere)
	ETileType TileType;

	UPROPERTY()
	TSubclassOf<ATileFeature> FeatureClass;
};
