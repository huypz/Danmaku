// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileHash.h"
#include "TileMetrics.generated.h"


UCLASS()
class DANMAKU_API UTileMetrics : public UObject
{
	GENERATED_BODY()
	
public:
	static constexpr int32 TileWidth = 100;

	static constexpr int32 TileHeight = 100;

	static constexpr int32 ChunkSizeX = 5;

	static constexpr int32 ChunkSizeY = 5;

	static constexpr int32 HashGridSize = 256;

	static constexpr float HashGridScale = 0.25f;
	
	static TArray<FTileHash> HashGrid;

	static void InitializeHashGrid(int32 Seed)
	{
		HashGrid.SetNum(HashGridSize * HashGridSize);
		int32 CurrentState = FMath::GetRandSeed();
		FMath::RandInit(Seed);
		for (int32 i = 0; i < HashGrid.Num(); i++)
		{
			HashGrid[i] = FTileHash::Create();
		}
	}

	static FTileHash SampleHashGrid(FVector Position)
	{
		int32 X = (int)(Position.X * HashGridScale) % HashGridSize;
		if (X < 0)
		{
			X += HashGridSize;
		}
		int32 Y = (int)(Position.Y * HashGridScale) % HashGridSize;
		if (Y < 0)
		{
			Y += HashGridSize;
		}
		return HashGrid[X + Y * HashGridSize];
	}
};
