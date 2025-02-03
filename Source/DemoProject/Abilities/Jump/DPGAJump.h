// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Abilities/DPGameplayAbility.h"

#include "DPGAJump.generated.h"

class ADPCharacter;

/**
 * Ability that make the character jump
 */
UCLASS()
class DEMOPROJECT_API UDPGAJump : public UDPGameplayAbility
{
	GENERATED_BODY()

public:

	UDPGAJump();

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;		

	// Function to call when landing
	UFUNCTION()
	virtual void OnLanded(const FHitResult& Hit);

protected:

	virtual void FinishingAbility() override;

	// Ability OwnerCharacter
	TObjectPtr<ADPCharacter> OwnerCharacter = nullptr;
};
