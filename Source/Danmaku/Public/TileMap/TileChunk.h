// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileChunk.generated.h"

#define MASK_DEFAULT_1 0
#define MASK_DEFAULT_2 1
#define MASK_DEFAULT_3 2
#define MASK_DEFAULT_4 3

#define MASK_SIDE_BOTTOM_3 4
#define MASK_SIDE_BOTTOM_4 5
#define MASK_SIDE_LEFT_1 6
#define MASK_SIDE_LEFT_3 7
#define MASK_SIDE_RIGHT_2 8
#define MASK_SIDE_RIGHT_4 9
#define MASK_SIDE_TOP_1 10
#define MASK_SIDE_TOP_2 11

#define MASK_INNER_1 12
#define MASK_INNER_2 13
#define MASK_INNER_3 14
#define MASK_INNER_4 15

#define MASK_OUTER_1 16
#define MASK_OUTER_2 17
#define MASK_OUTER_3 18
#define MASK_OUTER_4 19

class ATileFeature;
class UTileCell;

UCLASS()
class DANMAKU_API ATileChunk : public AActor
{
	GENERATED_BODY()

public:
	ATileChunk();

	void TriangulateTile(UTileCell* Cell, const int32& Index);

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