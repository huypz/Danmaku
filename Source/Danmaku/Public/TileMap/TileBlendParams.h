// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "TileCell.h"
#include "TileDirection.h"
#include "TileBlendParams.generated.h"

/**
 * The cursed struct that calculates god-knows-what for tile blending.
 * The code needs to be refactored and optimized, but that is a problem for future me.
 */
USTRUCT()
struct FTileBlendParams
{
	GENERATED_BODY()
	
	FVector Position;

	FVector2D TileUVTiling;
	
	FVector2D TileUVOffset;

	ETileDirection Direction;

	int32 MaskTypeIndex;

	float MaskRotation;

	FTileBlendParams()
		: Position(FVector::ZeroVector)
		, TileUVTiling(FVector2D::ZeroVector)
		, TileUVOffset(FVector2D::ZeroVector)
		, Direction(ETileDirection::North)
		, MaskTypeIndex(0)
		, MaskRotation(0.f)
	{}
	
	/**
	 * @param X Cell Coordinate X
	 * @param Y Cell Coordinate Y
	 * @param DirectionIndex \n
     * 0: North1\n
	 * 1: North2\n
	 * 2: NorthEast\n
	 * 3: East1\n
	 * 4: East2\n
	 * 5: SouthEast\n
	 * 6: South1\n
	 * 7: South2\n
	 * 8: SouthWest\n
	 * 9: West1\n
	 * 10: West2\n
	 * 11: NorthWest
	 */
	FTileBlendParams(const int32 X, const int32 Y, int32 DirectionIndex, UTileCell* Cell)
	{
		switch (DirectionIndex)
		{
		case 0:
			Position = FVector(X * 100.f + 25.f, Y * 100.f - 25.f, 0.f);
			TileUVOffset = FVector2D(0.f, 0.5f);
			Direction = ETileDirection::North;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction - 1) && Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType && Cell->GetNeighbor(Direction - 1)->IsBlendDrawn[4])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction - 1) || Cell->TileType > Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 4;
				MaskRotation = 0.f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 6;
				MaskRotation = 0.f;
			}
			break;
		case 1:
			Position = FVector(X * 100.f + 75.f, Y * 100.f - 25.f, 0.f);
			TileUVOffset = FVector2D(0.5f, 0.5f);
			Direction = ETileDirection::North;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType && Cell->GetNeighbor(Direction + 1)->IsBlendDrawn[9])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction + 1) || Cell->TileType > Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 5;
				MaskRotation = 0.f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 7;
				MaskRotation = 0.f;
			}
			break;
		case 2:
			Position = FVector(X * 100.f + 125.f, Y * 100.f - 25.f, 0.f);
			TileUVOffset = FVector2D(0.f, 0.5f);
			Direction = ETileDirection::NorthEast;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction + 1)->TileType) ||
				(Cell->GetNeighbor(Direction - 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			)
			{
				MaskTypeIndex = -1;
			}
			else
			{
				MaskTypeIndex = 8;
				MaskRotation = 0.75f;
			}
			break;
		case 3:
			Position = FVector(X * 100.f + 125.f, Y * 100.f + 25.f, 0.f);
			TileUVOffset = FVector2D(0.f, 0.0f);
			Direction = ETileDirection::East;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction - 1) && Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType && Cell->GetNeighbor(Direction - 1)->IsBlendDrawn[7])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction - 1) || Cell->TileType > Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.75f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 4;
				MaskRotation = 0.75f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 6;
				MaskRotation = 0.75f;
			}
			break;
		case 4:
			Position = FVector(X * 100.f + 125.f, Y * 100.f + 75.f, 0.f);
			TileUVOffset = FVector2D(0.f, 0.5f);
			Direction = ETileDirection::East;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType && Cell->GetNeighbor(Direction + 1)->IsBlendDrawn[0])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction + 1) || Cell->TileType > Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.75f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 5;
				MaskRotation = 0.75f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 7;
				MaskRotation = 0.75f;
			}
			break;
		case 5:
			Position = FVector(X * 100.f + 125.f, Y * 100.f + 125.f, 0.f);
			TileUVOffset = FVector2D(0.f, 0.f);
			Direction = ETileDirection::SouthEast;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction + 1)->TileType) ||
				(Cell->GetNeighbor(Direction - 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			)
			{
				MaskTypeIndex = -1;
			}
			else
			{
				MaskTypeIndex = 8;
				MaskRotation = 0.5f;
			}
			break;
		case 6:
			Position = FVector(X * 100.f + 75.f, Y * 100.f + 125.f, 0.f);
			TileUVOffset = FVector2D(0.5f, 0.f);
			Direction = ETileDirection::South;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction - 1) && Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType && Cell->GetNeighbor(Direction - 1)->IsBlendDrawn[10])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction - 1) || Cell->TileType > Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.5f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 4;
				MaskRotation = 0.5f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 6;
				MaskRotation = 0.5f;
			}
			break;
		case 7:
			Position = FVector(X * 100.f + 25.f, Y * 100.f + 125.f, 0.f);
			TileUVOffset = FVector2D(0.f, 0.f);
			Direction = ETileDirection::South;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType && Cell->GetNeighbor(Direction + 1)->IsBlendDrawn[3])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction + 1) || Cell->TileType > Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.5f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 5;
				MaskRotation = 0.5f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 7;
				MaskRotation = 0.5f;
			}
			break;
		case 8:
			Position = FVector(X * 100.f - 25.f, Y * 100.f + 125.f, 0.f);
			TileUVOffset = FVector2D(0.5f, 0.f);
			Direction = ETileDirection::SouthWest;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction + 1)->TileType) ||
				(Cell->GetNeighbor(Direction - 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			)
			{
				MaskTypeIndex = -1;
			}
			else
			{
				MaskTypeIndex = 8;
				MaskRotation = 0.25f;
			}
			break;
		case 9:
			Position = FVector(X * 100.f - 25.f, Y * 100.f + 75.f, 0.f);
			TileUVOffset = FVector2D(0.5f, 0.5f);
			Direction = ETileDirection::West;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction - 1) && Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType && Cell->GetNeighbor(Direction - 1)->IsBlendDrawn[1])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction - 1) || Cell->TileType > Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.25f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 4;
				MaskRotation = 0.25f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			{
				MaskTypeIndex = 6;
				MaskRotation = 0.25f;
			}
			break;
		case 10:
			Position = FVector(X * 100.f - 25.f, Y * 100.f + 25.f, 0.f);
			TileUVOffset = FVector2D(0.5f, 0.f);
			Direction = ETileDirection::West;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType && Cell->GetNeighbor(Direction + 1)->IsBlendDrawn[6])
			)
			{
				MaskTypeIndex = -1;
			}
			else if (!Cell->GetNeighbor(Direction + 1) || Cell->TileType > Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = FMath::RandRange(1, 3);
				MaskRotation = 0.25f;
			}
			else if (Cell->TileType == Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 5;
				MaskRotation = 0.25f;
			}
			else if (Cell->TileType < Cell->GetNeighbor(Direction + 1)->TileType)
			{
				MaskTypeIndex = 7;
				MaskRotation = 0.25f;
			}
			break;
		case 11:
			Position = FVector(X * 100.f - 25.f, Y * 100.f - 25.f, 0.f);
			TileUVOffset = FVector2D(0.5f, 0.5f);
			Direction = ETileDirection::NorthWest;
			if (
				!Cell->GetNeighbor(Direction) ||
				Cell->TileType <= Cell->GetNeighbor(Direction)->TileType ||
				(Cell->GetNeighbor(Direction + 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction + 1)->TileType) ||
				(Cell->GetNeighbor(Direction - 1) && Cell->GetNeighbor(Direction)->TileType < Cell->GetNeighbor(Direction - 1)->TileType)
			)
			{
				MaskTypeIndex = -1;
			}
			else
			{
				MaskTypeIndex = 8;
				MaskRotation = 0.f;
			}
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("FTileBlendParam: Invalid DirectionIndex"));
		}
	}
};
