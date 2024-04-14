// Copyright Huy Phan. All Rights Reserved.


#include "Character/Enemy/DanmakuEnemy.h"

#include "GAS/DanmakuAbilitySystemComponent.h"
#include "GAS/DanmakuAttributeSet.h"

ADanmakuEnemy::ADanmakuEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDanmakuAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UDanmakuAttributeSet>("AttributeSet");
}

void ADanmakuEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
