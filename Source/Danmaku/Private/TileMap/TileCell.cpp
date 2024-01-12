// © 2024, Huy Phan. All rights reserved.


#include "TileMap/TileCell.h"

#include "Core/DanmakuPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "TileMap/TileChunk.h"
#include "TileMap/TileMapData.h"
#include "TileMap/TileMesh.h"
#include "TileMap/TileType.h"

ATileCell::ATileCell()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	Neighbors.SetNum(8);
	BlendMeshes.SetNum(12);
	BlendMaterials.SetNum(12);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	TileMesh = CreateDefaultSubobject<UTileMesh>(TEXT("MeshComponent"));
	TileMesh->SetupAttachment(RootComponent);
	for (uint8 i = 0; i < 12; i++)
	{
		BlendMeshes[i] = CreateDefaultSubobject<UTileMesh>(*FString::Printf(TEXT("BlendMeshComponent%d"), i));
		BlendMeshes[i]->SetupAttachment(RootComponent);
	}
}

void ATileCell::TriangulateTile()
{
	FVector V1 =  UTileMetrics::Edges[ETileDirection::SouthWest];
	FVector V2 =  UTileMetrics::Edges[ETileDirection::SouthEast];
	FVector V3 =  UTileMetrics::Edges[ETileDirection::NorthWest];
	FVector V4 =  UTileMetrics::Edges[ETileDirection::NorthEast];

	TileMesh->AddQuad(V1, V2, V3, V4);
	TileMesh->AddQuadUV(0.f, 1.f, 0.f, 1.f);
	TileMesh->AddQuadMaskUV(0.f, 1.f, 0.f, 1.f);
	TileMesh->bIsDrawn = true;
}

