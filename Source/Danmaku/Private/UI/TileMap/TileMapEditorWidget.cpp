// Copyright Huy Phan. All Rights Reserved.


#include "UI/TileMap/TileMapEditorWidget.h"

#include "SlateOptMacros.h"
#include "TileMap/TileMapEditor.h"
#include "TileMap/TileType.h"
#include "UI/TileMap/TileSlotWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void STileMapEditorWidget::Construct(const FArguments& InArgs)
{
	BorderBrush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f, 0.8f));
	
	ChildSlot
	[
		SNew(SConstraintCanvas)
		+ SConstraintCanvas::Slot()
		.Alignment(FVector2D(0.f, 0.f))
		.Anchors(FAnchors(1.f, 0.f))
		.AutoSize(true)
		.Offset(FMargin(-400.f, 0.f))
		[
			SNew(SBox)
			.WidthOverride(400.f)
			.HeightOverride(1080.f)
			[
				SNew(SBorder)
				.BorderImage(&BorderBrush)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					[
						SNew(SBox)
						.WidthOverride(300.f)
						.HeightOverride(300.f)
						[
							SNew(SScrollBox)
							+ SScrollBox::Slot()
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Top)
							[
								SAssignNew(TileGridPanel, SUniformGridPanel)
								.SlotPadding(10.f)
							]
						]
					]
				]
			]
		]
	];

	RebuildFromData(InArgs._TileTextures);
}

void STileMapEditorWidget::RebuildFromData(const TArray<UTexture2D*>& TileTextures)
{
	TileGridPanel->ClearChildren();
	
	int32 Index = 0;
	for (const ETileType TileType : TEnumRange<ETileType>())
	{
		int32 TileTypeIndex = static_cast<int32>(TileType);
		if (TileTypeIndex < TileTextures.Num())
		{
			TileGridPanel->AddSlot(Index % 4, Index / 4)
			[
				SNew(STileSlotWidget)
				.TileTexture(TileTextures[TileTypeIndex])
				.OnClick(FOnClicked::CreateLambda([this, TileType]
				{
					if (TileMapEditor.IsValid())
					{
						TileMapEditor->SetTileType(TileType);
					}
					return FReply::Handled();
				}))
			];
		}
		Index++;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
