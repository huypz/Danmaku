// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TileType.h"
#include "GameFramework/Pawn.h"
#include "TileMapEditor.generated.h"

class UTileMapEditorWidget;
class ATileGrid;
class ATileCell;

UCLASS()
class DANMAKU_API ATileMapEditor : public APawn
{
	GENERATED_BODY()

public:
	ATileMapEditor();

	UFUNCTION(BlueprintCallable, Category = "TileMap")
	void SetTileTypeIndex(int32 Index);

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<ATileGrid> TileGrid;

	UPROPERTY()
	TObjectPtr<UTileMapEditorWidget> Widget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;
	
	ETileType ActiveTileType;

	void ProcessInput();

	void EditCell(ATileCell* Cell);
};
