// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileCell.h"

#include "TileMap/TileChunk.h"

UTileCell::UTileCell()
{
	TileType = ETileType::GrassForest;
	Neighbors.SetNum(8);
	IsBlendDrawn.SetNum(12);
}

void UTileCell::Refresh()
{
	if (Chunk)
	{
		Chunk->Refresh();
		for (UTileCell* Neighbor : Neighbors)
		{
			if (Neighbor && Neighbor->Chunk)
			{
				Neighbor->Chunk->Refresh();
			}
		}
	}
}

void UTileCell::SetTileType(ETileType Type)
{
	if (TileType == Type)
	{
		return;
	}
	
	TileType = Type;
	Refresh();
}

void UTileCell::SetNeighbor(ETileDirection Direction, UTileCell* TileCell)
{
	const uint8 D = static_cast<uint8>(Direction);
	Neighbors[D] = TileCell;
	TileCell->Neighbors[D < 4 ? D + 4 : D - 4] = this;
}

UTileCell* UTileCell::GetNeighbor(ETileDirection Direction)
{
	return Neighbors[static_cast<uint8>(Direction)];
}
