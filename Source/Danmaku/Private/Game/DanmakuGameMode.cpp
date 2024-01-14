// Copyright Huy Phan. All Rights Reserved.


#include "Game/DanmakuGameMode.h"

#include "Character/DanmakuCharacter.h"
#include "Player/DanmakuPlayerController.h"
#include "UI/DanmakuHUD.h"

ADanmakuGameMode::ADanmakuGameMode()
{
	DefaultPawnClass = ADanmakuCharacter::StaticClass();
	HUDClass = ADanmakuHUD::StaticClass();
	PlayerControllerClass = ADanmakuPlayerController::StaticClass();
}
