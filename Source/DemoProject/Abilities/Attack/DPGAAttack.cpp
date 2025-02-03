// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPGAAttack.h"

#include "Abilities/DPGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "AbilitySystemComponent.h"
#include "Characters/DPCharacter.h"
#include "Weapons/DPBaseWeapon.h"


// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
UDPGAAttack::UDPGAAttack()
{
	//Constructor
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);	
	
	if (UAbilityTask_PlayMontageAndWait* AnimationTask = GetPlayAnimMontageTask())
	{	
		AnimationTask->OnCompleted.AddDynamic(this, &UDPGAAttack::OnAnimationCompleted);

		if (auto ActorOwner = Cast<ADPCharacter>(GetOwningActorFromActorInfo()))
		{
			ActorOwner->ToggleMovement(false);
		}

		BindCollisionTagCallbacks();
		BindComboTagCallbacks();

		AnimationTask->ReadyForActivation();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::OnAnimationCompleted()
{

	if (auto ActorOwner = Cast<ADPCharacter>(GetOwningActorFromActorInfo()))
	{
		ActorOwner->ToggleMovement(true);		

		if (auto CharacterASC = ActorOwner->GetAbilitySystemComponent())
		{
			CharacterASC->CancelAllAbilities();
		}
	}	
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::BindCollisionTagCallbacks()
{
	auto* WaitCollisionTagAddedTask = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(this, AnimationTags::ANS_HandleCollision);
	if (WaitCollisionTagAddedTask)
	{
		WaitCollisionTagAddedTask->Added.AddDynamic(this, &UDPGAAttack::OnCollisionTagAdded);
		WaitCollisionTagAddedTask->ReadyForActivation();
	}

	auto* WaitCollisionTagRemovedTask = UAbilityTask_WaitGameplayTagRemoved::WaitGameplayTagRemove(this, AnimationTags::ANS_HandleCollision);
	if (WaitCollisionTagRemovedTask)
	{
		WaitCollisionTagRemovedTask->Removed.AddDynamic(this, &UDPGAAttack::OnCollisionTagRemoved);
		WaitCollisionTagRemovedTask->ReadyForActivation();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::BindComboTagCallbacks()
{
	auto* WaitComboTagAddedTask = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(this, AnimationTags::ANS_HandleCombo);
	if (WaitComboTagAddedTask)
	{
		WaitComboTagAddedTask->Added.AddDynamic(this, &UDPGAAttack::OnComboTagAdded);
		WaitComboTagAddedTask->ReadyForActivation();
	}

	auto* WaitComboTagRemovedTask = UAbilityTask_WaitGameplayTagRemoved::WaitGameplayTagRemove(this, AnimationTags::ANS_HandleCombo);
	if (WaitComboTagRemovedTask)
	{
		WaitComboTagRemovedTask->Removed.AddDynamic(this, &UDPGAAttack::OnComboTagRemoved);
		WaitComboTagRemovedTask->ReadyForActivation();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::OnCollisionTagAdded()
{
	EnableCollision(true);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::OnCollisionTagRemoved()
{
	EnableCollision(false);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::EnableCollision(bool bEnable)
{
	if (ADPCharacter* Character = Cast<ADPCharacter>(GetAvatarActorFromActorInfo()))
	{
		if (ADPBaseWeapon* Weapon = Character->GetEquippedWeapon())
		{
			Weapon->ToggleBoxCollision(bEnable);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::OnComboTagAdded()
{
	if (ADPCharacter* Character = Cast<ADPCharacter>(GetAvatarActorFromActorInfo()))
	{
		Character->SetComboAlertVisibility(true);
		if (ADPBaseWeapon* Weapon = Character->GetEquippedWeapon())
		{
			Weapon->SetDamageMultiplier(AbilityDamageMultiplier);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAAttack::OnComboTagRemoved()
{	
	if (ADPCharacter* Character = Cast<ADPCharacter>(GetAvatarActorFromActorInfo()))
	{
		Character->SetComboAlertVisibility(false);
		if (ADPBaseWeapon* Weapon = Character->GetEquippedWeapon())
		{
			Weapon->SetDamageMultiplier(DefaultDamageMultiplier);
		}
	}
}