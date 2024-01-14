// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "Widgets/SCompoundWidget.h"

class UTileMapEditor;
class SUniformGridPanel;

/**
 * 
 */
class DANMAKU_API STileMapEditorWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STileMapEditorWidget)
		{}
		SLATE_ARGUMENT(TArray<UTexture2D*>, TileTextures)
	SLATE_END_ARGS()

	TWeakObjectPtr<UTileMapEditor> TileMapEditor;

	TSharedPtr<SUniformGridPanel> TileGridPanel;

	FSlateBrush BorderBrush;
	
	void Construct(const FArguments& InArgs);

	void RebuildFromData(const TArray<UTexture2D*>& TileTextures);
};
