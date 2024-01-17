// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileType.h"
#include "Components/ActorComponent.h"
#include "TileMapEditor.generated.h"


class STileMapEditorWidget;
class UTileCell;
class ATileGrid;

UCLASS()
class DANMAKU_API UTileMapEditor : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<ATileGrid> TileGrid;
	
	UTileMapEditor();

	void SetTileType(ETileType TileType);

protected:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TSharedPtr<STileMapEditorWidget> TileMapEditorWidget;

	UPROPERTY()
	TArray<UTexture2D*> TileTextures;

	UPROPERTY()
	TArray<FString> SupportedResolutions;

	ETileType ActiveTileType;

	void ProcessInput();

	void EditCell(UTileCell* Cell);
};
