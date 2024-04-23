// Copyright Huy Phan. All Rights Reserved.


#include "UI/TileMap/TileMapEditorWidget.h"

#include "SlateOptMacros.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
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
	
	TArray<FIntPoint> SupportedResolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(SupportedResolutions);
	for (const FIntPoint& SupportedResolution : SupportedResolutions)
	{
		Resolutions.Add(MakeShareable(new FIntPoint(SupportedResolution)));
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
						.HeightOverride(50.f)
						[
							SNew(SComboBox<TSharedPtr<FIntPoint>>)
							.OptionsSource(&Resolutions)
							.OnSelectionChanged_Lambda([this](TSharedPtr<FIntPoint> NewValue, ESelectInfo::Type)
							{
								SelectedResolution = NewValue;

								if (GEngine)
								{
									UGameUserSettings* GameUserSettings = GEngine->GetGameUserSettings();
									GameUserSettings->SetScreenResolution(*SelectedResolution);
									GameUserSettings->SetVSyncEnabled(false);
									GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
									GameUserSettings->ApplySettings(false);
								}
							})
							.OnGenerateWidget_Lambda([](TSharedPtr<FIntPoint> InOption)
							{
								return SNew(STextBlock)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16.f))
								.Text(FText::FromString(FString::Printf(TEXT("%dx%d"), InOption->X, InOption->Y)));
							})
							.InitiallySelectedItem(SelectedResolution)
							[
								SNew(STextBlock)
								.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16.f))
								.Text_Lambda([this]()
								{
									return FText::FromString(FString::Printf(TEXT("%dx%d"), SelectedResolution->X, SelectedResolution->Y));
								})
							]
						]
					]
				]
			]
		]
	];

	BuildTileGridPanel();
}

void STileMapEditorWidget::BuildTileGridPanel()
{
	TileGridPanel->ClearChildren();
	
	int32 Index = 0;
	for (const ETileType TileType : TEnumRange<ETileType>())
	{
		UTexture2D* TileTexture = Cast<UTexture2D>(FSoftObjectPath(TileTexturePaths[TileType]).TryLoad());
		if (TileTexture)
		{
			TileTextures.Add(TileTexture);
		}
		TileGridPanel->AddSlot(Index % 4, Index / 4)
		[
			SNew(STileSlotWidget)
			.TileTexture(TileTexture)
			.OnClick(FOnClicked::CreateLambda([this, TileType]
			{
				if (TileMapEditor.IsValid())
				{
					TileMapEditor->SetTileType(TileType);
				}
				return FReply::Handled();
			}))
		];
		Index++;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
