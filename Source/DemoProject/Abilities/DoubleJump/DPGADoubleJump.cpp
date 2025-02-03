// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPGADoubleJump.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Characters/DPCharacter.h"
#include "Components/DPCharacterMovementComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DPGADoubleJump)

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPGADoubleJump::UDPGADoubleJump()
{
	AdditionalJumpZVelocity = 0.f;	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGADoubleJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{	
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
	DoubleJump();
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGADoubleJump::DoubleJump()
{
	if (auto MovementComponent = Cast<UDPCharacterMovementComponent>(OwnerCharacter->GetMovementComponent()))
	{
		MovementComponent->SetAdditionalJumpZVelocity(AdditionalJumpZVelocity);		
	}

	if (UAbilityTask_PlayMontageAndWait* AnimationTask = GetPlayAnimMontageTask())
	{
		AnimationTask->ReadyForActivation();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGADoubleJump::FinishingAbility()
{
	if (OwnerCharacter)
	{
		if (auto MovementComponent = Cast<UDPCharacterMovementComponent>(OwnerCharacter->GetMovementComponent()))
		{
			MovementComponent->ClearAdditionalJumpZVelocity(AdditionalJumpZVelocity);			
		}
	}
	
	Super::FinishingAbility();
}