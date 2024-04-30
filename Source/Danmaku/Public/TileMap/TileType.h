// Copyright Huy Phan. All Rights Reserved.

#pragma once


UENUM()
enum class ETileType : int32
{
	Blank,
	Water,
	Sand,
	GrassPlain,
	Snow,
	GrassForest,
};
ENUM_RANGE_BY_COUNT(ETileType, 6);

static const FString TileTextureDirectory = "/Script/Engine.Texture2D'/Game/Texture/Environment/Tile/";

static const TMap<ETileType, FString> TileTexturePaths = {
	{ETileType::Blank, TileTextureDirectory + "T_Blank.T_Blank'"},
	{ETileType::Water, TileTextureDirectory + "T_Water.T_Water'"},
	{ETileType::Sand, TileTextureDirectory + "T_Sand.T_Sand'"},
	{ETileType::GrassPlain, TileTextureDirectory + "T_GrassPlain.T_GrassPlain'"},
	{ETileType::Snow, TileTextureDirectory + "T_Snow.T_Snow'"},
	{ETileType::GrassForest, TileTextureDirectory + "T_GrassForest.T_GrassForest'"},
};
