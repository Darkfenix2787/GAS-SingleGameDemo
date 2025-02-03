// This project belongs to Daniel Corredor, Use it only for study purposes.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "Logging/LogMacros.h"
#include "DPGameplayAbility.generated.h"

class ADPCharacter;
class UAnimMontage;
class UAbilityTask_PlayMontageAndWait;

UENUM(BlueprintType)
enum class ETHABAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar spawns in the world (is first granted their ability set)
	OnSpawn,

	// Try to activate the ability when granted to the Avatar (should be used for passive abilities that need to be activated
	// as soon as they are granted)
	Passive
};

DECLARE_LOG_CATEGORY_EXTERN(LogGameplayAbility, Log, All);

/**
 * Base project GameplayAbility
 */
UCLASS()
class DEMOPROJECT_API UDPGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Costs", meta=(ClampMin="0.0",ClampMax="100.0", UIMin="0.0", UIMax="100"))
	float AbilityCost = 0.f;

protected:

	// Defines how this ability is meant to activate.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	ETHABAbilityActivationPolicy ActivationPolicy = ETHABAbilityActivationPolicy::OnInputTriggered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Ability Animation Montage")
	TObjectPtr<UAnimMontage> AbilityAnimationMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation | Ability Animation Montage")
	FName StartSection = NAME_None;

public:

	void TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const;
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;	

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void FinishingAbility();

	// Play an Ability Anime Montage
	UFUNCTION(BlueprintCallable)
	UAbilityTask_PlayMontageAndWait* GetPlayAnimMontageTask();

protected:
	
	/** Called when this ability is granted to the ability system component. */
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityAdded")
	void K2_OnAbilityAdded();

	// Returns if the input that triggers this ability is currently down
	UFUNCTION(BlueprintPure)
	bool IsTriggeringInputDown() const;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