void ATileCell::TriangulateBlend()
{
	ETileDirection Sides[] = { ETileDirection::North, ETileDirection::East, ETileDirection::South, ETileDirection::West };
	for (int32 i = 0; i < 4; i++)
	{
		if (
			ETileDirection Side = Sides[i];
			GetNeighbor(Side) != nullptr &&
			GetNeighbor(Side)->TileType < TileType
		)
		{
			FVector V1 = UTileMetrics::Edges[Side - 1];
			FVector V2 = UTileMetrics::Edges[Side];
			FVector V3 = UTileMetrics::Edges[Side + 1];

			// Side left half quad
			if (
				ETileDirection Side1 = Side - 1;
				GetNeighbor(Side1) == nullptr ||
				!(GetNeighbor(Side1)->TileType == TileType && GetNeighbor(Side1)->BlendMeshes[(Side1 < 4 ? Side1 + 4 : Side1 - 4)]->bIsDrawn)
			)
			{
				BlendMeshes[Side]->AddQuad(V1, V2, V1 + UTileMetrics::Edges[Side], V2 + UTileMetrics::Edges[Side]);
				if (Side == ETileDirection::North)
				{
					BlendMeshes[Side + 0]->AddQuadUV({0.f, 1.f}, {0.5f, 1.f}, {0.f, 0.5f}, {0.5f, 0.5f});
				}
				else if (Side == ETileDirection::East)
				{
					BlendMeshes[Side + 0]->AddQuadUV({0.f, 0.f}, {0.f, 0.5f}, {0.5f, 0.f}, {0.5f, 0.5f});
				}
				else if (Side == ETileDirection::South)
				{
					BlendMeshes[Side]->AddQuadUV({1.f, 0.f}, {0.5f, 0.f}, {1.f, 0.5f}, {0.5f, 0.5f});
				}
				else if (Side == ETileDirection::West)
				{
					BlendMeshes[Side]->AddQuadUV({1.f, 1.f}, {1.f, 0.5f}, {0.5f, 1.f}, {0.5f, 0.5f});
				}
				BlendMeshes[Side]->AddQuadMaskUV(0.f, 1.f, 0.f, 1.f);
				
				uint8 MaskTypeIndex = 0;
				if (GetNeighbor(Side1) == nullptr)
				{
					MaskTypeIndex = FMath::RandRange(EMask::SideMask1, EMask::SideMask3);
				}
				else if (GetNeighbor(Side1)->TileType == TileType)
				{
					MaskTypeIndex = EMask::InnerMask1;
				}
				else if (GetNeighbor(Side1)->TileType > TileType)
				{
					MaskTypeIndex = EMask::InnerPMask1;
				}
				BlendMaterials[Side]->SetScalarParameterValue(FName(TEXT("MaskTypeIndex")), MaskTypeIndex);
				BlendMeshes[Side]->bIsDrawn = true;
			}

			// Side right half quad
			if (
				ETileDirection Side2 = Side + 1;
				GetNeighbor(Side2) == nullptr ||
				!(GetNeighbor(Side2)->TileType == TileType && GetNeighbor(Side2)->BlendMeshes[(Side2 < 4 ? Side2 + 4 : Side2 - 4) + 1]->bIsDrawn)
			)
			{
				BlendMeshes[Side + 1]->AddQuad(V2, V3, V2 + UTileMetrics::Edges[Side], V3 + UTileMetrics::Edges[Side]);
				BlendMeshes[Side + 1]->AddQuadUV(0.5f, 1.f, 0.f, 0.5f);
				if (Side == ETileDirection::North)
				{
					BlendMeshes[Side + 1]->AddQuadUV({0.5f, 1.f}, {1.f, 1.f}, {0.5f, 0.5f}, {1.f, 0.5f});
				}
				else if (Side == ETileDirection::East)
				{
					BlendMeshes[Side + 1]->AddQuadUV({0.f, 0.5f}, {0.f, 1.f}, {0.5f, 0.5f}, {0.5f, 1.f});
				}
				else if (Side == ETileDirection::South)
				{
					BlendMeshes[Side + 1]->AddQuadUV({0.5f, 0.f}, {0.f, 0.f}, {0.5f, 0.5f}, {0.f, 0.5f});
				}
				else if (Side == ETileDirection::West)
				{
					BlendMeshes[Side + 1]->AddQuadUV({1.f, 0.5f}, {1.f, 0.f}, {0.5f, 0.5f}, {0.5f, 0.f});
				}
				BlendMeshes[Side + 1]->AddQuadMaskUV(0.f, 1.f, 0.f, 1.f);
				int32 MaskTypeIndex = 0;
				if (GetNeighbor(Side2) == nullptr)
				{
					MaskTypeIndex = FMath::RandRange(EMask::SideMask1, EMask::SideMask3);
				}
				else if (GetNeighbor(Side2)->TileType == TileType)
				{
					MaskTypeIndex = EMask::InnerMask2;
				}
				else if (GetNeighbor(Side2)->TileType > TileType)
				{
					MaskTypeIndex = EMask::InnerPMask2;
				}
				BlendMaterials[Side + 1]->SetScalarParameterValue(FName(TEXT("MaskTypeIndex")), MaskTypeIndex);
				BlendMeshes[Side + 1]->bIsDrawn = true;
			}
		}
	}

	ETileDirection Corners[] = { ETileDirection::NorthWest, ETileDirection::NorthEast, ETileDirection::SouthEast, ETileDirection::SouthWest };
	for (int32 i = 0; i < 4; i++)
	{
		ETileDirection Corner = Corners[i];
		// Triangulate top-left corner triangle (EXAMPLE) IF
		if (
			// Top-left tile exists
			GetNeighbor(Corner) != nullptr &&
			// Top-left tile is lower priority
			GetNeighbor(Corner)->TileType < TileType &&
			// Top tile is not blending into top-right tile
			GetNeighbor(Corner + 1)->TileType <= GetNeighbor(Corner)->TileType &&
			// Left tile should not be blending into top-left tile
			GetNeighbor(Corner - 1) != nullptr && GetNeighbor(Corner - 1)->TileType <= GetNeighbor(Corner)->TileType
		)
		{
			FVector V2 = UTileMetrics::Edges[Corner];
			FVector V1 = V2 + UTileMetrics::Edges[Corner - 1];
			FVector V3 = V1 + UTileMetrics::Edges[Corner + 1];
			FVector V4 = V2 + UTileMetrics::Edges[Corner + 1];
			BlendMeshes[i + 8]->AddQuad(V1, V2, V3, V4);
			BlendMeshes[i + 8]->AddQuadUV(0.5f, 1.f, 0.5f, 1.f);
			BlendMeshes[i + 8]->AddQuadMaskUV(0.f, 1.f, 0.f, 1.f);
			BlendMeshes[i + 8]->bIsDrawn = true;
			BlendMaterials[i + 8]->SetScalarParameterValue(FName(TEXT("MaskTypeIndex")), EMask::OuterMask);
		}
	}
}

