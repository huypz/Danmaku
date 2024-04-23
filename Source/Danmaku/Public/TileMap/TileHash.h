// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "TileHash.generated.h"

/**
 * 
 */
USTRUCT()
struct DANMAKU_API FTileHash
{
	GENERATED_BODY()
	
	float A;
	float B;

	FTileHash()
		: A(0.f)
		, B(0.f)
	{}
	
	static FTileHash Create()
	{
		FTileHash Hash;
		Hash.A = FMath::RandRange(0.f, 1.f);
		Hash.B = FMath::RandRange(0.f, 1.f);
		return Hash;
	}
};
