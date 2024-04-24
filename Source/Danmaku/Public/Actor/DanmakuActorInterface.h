// Copyright Huy Phan. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DanmakuActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDanmakuActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DANMAKU_API IDanmakuActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdateRotation(FVector CameraLocation, float Rotation);
};
