// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileCell.h"

#include "TileMap/TileChunk.h"
#include "TileMap/TileFeature.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

UTileCell::UTileCell()
{
	TileType = ETileType::GrassForest;
	
	Neighbors.SetNum(8);
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

void UTileCell::Save(FBufferArchive& Writer)
{
	Writer << TileType;

	FObjectAndNameAsStringProxyArchive WrappedWriter(Writer, true);
	WrappedWriter << FeatureClass;
}

void UTileCell::Load(FMemoryReader& Reader)
{
	int32 InTileTypeIndex;
	Reader << InTileTypeIndex;
	SetTileType(static_cast<ETileType>(InTileTypeIndex));

	FObjectAndNameAsStringProxyArchive WrappedReader(Reader, true);
	UClass* InFeatureClass;
	WrappedReader << InFeatureClass;
	SetFeatureClass(InFeatureClass);
	
}

ETileType UTileCell::GetTileType() const
{
	return TileType;
}

void UTileCell::SetTileType(ETileType Value)
{
	if (TileType == Value)
	{
		return;
	}
	
	TileType = Value;
	Refresh();
}

TSubclassOf<ATileFeature> UTileCell::GetFeatureClass() const
{
	return FeatureClass;
}

void UTileCell::SetFeatureClass(TSubclassOf<ATileFeature> NewFeatureClass)
{
	if (FeatureClass == NewFeatureClass)
	{
		return;
	}
	
	FeatureClass = NewFeatureClass;
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
