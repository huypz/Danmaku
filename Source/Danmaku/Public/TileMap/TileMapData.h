// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "TilemapData.generated.h"

enum ETileDirection : uint8
{
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest,
};

inline ETileDirection operator+(const ETileDirection Value, const int32 Other)
{
	return static_cast<ETileDirection>((static_cast<int32>(Value) + Other) % 8);
}

inline ETileDirection operator-(const ETileDirection Value, const int32 Other)
{
	return static_cast<ETileDirection>((static_cast<int32>(Value) + 8 - Other) % 8);
}

UCLASS()
class DANMAKU_API UTileMetrics : public UObject
{
	GENERATED_BODY()
	
public:
	static constexpr int32 TileWidth = 100;

	static constexpr int32 TileHeight = 100;

	static constexpr int32 ChunkSizeX = 5;

	static constexpr int32 ChunkSizeY = 5;

	static const inline FVector Edges[] = {
		{0.5f * TileHeight, 0.f, 0.f},
		{0.5f * TileWidth, 0.5f * TileHeight, 0.f},		
		{0.f, 0.5f * TileWidth, 0.f},					
		{-0.5f * TileWidth, 0.5f * TileHeight, 0.f},	
		{-0.5f * TileWidth, 0.f, 0.f},					
		{-0.5f * TileWidth, -0.5f * TileHeight, 0.f},	
		{0.f, -0.5f * TileHeight, 0.f},					
		{0.5f * TileWidth, -0.5f * TileHeight, 0.f}	
	};
};

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
		const int32 X = Position.X / UTileMetrics::TileHeight;
		const int32 Y = Position.Y / UTileMetrics::TileWidth;

		return FTileCoordinates(X, Y);
	}

	FString ToString() const {
		return FString::Printf(TEXT("(%d, %d)"), X, Y);
	}
};
