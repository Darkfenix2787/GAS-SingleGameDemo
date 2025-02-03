// This project belongs to Daniel Corredor, Use it only for study purposes.

#include "DPGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY(LogGameplayAbility);

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGameplayAbility::TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const
{
	const bool bIsPredicting = (Spec.ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::Predicting);
	
	// Try to activate if activation policy is on spawn.
	if (ActorInfo && !Spec.IsActive() && !bIsPredicting && (ActivationPolicy == ETHABAbilityActivationPolicy::OnSpawn))
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		const AActor* AvatarActor = ActorInfo->AvatarActor.Get();

		// If avatar actor is torn off or about to die, don't try to activate until we get the new one.
		if (ASC && AvatarActor && !AvatarActor->GetTearOff() && (AvatarActor->GetLifeSpan() <= 0.0f))
		{
			const bool bIsLocalExecution = (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::LocalPredicted) || (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::LocalOnly);
			const bool bIsServerExecution = (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::ServerOnly) || (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::ServerInitiated);

			const bool bClientShouldActivate = ActorInfo->IsLocallyControlled() && bIsLocalExecution;
			const bool bServerShouldActivate = ActorInfo->IsNetAuthority() && bIsServerExecution;

			if (bClientShouldActivate || bServerShouldActivate)
			{
				ASC->TryActivateAbility(Spec.Handle);
			}
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	K2_OnAbilityAdded();

	TryActivateAbilityOnSpawn(ActorInfo, Spec);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
bool UDPGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return (Character != nullptr);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, OwnerInfo, ActivationInfo))
	{
		return;
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	FinishingAbility();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDPGameplayAbility::FinishingAbility()
{
	//Do stuff before the Endability (To use in child classes)
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
bool UDPGameplayAbility::IsTriggeringInputDown() const
{
	return GetCurrentAbilitySpec()->InputPressed;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	// Passive abilities
	if (ActivationPolicy == ETHABAbilityActivationPolicy::Passive)
	{
		bool bSuccess = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		if (!bSuccess)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("Failed to activate passive ability: %s"), *GetName());
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UAbilityTask_PlayMontageAndWait* UDPGameplayAbility::GetPlayAnimMontageTask()
{
	if (AbilityAnimationMontage)
	{
		FString MontageName = AbilityAnimationMontage->GetName();
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			*MontageName,
			AbilityAnimationMontage,
			1.0f,
			StartSection,
			true
		);

		return MontageTask;
	}

	return nullptr;
}