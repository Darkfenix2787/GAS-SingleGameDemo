// This project belongs to Daniel Corredor, Use it only for study purposes.


#include "DPCostMagnitudeCalculation.h"

#include "DPGameplayAbility.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------- //
float UDPCostMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	if (const auto GameplayAbility = Cast<UDPGameplayAbility>(Spec.GetContext().GetAbility()))
	{
		return GameplayAbility->AbilityCost;
	}

	return 0.0f;
}
