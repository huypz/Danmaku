// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "TileMesh.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API UTileMesh : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	bool bIsDrawn;
	
	UTileMesh(const FObjectInitializer& ObjectInitializer);

	void AddTriangle(FVector V1, FVector V2, FVector V3);

	void AddTriangleUV(FVector2D UV1, FVector2D UV2, FVector2D UV3);

	void AddQuad(FVector V1, FVector V2, FVector V3, FVector V4);

	void AddQuadUV(FVector2D UV1, FVector2D UV2, FVector2D UV3, FVector2D UV4);

	void AddQuadUV(float UMin, float UMax, float VMin, float VMax);

	void AddQuadMaskUV(FVector2D UV1, FVector2D UV2, FVector2D UV3, FVector2D UV4);

	void AddQuadMaskUV(float UMin, float UMax, float VMin, float VMax);

	void Clear();

	void Apply();
	
private:
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
