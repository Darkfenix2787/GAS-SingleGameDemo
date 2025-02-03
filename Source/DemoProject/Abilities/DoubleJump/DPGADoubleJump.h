// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Abilities/Jump/DPGAJump.h"
#include "DPGADoubleJump.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPGADoubleJump : public UDPGAJump
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Ability Activation")
	float AdditionalJumpZVelocity;

public:

	UDPGADoubleJump();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;	

	virtual void FinishingAbility();

protected:

	void DoubleJump();		
};
