// Copyright Huy Phan. All Rights Reserved.


#include "Game/DanmakuGameViewportClient.h"

void UDanmakuGameViewportClient::Activated(FViewport* InViewport, const FWindowActivateEvent& InActivateEvent)
{
	Super::Activated(InViewport, InActivateEvent);
	
	ApplyViewMode(EViewModeIndex::VMI_Unlit, false, EngineShowFlags);
}