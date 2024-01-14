// Copyright Huy Phan. All Rights Reserved.


#include "UI/TileMap/TileSlotWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void STileSlotWidget::Construct(const FArguments& InArgs)
{
	ButtonStyle.NormalPadding = 0.f;
	ButtonStyle.PressedPadding = 0.f;

	if (InArgs._TileTexture)
	{
		ImageBrush.SetResourceObject(InArgs._TileTexture);
	}
	
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(64.f)
		.HeightOverride(64.f)
		[
			SNew(SButton)
			.ButtonStyle(&ButtonStyle)
			.ContentPadding(0.f)
			.OnClicked(InArgs._OnClick)
			[
				SNew(SImage)
				.Image(&ImageBrush)
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
