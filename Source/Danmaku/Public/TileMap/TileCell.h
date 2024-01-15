// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileCoordinates.h"
#include "TileDirection.h"
#include "TileType.h"
#include "UObject/Object.h"
#include "TileCell.generated.h"


class ATileChunk;

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
	ETileType TileType;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ATileChunk> Chunk;
	
	TArray<bool> IsBlendDrawn;

	UTileCell();

	void Refresh();

	void SetTileType(ETileType Type);

	void SetNeighbor(ETileDirection Direction, UTileCell* TileCell);

	UTileCell* GetNeighbor(ETileDirection Direction);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UTileCell*> Neighbors;
};
