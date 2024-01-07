// © 2024, Huy Phan. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/DanmakuCharacterBase.h"
#include "DanmakuPlayerCharacter.generated.h"

class UCameraComponent;
class UPaperSpriteComponent;
class UPaperSprite;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class DANMAKU_API ADanmakuPlayerCharacter : public ADanmakuCharacterBase
{
	GENERATED_BODY()

public:
	ADanmakuPlayerCharacter();

private:
	TObjectPtr<USpringArmComponent> CameraSpringArmComponent;

	TObjectPtr<UCameraComponent> CameraComponent;
	
};
