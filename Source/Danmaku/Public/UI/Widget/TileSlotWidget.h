// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileMap/TileType.h"
#include "TileSlotWidget.generated.h"

class UButton;
class UImage;

/**
 * 
 */
UCLASS()
class DANMAKU_API UTileSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 TileType;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterial> TileMaterial;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> SlotButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> SlotTexture;
};
