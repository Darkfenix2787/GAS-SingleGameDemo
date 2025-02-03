// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Abilities/DPGameplayAbility.h"
#include "DPGAAttack.generated.h"

/**
 * 
 */
UCLASS()
class DEMOPROJECT_API UDPGAAttack : public UDPGameplayAbility
{
	GENERATED_BODY()

public:

	UDPGAAttack();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// Called function from delegate when the animation is completed
	UFUNCTION()
	void OnAnimationCompleted();

	// Callback function for the Collision delegate when a tag is added to the owner
	UFUNCTION()
	void OnCollisionTagAdded();

	// Callback function for the Collision delegate when a tag is added to the owner
	UFUNCTION()
	void OnCollisionTagRemoved();

	// Callback function for the Combo delegate when a tag is added to the owner
	UFUNCTION()
	virtual void OnComboTagAdded();

	// Callback function for the Combo delegate when a tag is added to the owner
	UFUNCTION()
	virtual void OnComboTagRemoved();

	virtual void BindCollisionTagCallbacks();
	virtual void BindComboTagCallbacks();

	void EnableCollision(bool bEnable);
	
	int32 DefaultDamageMultiplier = 1;

public:

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityDamageMultiplier = 1;


	
};
