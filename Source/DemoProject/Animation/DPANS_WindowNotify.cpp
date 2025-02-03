// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPANS_WindowNotify.h"

#include "AbilitySystemComponent.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPANS_WindowNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UAbilitySystemComponent* ASC = OwnerActor->FindComponentByClass<UAbilitySystemComponent>())
		{
			ASC->AddLooseGameplayTag(ANSWindowTag);
		}
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
void UDPANS_WindowNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* OwnerActor = MeshComp->GetOwner())
	{
		if (UAbilitySystemComponent* ASC = OwnerActor->FindComponentByClass<UAbilitySystemComponent>())
		{
			ASC->RemoveLooseGameplayTag(ANSWindowTag);
		}
	}
}
