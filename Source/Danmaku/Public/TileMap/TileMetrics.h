// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "TileMetrics.generated.h"


UCLASS()
class DANMAKU_API UTileMetrics : public UObject
{
	GENERATED_BODY()
	
public:
	static constexpr int32 TileWidth = 100;

	static constexpr int32 TileHeight = 100;

	static constexpr int32 ChunkSizeX = 1;

	static constexpr int32 ChunkSizeY = 1;
};
