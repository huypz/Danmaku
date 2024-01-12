// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileChunk.generated.h"

class ATileCell;

/**
 * 
 */
UCLASS()
class DANMAKU_API ATileChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileChunk();

	void Triangulate();
	
	void AddCell(int32 Index, ATileCell* Cell);

	void Refresh();

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	
private:
	UPROPERTY()
	TArray<ATileCell*> Cells;
};
