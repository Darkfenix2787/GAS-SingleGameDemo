// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPGADash.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Characters/DPCharacter.h"
#include "Components/DPCharacterMovementComponent.h"
#include "DPTApplyRootMotion_Dash.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPGADash::UDPGADash()
{
	//Constructor
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGADash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);	

	if (auto OwnerCharacter = Cast<ADPCharacter>(OwnerInfo->AvatarActor.Get()))
	{	
		if (auto MovementComponent = Cast<UDPCharacterMovementComponent>(OwnerCharacter->GetMovementComponent()))
		{

			const FVector DashDirection = OwnerCharacter->GetActorForwardVector();
			const float FinishVelocity = MovementComponent->MaxWalkSpeed;

			DashAbilityTask = UDPTApplyRootMotion_Dash::ApplyRootMotionDash(this, "DashTask", DashDirection, DashStrenght, false, DashDuration, nullptr, false, ERootMotionAccumulateMode::Override, false, EMovementMode::MOVE_None, ERootMotionFinishVelocityMode::ClampVelocity, FVector::ZeroVector, FinishVelocity);			
			if (DashAbilityTask)
			{
				DashAbilityTask->OnFinish.AddDynamic(this, &UDPGADash::OnTaskFinished);
				DashAbilityTask->ReadyForActivation();
			}			
		}

		if (UAbilityTask_PlayMontageAndWait* AnimationTask = GetPlayAnimMontageTask())
		{
			AnimationTask->ReadyForActivation();
		}
	}	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGADash::OnTaskFinished(bool bTimedOut, bool bBlockingImpact)
{
	if (DashAbilityTask)
	{
		DashAbilityTask->OnFinish.RemoveAll(this);
	}
	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
