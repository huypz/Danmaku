// © 2024, Huy Phan. All rights reserved.


#include "UI/Widget/TileMapEditorWidget.h"

#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "TileMap/TileType.h"
#include "UI/Widget/TileSlotWidget.h"

void UTileMapEditorWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TileSlotClass)
	{
		int32 Index = 0;
		for (ETileType Type : TEnumRange<ETileType>())
		{
			TileSlot = CreateWidget<UTileSlotWidget>(this, TileSlotClass);
			TileSlot->TileType = static_cast<int32>(Type);
			
			// Load texture
			if (UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *TileTexturePaths[Type]))
			{
				TileSlot->SlotTexture->SetBrushFromTexture(Texture, false);
			}
			
			TileGridPanel->AddChildToUniformGrid(TileSlot, Index / 3, Index % 3);
			Index++;
		}
	}
}
