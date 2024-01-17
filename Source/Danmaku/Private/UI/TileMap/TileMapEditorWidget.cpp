// Copyright Huy Phan. All Rights Reserved.


#include "UI/TileMap/TileMapEditorWidget.h"

#include "SlateOptMacros.h"
#include "GameFramework/GameUserSettings.h"
#include "TileMap/TileMapEditor.h"
#include "TileMap/TileType.h"
#include "UI/TileMap/TileSlotWidget.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void STileMapEditorWidget::Construct(const FArguments& InArgs)
{
	BorderBrush.TintColor = FSlateColor(FLinearColor(0.f, 0.f, 0.f, 0.8f));

	for (const FString& Resolution : InArgs._Resolutions)
	{
		Resolutions.Add(MakeShareable(new FString(Resolution)));
	}
	SelectedResolution = Resolutions[0];
	
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
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
					[
						SNew(SBox)
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
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					[
						SNew(SBox)
						.WidthOverride(300.f)
						.HeightOverride(75.f)
						[
							SNew(SComboBox<TSharedPtr<FString>>)
							.OptionsSource(&Resolutions)
							.OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewValue, ESelectInfo::Type)
							{
								SelectedResolution = NewValue;

								if (GEngine)
								{
									UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
									GameUserSettings->SetScreenResolution(FIntPoint(800, 600));
									GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
									//GameUserSettings->SaveSettings();
									GameUserSettings->ApplySettings(false);
								}
							})
							.OnGenerateWidget_Lambda([](TSharedPtr<FString> InOption)
							{
								return SNew(STextBlock)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16.f))
								.Text(FText::FromString(*InOption));
							})
							.InitiallySelectedItem(SelectedResolution)
							[
								SNew(STextBlock)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16.f))
								.Text_Lambda([this]()
								{
									if (SelectedResolution.IsValid())
									{
										return FText::FromString(*SelectedResolution);
									}
									return NSLOCTEXT("Danmaku", "InvalidComboEntryText", "<Invalid option>");
								})
							]
						]
					]
				]
			]
		]
	];

	BuildTileGridPanel(InArgs._TileTextures);
}

void STileMapEditorWidget::BuildTileGridPanel(const TArray<UTexture2D*>& TileTextures)
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