void ATileCell::Triangulate()
{
	TileMesh->Clear();
	for (UTileMesh* BlendMesh : BlendMeshes)
	{
		BlendMesh->Clear();
	}

	TriangulateTile();
	TriangulateBlend();

	TileMesh->Apply();
	for (UTileMesh* BlendMesh : BlendMeshes)
	{
		BlendMesh->Apply();
	}
}

void ATileCell::SetMaterial(int32 Index, UMaterial* NewMaterial)
{
	if (!NewMaterial)
	{
		return;
	}
	
	TileMaterial = UMaterialInstanceDynamic::Create(NewMaterial, this);
	TileMaterial->SetScalarParameterValue(FName(TEXT("bIsBlend")), 0.f);
	TileMesh->SetMaterial(Index, TileMaterial);
	for (uint8 i = 0; i < BlendMeshes.Num(); i++)
	{
		BlendMaterials[i] = UMaterialInstanceDynamic::Create(NewMaterial, this);
		BlendMaterials[i]->SetScalarParameterValue(FName(TEXT("bIsBlend")), 1.f);
		BlendMeshes[i]->SetMaterial(Index, BlendMaterials[i]);
	}
}

void ATileCell::SetTileType(ETileType NewTileType, bool bForceRefresh)
{
	if (!bForceRefresh && TileType == NewTileType)
	{
		return;
	}
	
	uint32 TypeIndex = static_cast<uint32>(NewTileType);
	if (UMaterial* Material = LoadObject<UMaterial>(nullptr, *TileMaterialPaths[TileType]))
	{
		SetMaterial(0, Material);
		TileMaterial->SetScalarParameterValue(FName(TEXT("TerrainTypeIndex")), TypeIndex);
		TileMesh->SetTranslucentSortPriority(TypeIndex);
		
		for (uint8 i = 0; i < BlendMeshes.Num(); i++)
		{
			BlendMaterials[i]->SetScalarParameterValue(FName(TEXT("TerrainTypeIndex")), TypeIndex);
			BlendMeshes[i]->SetTranslucentSortPriority(TypeIndex);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATileCell::SetTileType failed to load material"));
	}

	TileType = NewTileType;
	Refresh();
}

void ATileCell::SetNeighbor(ETileDirection Direction, ATileCell* Cell)
{
	Neighbors[Direction] = Cell;
	Cell->Neighbors[Direction < 4 ? Direction + 4 : Direction - 4] = this;
}

ATileCell* ATileCell::GetNeighbor(ETileDirection Direction) const
{
	return Neighbors[static_cast<uint8>(Direction)];
}

ATileCell* ATileCell::GetNeighbor(uint8 Direction) const
{
	return Neighbors[Direction];
}

void ATileCell::BeginPlay()
{
	Super::BeginPlay();
	
	SetTileType(TileType, true);
}

void ATileCell::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATileCell, TileType);
}

bool ATileCell::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (const ADanmakuPlayerController* PC = Cast<ADanmakuPlayerController>(RealViewer))
	{
		return PC->bClientFinishProceduralGeneration && Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}
	
	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

void ATileCell::OnRep_TileType()
{
	SetTileType(TileType, true);
}

void ATileCell::Refresh()
{
	if (Chunk != nullptr)
	{
		Chunk->Refresh();
		for (ATileCell* Neighbor : Neighbors)
		{
			if (Neighbor != nullptr && Neighbor->Chunk != Chunk)
			{
				Neighbor->Chunk->Refresh();
			}
		}
	}
}

void ATileCell::RefreshSelf()
{
	Chunk->Refresh();
}
