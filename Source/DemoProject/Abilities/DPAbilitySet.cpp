// This project belongs to Daniel Corredor, Use it only for study purposes.

#include "DPAbilitySet.h"

#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DPAbilitySet)

DEFINE_LOG_CATEGORY(LogAbilitySet);

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPAbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* abilitySystem, UObject* SourceObject) const
{
	// Grant the attribute sets.
	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		const FAttributeDefaults& SetToGrant = GrantedAttributes[SetIndex];

		if (!IsValid(SetToGrant.Attributes))
		{
			UE_LOG(LogAbilitySet, Error, TEXT("GrantedAttributeSet[%d] on ability set [%s] is not valid"), SetIndex, *GetNameSafe(this));
			continue;
		}

		if (!SetToGrant.DefaultStartingTable)
		{
			UE_LOG(LogAbilitySet, Error, TEXT("DefaultStartingTable for GrantedAttributes[%d] on ability set [%s] is not valid"), SetIndex, *GetNameSafe(this));
			continue;
		}

		UAttributeSet* NewSet = NewObject<UAttributeSet>(abilitySystem->GetOwner(), SetToGrant.Attributes);
		NewSet->InitFromMetaDataTable(SetToGrant.DefaultStartingTable);
		abilitySystem->AddSpawnedAttribute(NewSet);
	}

	// Grant the gameplay abilities.
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FDPGameplayAbility_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogAbilitySet, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		FGameplayAbilitySpecHandle AbilitySpecHandle = abilitySystem->GiveAbility(AbilitySpec);
	}

	for (int32 effectIndex = 0; effectIndex < GrantedGameplayEffects.Num(); ++effectIndex)
	{
		const auto& effectToGrant = GrantedGameplayEffects[effectIndex];		
		FGameplayEffectSpecHandle EffectSpecHandle = abilitySystem->MakeOutgoingSpec(effectToGrant.GameplayEffect,effectToGrant.EffectLevel, abilitySystem->MakeEffectContext());

		if (EffectSpecHandle.IsValid())
		{		
			abilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
	}
}
