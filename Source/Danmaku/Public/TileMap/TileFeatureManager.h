// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileFeatureManager.generated.h"


class UTileCell;
class ATileFeature;

UCLASS()
class DANMAKU_API UTileFeatureManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTileFeatureManager();

	void Clear();

	void Apply(TArray<UTileCell*> Cells);

	void SpawnFeature(UTileCell* Cell, TSubclassOf<ATileFeature> FeatureClass);

private:
	UPROPERTY()
	TArray<ATileFeature*> Features;
};
