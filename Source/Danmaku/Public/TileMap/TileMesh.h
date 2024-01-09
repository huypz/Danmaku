// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileMesh.generated.h"

class UProceduralMeshComponent;

/**
 * 
 */
UCLASS()
class DANMAKU_API UTileMesh : public UObject
{
	GENERATED_BODY()

public:
	bool bIsDrawn;
	
	UTileMesh();

	void AddTriangle(FVector V1, FVector V2, FVector V3);

	void AddTriangleUV(FVector2D UV1, FVector2D UV2, FVector2D UV3);

	void AddQuad(FVector V1, FVector V2, FVector V3, FVector V4);

	void AddQuadUV(FVector2D UV1, FVector2D UV2, FVector2D UV3, FVector2D UV4);

	void AddQuadUV(float UMin, float UMax, float VMin, float VMax);

	void AddQuadMaskUV(FVector2D UV1, FVector2D UV2, FVector2D UV3, FVector2D UV4);

	void AddQuadMaskUV(float UMin, float UMax, float VMin, float VMax);

	void SetMaterial(int32 Index, UMaterialInterface* Material);

	void SetTranslucentSortPriority(int32 NewTranslucentSortPriority);

	void Clear();

	void Apply();
	
private:
	UPROPERTY()
	TObjectPtr<UProceduralMeshComponent> Mesh;

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int32> Triangles;

	UPROPERTY()
	TArray<FVector2D> TextureUVs;

	UPROPERTY()
	TArray<FVector2D> BlendUVs;
	
	bool bBlendTerrain;
};
