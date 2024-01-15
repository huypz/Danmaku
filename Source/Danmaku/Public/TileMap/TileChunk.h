// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileBlendParams.h"
#include "GameFramework/Actor.h"
#include "TileChunk.generated.h"

class ATileFeature;
class UTileCell;

UCLASS()
class DANMAKU_API ATileChunk : public AActor
{
	GENERATED_BODY()

public:
	ATileChunk();

	void TriangulateTile(UTileCell* Cell, const int32& Index);
	
	void TriangulateBlend(UTileCell* Cell, int32& Index);

	void Triangulate();

	void AddCell(int32 Index, UTileCell* Cell);

	void AddFeature(const FVector& Position);

	void Refresh();

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UTileCell*> Cells;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInstancedStaticMeshComponent> InstancedStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TArray<ATileFeature*> Features;
};
