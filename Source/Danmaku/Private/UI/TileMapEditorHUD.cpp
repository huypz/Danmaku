// Copyright Huy Phan. All Rights Reserved.


#include "UI/TileMapEditorHUD.h"

#include "EngineUtils.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"
#include "TileMap/TileCell.h"
#include "TileMap/TileGrid.h"

void UTileMapEditorHUD::Save()
{
	FString Path = FPaths::Combine(FPaths::ProjectPersistentDownloadDir(), "test.map");
	FBufferArchive Writer;
	uint32 Header = 0;
	Writer << Header;
	TileGridActor->Save(Writer);
	bool bResult = FFileHelper::SaveArrayToFile(Writer, *Path);
	if (bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully saved tile map: %s"), *Path);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to save tile map: %s"), *Path);
	}
	Writer.FlushCache();
	Writer.Empty();
}

void UTileMapEditorHUD::Load()
{
	FString Path = FPaths::Combine(FPaths::ProjectPersistentDownloadDir(), "test.map");
	TArray<uint8> BinaryArray;
	if (!FFileHelper::LoadFileToArray(BinaryArray, *Path))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load tile map: %s"), *Path);
		return;
	}
	FMemoryReader Reader(BinaryArray, true);
	Reader.Seek(0);
	uint32 Header;
	Reader << Header;
	if (Header == 0)
	{
		TileGridActor->Load(Reader);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unknown map format: %d"), Header);
	}
	
	Reader.FlushCache();
	BinaryArray.Empty();
	Reader.Close();
}

void UTileMapEditorHUD::NativeConstruct()
{
	Super::NativeConstruct();

	for (ATileGrid* Actor : TActorRange<ATileGrid>(GetWorld()))
	{
		TileGridActor = Actor;
	}
}

void UTileMapEditorHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// Get mouse position
	FVector2D MousePosition;
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (APlayerController* PlayerController = GameInstance->GetFirstLocalPlayerController())
		{
			if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
			{
				if (PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
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
							if (TileGridActor)
							{
								UTileCell* Cell = TileGridActor->GetCell(HitResult.ImpactPoint);
								EditCell(Cell);
							}
						}
					}
				}
			}
		}
	}
}

void UTileMapEditorHUD::EditCell(UTileCell* Cell)
{
	if (Cell)
	{
		if (EditMode == EEditMode::Tile)
		{
			Cell->SetTileType(static_cast<ETileType>(ActiveTileType));
		}
		else if (EditMode == EEditMode::Feature)
		{
			Cell->SetFeatureClass(ActiveTileFeatureClass);
		}
	}
}

UTexture2D* UTileMapEditorHUD::GetAssetThumbnail(FString ObjectPath)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(ObjectPath);
	FString PackageFilename;
	if (FPackageName::DoesPackageExist(AssetData.PackageName.ToString(), &PackageFilename))
	{
		FObjectThumbnail ObjectThumbnail;
		ThumbnailTools::LoadThumbnailFromPackage(AssetData, ObjectThumbnail);
		IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));
		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
		ImageWrapper->SetRaw(ObjectThumbnail.GetUncompressedImageData().GetData(), ObjectThumbnail.GetUncompressedImageData().Num(), ObjectThumbnail.GetImageWidth(), ObjectThumbnail.GetImageHeight(), ERGBFormat::BGRA, 8);
		if (ImageWrapper)
		{
			const TArray64<uint8>& CompressedByteArray = ImageWrapper->GetCompressed();
			return FImageUtils::ImportBufferAsTexture2D(CompressedByteArray);  
		}
	}

	return nullptr;
}
