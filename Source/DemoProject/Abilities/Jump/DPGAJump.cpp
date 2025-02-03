// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPGAJump.h"

#include "Characters/DPCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DPGAJump)

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPGAJump::UDPGAJump()
{
	//Constructor
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
bool UDPGAJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const auto Character = Cast<ADPCharacter>(ActorInfo->AvatarActor.Get());
	return (Character && Character->CanJump());
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (OwnerCharacter = Cast<ADPCharacter>(OwnerInfo->AvatarActor.Get()))
	{
		OwnerCharacter->Jump();
		OwnerCharacter->LandedDelegate.AddDynamic(this, &ThisClass::OnLanded);
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAJump::OnLanded(const FHitResult& Hit)
{
	// Ends the ability when the character lands
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAJump::FinishingAbility()
{
	if (OwnerCharacter)
	{
		OwnerCharacter->StopJumping();
		OwnerCharacter->LandedDelegate.RemoveAll(this);
	}
}
