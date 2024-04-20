// Copyright Huy Phan. All Rights Reserved.


#include "GAS/DanmakuAttributeSet.h"

#include "Net/UnrealNetwork.h"

UDanmakuAttributeSet::UDanmakuAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void UDanmakuAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UDanmakuAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UDanmakuAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UDanmakuAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UDanmakuAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

void UDanmakuAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDanmakuAttributeSet, Health, OldHealth)
}

void UDanmakuAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDanmakuAttributeSet, MaxHealth, OldMaxHealth)
}

void UDanmakuAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDanmakuAttributeSet, Mana, OldMana)
}

void UDanmakuAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDanmakuAttributeSet, MaxMana, OldMaxMana)
}
