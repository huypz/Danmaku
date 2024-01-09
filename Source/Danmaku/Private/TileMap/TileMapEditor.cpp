// © 2024, Huy Phan. All rights reserved.


#include "TileMap/TileMapEditor.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileGrid.h"
#include "UI/Widget/TileMapEditorWidget.h"


ATileMapEditor::ATileMapEditor()
{
	PrimaryActorTick.bCanEverTick = true;

	ActiveTileType = ETileType::Blank;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATileMapEditor::SetTileTypeIndex(int32 Index)
{
	ActiveTileType = static_cast<ETileType>(Index);
}

void ATileMapEditor::BeginPlay()
{
	Super::BeginPlay();

	Widget = CreateWidget<UTileMapEditorWidget>(GetWorld(), WidgetClass);
	Widget->Editor = this;
	Widget->AddToViewport();
}

void ATileMapEditor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UGameInstance* GameInstance = GetGameInstance())
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

void ATileMapEditor::ProcessInput()
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
				if (TileGrid != nullptr)
				{
					if (ATileCell* CurrentCell = TileGrid->GetCell(HitResult.ImpactPoint))
					{
						EditCell(CurrentCell);
					}
				}
			}
		}
	}
}

void ATileMapEditor::EditCell(ATileCell* Cell)
{
	if (ActiveTileType >= ETileType::Blank)
	{
		Cell->SetTileType(ActiveTileType);
	}
}

