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
	
	OutCameraView.ProjectionMode = ECameraProjectionMode::Orthographic;
	OutCameraView.OrthoWidth = 1600.f;
	OutCameraView.bConstrainAspectRatio = true;
	OutCameraView.AspectRatio = GSystemResolution.ResX / GSystemResolution.ResY;
}
