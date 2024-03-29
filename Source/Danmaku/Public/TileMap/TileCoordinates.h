// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileMetrics.h"
#include "TileCoordinates.generated.h"

/**
 * 
 */
USTRUCT()
struct DANMAKU_API FTileCoordinates
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	int32 X;

	UPROPERTY(VisibleAnywhere)
	int32 Y;

	FTileCoordinates()
		: X(0)
		, Y(0)
	{}

	FTileCoordinates(const int32 X, const int32 Y)
		: X(X)
		, Y(Y)
	{}
	
	static FTileCoordinates FromPosition(const FVector& Position)
	{
		const int32 X = Position.X / UTileMetrics::TileWidth;
		const int32 Y = Position.Y / UTileMetrics::TileHeight;

		return FTileCoordinates(X, Y);
	}

	static FVector ToPosition(const FTileCoordinates& Coordinates)
	{
		const int32 X = Coordinates.X * UTileMetrics::TileWidth;
		const int32 Y = Coordinates.Y * UTileMetrics::TileHeight;

		return FVector(X + 50.f, Y + 50.f, 0.f);
	}

	FString ToString() const {
		return FString::Printf(TEXT("(%d, %d)"), X, Y);
	}
};
