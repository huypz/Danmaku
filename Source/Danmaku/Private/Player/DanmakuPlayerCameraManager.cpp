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
	OutCameraView.OrthoWidth = GSystemResolution.ResX * 2 + 1;
}