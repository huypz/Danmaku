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
ENUM_RANGE_BY_FIRST_AND_LAST(ETileType, ETileType::Blank, ETileType::GrassForest);

static const TMap<ETileType, FString> TileTexturePaths = {
	{ETileType::Blank, "/Script/Engine.Texture2D'/Game/Textures/Environment/T_Blank.T_Blank'"},
	{ETileType::Water, "/Script/Engine.Texture2D'/Game/Textures/Environment/T_Water.T_Water'"},
	{ETileType::Sand, "/Script/Engine.Texture2D'/Game/Textures/Environment/T_Sand.T_Sand'"},
	{ETileType::GrassPlain, "/Script/Engine.Texture2D'/Game/Textures/Environment/T_GrassPlain.T_GrassPlain'"},
	{ETileType::Snow, "/Script/Engine.Texture2D'/Game/Textures/Environment/T_Snow.T_Snow'"},
	{ETileType::GrassForest, "/Script/Engine.Texture2D'/Game/Textures/Environment/T_GrassForest.T_GrassForest'"},
};

static const TMap<ETileType, FString> TileMaterialPaths = {
	{ETileType::Blank, "/Script/Engine.Material'/Game/Materials/M_Terrain.M_Terrain'"},
	{ETileType::Water, "/Script/Engine.Material'/Game/Materials/M_Terrain.M_Terrain'"},
	{ETileType::Sand, "/Script/Engine.Material'/Game/Materials/M_Terrain.M_Terrain'"},
	{ETileType::GrassPlain, "/Script/Engine.Material'/Game/Materials/M_Terrain.M_Terrain'"},
	{ETileType::Snow, "/Script/Engine.Material'/Game/Materials/M_Terrain.M_Terrain'"},
	{ETileType::GrassForest, "/Script/Engine.Material'/Game/Materials/M_Terrain.M_Terrain'"},
};
