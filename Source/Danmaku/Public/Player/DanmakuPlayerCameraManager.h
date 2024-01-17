// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "DanmakuPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	const FVector2D ReferenceResolution = FVector2D(640.f, 360.f);

	const float ReferencePixelsPerUnit = 0.64f;

	const float ZoomFactor = 3.f;

protected:
	virtual void DoUpdateCamera(float DeltaTime) override;
	
	void UpdateCameraWidth(FMinimalViewInfo& OutCameraView);

	float GetPixelArtScale(const FVector2D& InViewportSize);
};
