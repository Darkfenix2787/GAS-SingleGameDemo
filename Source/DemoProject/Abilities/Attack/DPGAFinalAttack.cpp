// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPGAFinalAttack.h"

#include "Abilities/DPGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "AbilitySystemComponent.h"
#include "Characters/DPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Weapons/DPBaseWeapon.h"


// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAFinalAttack::BindComboTagCallbacks()
{
	auto* WaitComboTagAddedTask = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(this, AnimationTags::ANS_FinalAttack);
	if (WaitComboTagAddedTask)
	{
		WaitComboTagAddedTask->Added.AddDynamic(this, &UDPGAAttack::OnComboTagAdded);
		WaitComboTagAddedTask->ReadyForActivation();
	}

	auto* WaitComboTagRemovedTask = UAbilityTask_WaitGameplayTagRemoved::WaitGameplayTagRemove(this, AnimationTags::ANS_FinalAttack);
	if (WaitComboTagRemovedTask)
	{
		WaitComboTagRemovedTask->Removed.AddDynamic(this, &UDPGAAttack::OnComboTagRemoved);
		WaitComboTagRemovedTask->ReadyForActivation();
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPGAFinalAttack::OnComboTagAdded()
{
	if (ADPCharacter* Character = Cast<ADPCharacter>(GetAvatarActorFromActorInfo()))
	{
		if (ADPBaseWeapon* Weapon = Character->GetEquippedWeapon())
		{
			Weapon->SetDamageMultiplier(DefaultDamageMultiplier);
		}
		
		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(Character);
		TArray<AActor*> OverlappedActors;

		UKismetSystemLibrary::SphereOverlapActors(this, Character->GetActorLocation(), AttackRadius, TArray<TEnumAsByte<EObjectTypeQuery>>(), ADPCharacter::StaticClass(), IgnoredActors, OverlappedActors);

		for (AActor* AffectedActor : OverlappedActors)
		{
			if (auto TargetCharacter = Cast<ADPCharacter>(AffectedActor))
			{
				//Launch Enemy
				UCharacterMovementComponent* TargetMovement = AffectedActor->FindComponentByClass<UCharacterMovementComponent>();
				if (TargetMovement)
				{
					TargetCharacter->ToggleMovement(true);
					FVector LaunchDirection = TargetCharacter->GetActorLocation() - Character->GetActorLocation();
					LaunchDirection.Normalize();
					LaunchDirection.Z = PushZDirection;
					
					TargetMovement->Launch(LaunchDirection * PushForce);

					DrawDebugSphere(GetWorld(), Character->GetActorLocation(), AttackRadius, 24, FColor::Red, false, 3.f, 0, 2);

					// Apply damage
					auto TargetASC = TargetCharacter->GetAbilitySystemComponent();
					auto OwnerASC = Character->GetAbilitySystemComponent();

					if (TargetASC && OwnerASC)
					{
						FGameplayEffectContextHandle DamageEffectContext = OwnerASC->MakeEffectContext();
						DamageEffectContext.AddInstigator(OwnerASC->GetOwner(), Character);


						const auto& SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.0f, DamageEffectContext);

						if (SpecHandle.Data.IsValid())
						{
							SpecHandle.Data->SetSetByCallerMagnitude(SetByCallerTags::SetByCaller_Damage, -DamageAmount);
							OwnerASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
						}
					}
				}
			}
		}
	}
}
