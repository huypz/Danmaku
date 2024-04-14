// Copyright Huy Phan. All Rights Reserved.


#include "Player/DanmakuPlayerState.h"

#include "GAS/DanmakuAbilitySystemComponent.h"
#include "GAS/DanmakuAttributeSet.h"

ADanmakuPlayerState::ADanmakuPlayerState()
{
	NetUpdateFrequency = 128.f;

	AbilitySystemComponent = CreateDefaultSubobject<UDanmakuAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UDanmakuAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ADanmakuPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ADanmakuPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
