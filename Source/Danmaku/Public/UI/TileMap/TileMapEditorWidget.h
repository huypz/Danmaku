// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "Widgets/SCompoundWidget.h"

class UTileMapEditor;
class SUniformGridPanel;

class FDanmakuUIResources
{};

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

	TArray<TObjectPtr<UTexture2D>> TileTextures;

	TArray<TSharedPtr<FIntPoint>> Resolutions;

	TSharedPtr<FIntPoint> SelectedResolution;
	
	FSlateBrush BorderBrush;
	
	void Construct(const FArguments& InArgs);

	void BuildTileGridPanel();
};