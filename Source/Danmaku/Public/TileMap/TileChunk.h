﻿// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileBlendParams.h"
#include "GameFramework/Actor.h"
#include "TileChunk.generated.h"

class UTileCell;

UCLASS()
class DANMAKU_API ATileChunk : public AActor
{
	GENERATED_BODY()

public:
	ATileChunk();

	void TriangulateTile();
	
	void TriangulateBlend();

	void Triangulate();

	void AddCell(int32 Index, UTileCell* Cell);

	void Refresh();

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UTileCell*> Cells;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInstancedStaticMeshComponent> InstancedStaticMeshComponent;
};
