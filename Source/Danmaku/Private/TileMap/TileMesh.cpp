// © 2024, Huy Phan. All rights reserved.


#include "TileMap/TileMesh.h"

#include "Util/ListPool.h"


template <typename T>
TArray<TArray<T>> TListPool<T>::Stack;

UTileMesh::UTileMesh(const FObjectInitializer& ObjectInitializer) : UProceduralMeshComponent(ObjectInitializer)
{
	bUseAsyncCooking = true;

	
	bBlendTerrain = true;
	bIsDrawn = false;
}

void UTileMesh::AddTriangle(FVector V1, FVector V2, FVector V3)
{
	int32 VertexIndex = Vertices.Num();
	Vertices.Add(V1);
	Vertices.Add(V2);
	Vertices.Add(V3);
	Triangles.Add(VertexIndex);
	Triangles.Add(VertexIndex + 1);
	Triangles.Add(VertexIndex + 2);
}

void UTileMesh::AddTriangleUV(FVector2D UV1, FVector2D UV2, FVector2D UV3)
{
	TextureUVs.Add(UV1);
	TextureUVs.Add(UV2);
	TextureUVs.Add(UV3);
}

void UTileMesh::AddQuad(FVector V1, FVector V2, FVector V3, FVector V4)
{
	int VertexIndex = Vertices.Num();
	Vertices.Add(V1);
	Vertices.Add(V2);
	Vertices.Add(V3);
	Vertices.Add(V4);
	Triangles.Add(VertexIndex);
	Triangles.Add(VertexIndex + 3);
	Triangles.Add(VertexIndex + 2);
	Triangles.Add(VertexIndex);
	Triangles.Add(VertexIndex + 1);
	Triangles.Add(VertexIndex + 3);
}

void UTileMesh::AddQuadUV(FVector2D UV1, FVector2D UV2, FVector2D UV3, FVector2D UV4)
{
	TextureUVs.Add(UV1);
	TextureUVs.Add(UV2);
	TextureUVs.Add(UV3);
	TextureUVs.Add(UV4);
}

void UTileMesh::AddQuadUV(float UMin, float UMax, float VMin, float VMax)
{
	TextureUVs.Add(FVector2D(UMin, VMax));
	TextureUVs.Add(FVector2D(UMax, VMax));
	TextureUVs.Add(FVector2D(UMin, VMin));
	TextureUVs.Add(FVector2D(UMax, VMin));
}

void UTileMesh::AddQuadMaskUV(FVector2D UV1, FVector2D UV2, FVector2D UV3, FVector2D UV4)
{
	BlendUVs.Add(UV1);
	BlendUVs.Add(UV2);
	BlendUVs.Add(UV3);
	BlendUVs.Add(UV4);
}

void UTileMesh::AddQuadMaskUV(float UMin, float UMax, float VMin, float VMax)
{
	BlendUVs.Add(FVector2D(UMin, VMax));
	BlendUVs.Add(FVector2D(UMax, VMax));
	BlendUVs.Add(FVector2D(UMin, VMin));
	BlendUVs.Add(FVector2D(UMax, VMin));
}

void UTileMesh::Clear()
{
	ClearAllMeshSections();
	bIsDrawn = false;

	Vertices = TListPool<FVector>::Get();
	Triangles = TListPool<int32>::Get();
	TextureUVs = TListPool<FVector2D>::Get();
	if (bBlendTerrain)
	{
		BlendUVs = TListPool<FVector2D>::Get();
	}
}

void UTileMesh::Apply()
{
	CreateMeshSection(
		0,
		Vertices,
		Triangles,
		TArray<FVector>(),
		TextureUVs,
		BlendUVs,
		TArray<FVector2D>(),
		TArray<FVector2D>(),
		TArray<FColor>(),
		TArray<FProcMeshTangent>(),
		false
	);

	TListPool<FVector>::Add(Vertices);
	TListPool<int32>::Add(Triangles);
	TListPool<FVector2D>::Add(TextureUVs);
	if (bBlendTerrain)
	{
		TListPool<FVector2D>::Add(BlendUVs);
	}
}
