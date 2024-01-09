// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileMapEditorWidget.generated.h"

class ATileMapEditor;
class UTileSlotWidget;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class DANMAKU_API UTileMapEditorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATileMapEditor> Editor;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> TileGridPanel;

	UPROPERTY()
	TObjectPtr<UTileSlotWidget> TileSlot;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TileSlotClass;

protected:
	virtual void NativePreConstruct() override;
};
