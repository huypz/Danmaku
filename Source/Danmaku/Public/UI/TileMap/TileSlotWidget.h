// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class DANMAKU_API STileSlotWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STileSlotWidget)
		{}
		SLATE_ARGUMENT(UTexture2D*, TileTexture)
		SLATE_ARGUMENT(FOnClicked, OnClick)
	SLATE_END_ARGS()
	
	FButtonStyle ButtonStyle;
	
	FSlateBrush ImageBrush;
	
	void Construct(const FArguments& InArgs);
	
};
