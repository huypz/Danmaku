// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileMapData.h"
#include "TileType.h"
#include "GameFramework/Actor.h"
#include "TileCell.generated.h"

class UTileMesh;
class ATileChunk;

/**
 * 
 */
UCLASS()
class DANMAKU_API ATileCell : public AActor
{
	GENERATED_BODY()

	enum EMask : uint8
	{
		SideMask1,
		SideMask2,
		SideMask3,
		InnerMask1,
		InnerMask2,
		InnerPMask1,
		InnerPMask2,
		OuterMask,
	};
	
public:
	UPROPERTY()
	TObjectPtr<ATileChunk> Chunk;

	UPROPERTY(VisibleAnywhere)
	FTileCoordinates Coordinates;
	
	ATileCell();

	void TriangulateTile();

	void TriangulateBlend();

	void Triangulate();

	void SetMaterial(int32 Index, UMaterial* NewMaterial);

	void SetTileType(ETileType NewTileType);

	void SetNeighbor(ETileDirection Direction, ATileCell* Cell);

	ATileCell* GetNeighbor(ETileDirection Direction) const;

	ATileCell* GetNeighbor(uint8 Direction) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	ETileType TileType;
	
	UPROPERTY(VisibleAnywhere)
	TArray<ATileCell*> Neighbors;

	UPROPERTY()
	TObjectPtr<UTileMesh> TileMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterialInstanceDynamic> TileMaterial;

	UPROPERTY()
	TArray<UTileMesh*> BlendMeshes;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> BlendMaterials;

	void Refresh();

	void RefreshSelf();
};
