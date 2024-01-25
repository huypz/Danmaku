// Copyright Huy Phan. All Rights Reserved.


#include "Player/DanmakuPlayerCameraManager.h"

void ADanmakuPlayerCameraManager::DoUpdateCamera(float DeltaTime)
{
	Super::DoUpdateCamera(DeltaTime);

	FMinimalViewInfo CameraCache = GetCameraCacheView();
	UpdateCameraWidth(CameraCache);
	FillCameraCache(CameraCache);
}

void ADanmakuPlayerCameraManager::UpdateCameraWidth(FMinimalViewInfo& OutCameraView)
{
	if (!GEngine)
	{
		return;
	}

	const UGameViewportClient* GameViewport = GEngine->GameViewportForWorld(GetWorld());
	if (GameViewport && GameViewport->Viewport)
	{
		const FVector2D ViewportSize(GameViewport->Viewport->GetSizeXY());
		OutCameraView.ProjectionMode = ECameraProjectionMode::Orthographic;
		OutCameraView.OrthoWidth = 1600.f;
		//OutCameraView.bConstrainAspectRatio = true;
		OutCameraView.AspectRatio = GSystemResolution.ResX / GSystemResolution.ResY;
		//UE_LOG(LogTemp, Warning, TEXT("Game resolution: %d, %d"), GSystemResolution.ResX, GSystemResolution.ResY);
		
	}
}

float ADanmakuPlayerCameraManager::GetPixelArtScale(const FVector2D& InViewportSize)
{
	// Calculate the new art scale factor
	float BasePixelArtScale = (InViewportSize.X / ReferenceResolution.X);

	// Round it up or down
	BasePixelArtScale = (FMath::Frac(BasePixelArtScale) > 0.9f) ? FMath::CeilToFloat(BasePixelArtScale) : FMath::FloorToFloat(BasePixelArtScale);

	// In the extremely rare case where the display resolution is lower than the reference resolution we
	// also need to protect against divisions by zero, although in this case the game will be unplayable :)
	BasePixelArtScale = FMath::Max(1.0f, BasePixelArtScale);
	
	return BasePixelArtScale;
}