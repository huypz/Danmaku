// Copyright Huy Phan. All Rights Reserved.


#include "TileMap/TileMapEditor.h"

#include "Kismet/GameplayStatics.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileGrid.h"
#include "UI/TileMap/TileMapEditorWidget.h"


UTileMapEditor::UTileMapEditor()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	for (const ETileType TileType : TEnumRange<ETileType>())
	{
		ConstructorHelpers::FObjectFinder<UTexture2D> TileTexture(*TileTexturePaths[TileType]);
		if (TileTexture.Succeeded())
		{
			TileTextures.Add(TileTexture.Object);
		}
	}

	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	for (const FIntPoint& Resolution : Resolutions)
	{
		SupportedResolutions.Add(FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y));
	}

	ActiveTileType = ETileType::Blank;
}

void UTileMapEditor::SetTileType(ETileType TileType)
{
	ActiveTileType = TileType;
}

void UTileMapEditor::BeginPlay()
{
	Super::BeginPlay();

	TileMapEditorWidget = SNew(STileMapEditorWidget)
		.TileTextures(TileTextures)
		.Resolutions(SupportedResolutions);
	TileMapEditorWidget->TileMapEditor = this;

	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
	ViewportClient->AddViewportWidgetContent(TileMapEditorWidget.ToSharedRef());
}

void UTileMapEditor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController())
		{
			if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
			{
				ProcessInput();
			}
		}
	}
}

void UTileMapEditor::ProcessInput()
{
	// Get mouse position
	FVector2D MousePosition;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
	{
		// Perform raycast
		FVector WorldPosition;
		FVector WorldDirection;
		if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, WorldPosition, WorldDirection))
		{
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition, WorldPosition + WorldDirection * 10000.f, ECC_Visibility, CollisionParams))
			{
				if (TileGrid)
				{
					if (UTileCell* Cell = TileGrid->GetCell(HitResult.ImpactPoint))
					{
						EditCell(Cell);
					}
				}
			}
		}
	}
}

void UTileMapEditor::EditCell(UTileCell* Cell)
{
	Cell->SetTileType(ActiveTileType);
}

