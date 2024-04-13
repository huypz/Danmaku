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

protected:
	virtual void DoUpdateCamera(float DeltaTime) override;
	
	void UpdateCameraWidth(FMinimalViewInfo& OutCameraView);
	
};
