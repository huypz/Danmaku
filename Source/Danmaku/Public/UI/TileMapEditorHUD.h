// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileMapEditorHUD.generated.h"

class ATileFeature;

UENUM()
enum class EEditMode : uint8
{
	Ignore,
	Tile,
	Feature
};

class ATileGrid;
class UTileCell;

/**
 * 
 */
UCLASS(Abstract)
class DANMAKU_API UTileMapEditorHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATileGrid> TileGridActor;
	
	UPROPERTY(BlueprintReadWrite)
	int32 ActiveTileType;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ATileFeature> ActiveTileFeatureClass;

	UPROPERTY(BlueprintReadWrite)
	EEditMode EditMode;

	UFUNCTION(BlueprintCallable)
	void Save();

	UFUNCTION(BlueprintCallable)
	void Load();

protected:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void EditCell(UTileCell* Cell);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetAssetThumbnail(FString ObjectPath);
};
